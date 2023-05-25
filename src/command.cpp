#include <iostream>
#include <algorithm>
#include <vector>

#include "account.hpp"
#include "command.hpp"
#include "custom_exceptions/bad_request_exception.hpp"
#include "custom_exceptions/empty_exception.hpp"
#include "custom_exceptions/not_found_exception.hpp"
#include "custom_exceptions/permission_denied_exception.hpp"
#include "player.hpp"

using namespace std;

string Command::get_name() {
    return name;
}

HTTP_VERB Command::get_verb() {
    return verb;
}

void Command::execute(Database* db, Session* cookie, Arguments args) {
    exec(db, cookie, args);
}

void get_team_of_the_week(Database* db, Session* cookie, Arguments args) {
    if (args.empty() or args[0] != "?" or (args.size() == 3 and args[1] != "week") or (args.size() != 1 and args.size() != 3))
        throw BadRequestException();

    int week = args.size() == 3 ? stoi(args[2]) : cookie->get_current_week();   
    if (week <= 0 or week > cookie->get_current_week()) throw BadRequestException();
    
    vector<vector<Player*>> chosen_players;
    for (PLAYER_POSITION position : POSITIONS_IN_ORDER) 
        chosen_players.push_back(db->get_best_players(position, PLAYERS_COUNT_IN_SQUAD[position], week));
    
    cout << "list of players:" << endl;
    for (int i = 0, p = 0; i < NUM_OF_PLAYERS_IN_SQUAD; p++) {
        for (Player* player : chosen_players[p]) {
            cout << i+1 << ". name: " << player->get_name() << " | score: " << player->get_week_score(week) << endl;
            i++;
        }
    }
}

void get_players(Database* db, Session*, Arguments args) {
    if (args.empty() or args[0] != "?") throw BadRequestException();
    if (args.size() == 3 and args[1] != "team") throw BadRequestException();
    if (args.size() != 1 and args.size() != 3 and args.size() != 4 and args.size() != 5) throw BadRequestException();

    string team_name;
    for (char c : args[2])
        team_name += (c == '_' ? ' ' : c);

    Club* team = db->get_club(team_name);
    if (!team) throw NotFoundException();

    bool sort_by_rank = args.back() == "ranks" ? true : false;
    bool filter_by_position = false;
    PLAYER_POSITION position;

    if (args.back() == "fw") {
        position = FORWARD;
        filter_by_position = true;
    } else if (args.back() == "md") {
        position = MIDFIELDER;
        filter_by_position = true;
    } else if (args.back() == "df") {
        position = DEFENDER;
        filter_by_position = true;
    } else if (args.back() == "gk") {
        position = GOALKEEPER;
        filter_by_position = true;
    }

    vector<Player*> players = db->get_players_of_club(team);
    if (sort_by_rank)
        sort(players.begin(), players.end(), [](Player* p1, Player* p2) { return p1->get_current_week_score() > p2->get_current_week_score(); });

    int i = 0;
    for (Player* player : players) {
        if (filter_by_position and player->get_position() != position) continue;
        i++;
        cout << i << ". name: " << player->get_name() << " | role: " << player->get_position_shortened() << " | score: " << player->get_current_week_score() << endl;
    }
}

void get_league_standings(Database* db, Session*, Arguments) {
    vector<Club*> teams = db->get_clubs_sorted();
    cout << "league standings:" << endl;
    for (int i = 0; i < (int)teams.size(); i++)
        cout << i+1 << ". " << teams[i]->get_name() << ": score: " << teams[i]->get_points()
        << " | GF: " << teams[i]->get_goals_scored() << " | GA: " << teams[i]->get_goals_conceded() << endl;
}

void get_users_ranking(Database* db, Session*, Arguments args) {
    if (args.size() != 0) throw BadRequestException();

    vector<User*> users = db->get_users();
    sort(users.begin(), users.end(), [](User* u1, User* u2) { return u1->get_total_points() > u2->get_total_points();  });

    int i = 1;
    for (User* user : users) {
        cout << i << ". team_name: " << user->get_username() << " | point: " << user->get_total_points() << endl;
        i++;
    }
}

void get_matches_result(Database* db, Session* cookie, Arguments args) {
    if ((args.size() == 3 and args[1] != "week_num") or (args.size() != 3 and args.size() != 1) or args[0] != "?")
        throw BadRequestException();
    
    int week = args.size() == 3 ? stoi(args[2]) : cookie->get_current_week();   
    if (week <= 0 or week > cookie->get_current_week()) throw BadRequestException();

    for (Match* match : db->get_matches(week))
        match->print_result();
}

void signup(Database* db, Session* cookie, Arguments args) {
    if (args[0] != "?" or args[1] != "team_name" or args[3] != "password") throw BadRequestException();
    cookie->ensure_user_not_logged_in();
    
    Account* found_user = db->get_user(args[2]);
    if (found_user) throw BadRequestException();
    
    Account* new_user = db->create_user(args[2], args[4]);
    cookie->set_current_user(new_user);
    
    cout << "OK" << endl;
}

void login(Database* db, Session* cookie, Arguments args) {
    if (args[0] != "?" or args[1] != "team_name" or args[3] != "password") throw BadRequestException();
    cookie->ensure_user_not_logged_in();

    Account* found_user = db->get_user(args[2]);
    if (!found_user) throw NotFoundException();
    if (!found_user->check_password(args[4])) throw PermissionDeniedException();
    
    cookie->set_current_user(found_user);
    
    cout << "OK" << endl;
}

void register_admin(Database* db, Session* cookie, Arguments args) {
    if (args[0] != "?" or args[1] != "username" or args[3] != "password") throw BadRequestException();
    cookie->ensure_user_not_logged_in();

    Account* found_user = db->get_user(args[2]);
    if (!found_user or !found_user->is_admin()) throw BadRequestException();
    if (!found_user->check_password(args[4])) throw BadRequestException();
    
    cookie->set_current_user(found_user);

    cout << "OK" << endl;
}

void logout(Database*, Session* cookie, Arguments) {
    cookie->ensure_user_logged_in();
    cookie->set_current_user(nullptr);

    cout << "OK" << endl;
}

void sell_player(Database* db, Session* cookie, Arguments args) {
    if (args.size() < 3 or args[0] != "?" or args[1] != "name") throw BadRequestException();
    if (!cookie->is_transfer_window_open()) throw PermissionDeniedException();
    cookie->ensure_user_logged_in();
    if (cookie->get_current_user()->is_admin()) throw PermissionDeniedException();

    User* current_user = (User*)cookie->get_current_user();

    string player_name;
    for (int i = 2; i < (int)args.size(); i++)
        player_name = player_name + args[i] + " ";
    player_name.pop_back();

    Player* player = db->get_player(player_name);
    if (!player) throw NotFoundException();
    if (current_user->has_player(player)) throw NotFoundException();
    if (current_user->get_players_sold_this_week() >= MAX_SELLS and current_user->had_completed_squad()) throw PermissionDeniedException();

    current_user->sell_player(player);
    current_user->inc_solds_count();

    cout << "OK" << endl;
}

void buy_player(Database* db, Session* cookie, Arguments args) {
    if (args.size() < 3 or args[0] != "?" or args[1] != "name") throw BadRequestException();
    if (!cookie->is_transfer_window_open()) throw PermissionDeniedException();
    cookie->ensure_user_logged_in();
    if (cookie->get_current_user()->is_admin()) throw PermissionDeniedException();

    string player_name;
    for (int i = 2; i < (int)args.size(); i++)
        player_name = player_name + args[i] + " ";
    player_name.pop_back();

    User* current_user = (User*)cookie->get_current_user();

    Player* player = db->get_player(player_name);
    if (!player) throw NotFoundException();
    if (current_user->has_player(player)) throw BadRequestException();
    if (current_user->get_players_sold_this_week() >= MAX_BUYS and current_user->had_completed_squad()) throw PermissionDeniedException();
    if (current_user->get_number_of_players(player->get_position()) >= PLAYERS_COUNT_IN_SQUAD[player->get_position()])
        throw BadRequestException();

    current_user->buy_player(player);
    current_user->inc_boughts_count();

    cout << (player->is_available() ? "OK" : "This player is not available for the next week") << endl;
}

void get_squad(Database* db, Session* cookie, Arguments args) {
    if ((args.size() == 3 and args[1] != "fantasy_team") or (args.size() != 3 and args.size() != 1) or args[0] != "?")
        throw BadRequestException();
    cookie->ensure_user_logged_in();

    User* team = args.size() == 3 ? db->get_user(args[2]) : (User*)cookie->get_current_user();
    if (!team) throw NotFoundException();
    if (!team->is_complted()) throw EmptyException();

    vector<Player*> squad = team->get_squad();
    sort(squad.begin(), squad.end(), [](Player* p1, Player* p2) {
        if (p1->get_position() > p2->get_position()) return false;
        if (p1->get_position() < p2->get_position()) return true;
        return p1->get_name() < p2->get_name();
    });

    cout << "fantasy_team: " << team->get_username() << endl;
    cout << "Goalkeeper: " << squad[0]->get_name() << endl;
    cout << "Defender1: " << squad[1]->get_name() << endl;
    cout << "Defender2: " << squad[2]->get_name() << endl;
    cout << "Midfielder: " << squad[3]->get_name() << endl;
    cout << "Striker: " << squad[4]->get_name() << endl;
    cout << "Total Points: " << team->get_total_points() << endl;
}

void close_transfer_window(Database*, Session* cookie, Arguments) {
    cookie->ensure_admin_logged_in();
    cookie->set_transfer_window(false);

    cout << "OK" << endl;
}

void open_transfer_window(Database*, Session* cookie, Arguments) {
    cookie->ensure_admin_logged_in();
    cookie->set_transfer_window(true);

    cout << "OK" << endl;
}

void pass_week(Database* db, Session* cookie, Arguments) {
    cookie->ensure_admin_logged_in();

    cookie->pass_week();
    db->tell_player_the_week_passed();
    db->reset_transfers_counts();
    db->read_week_stats(cookie->get_current_week()+1);
    db->calculate_points();

    cout << "OK" << endl;
}
