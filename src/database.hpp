#ifndef DATABASE_HEADERFILE
#define DATABASE_HEADERFILE

#include <vector>
#include <string>

#include "player.hpp"
#include "account.hpp"
#include "club.hpp"
#include "match.hpp"

const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "123456";

class Database {
private:
    std::vector<Player*> players;
    std::vector<Account*> accounts;
    std::vector<Club*> clubs;
    std::vector<Match*> matches;
    void read_league_csv();
    Club* create_club(std::string club_name);
    Player* create_player(std::string name, Club* club, PLAYER_POSITION position);
    Match* create_match(Club* home, Club* away, Result res, int week);
    void update_standings_stats(Club* home, Club* away, Result res);
    void create_admin_account();
public:
    Database() {
        create_admin_account();
        read_league_csv();
    }
    std::vector<Player*> get_players();
    void read_week_stats(int week);
    std::vector<Club*> get_clubs_sorted();
    Account* get_user(std::string username);
    Account* create_user(std::string username, std::string pasword);
    std::vector<Player*> get_best_players(PLAYER_POSITION position, int count, int week);
    std::vector<Match*> get_matches(int week);
    Club* get_club(std::string club_name);
    Player* get_player(std::string player_name);
    std::vector<Player*> get_players_of_club(Club* club);
    void tell_player_the_week_passed();
    void reset_transfers_counts();
    void calculate_points();
    std::vector<Account*> get_users();
};

#endif
