#include <iostream>
#include <string>

#include "app.hpp"
#include "command.hpp"
#include "input.hpp"
#include "custom_exception.hpp"
#include "general.hpp"

using namespace std;

void App::initialize_commands() {
    commands.push_back(new Command(get_team_of_the_week, "team_of_the_week", HTTP_VERB::GET));
    commands.push_back(new Command(get_players, "players", HTTP_VERB::GET));
    commands.push_back(new Command(get_league_standings, "league_standings", HTTP_VERB::GET));
    commands.push_back(new Command(get_users_ranking, "users_ranking", HTTP_VERB::GET));
    commands.push_back(new Command(get_matches_result, "matches_result_league", HTTP_VERB::GET));
    commands.push_back(new Command(signup, "signup", HTTP_VERB::POST));
    commands.push_back(new Command(login, "login", HTTP_VERB::POST));
    commands.push_back(new Command(register_admin, "register_admin", HTTP_VERB::POST));
    commands.push_back(new Command(logout, "logout", HTTP_VERB::POST));
    commands.push_back(new Command(sell_player, "sell_player", HTTP_VERB::POST));
    commands.push_back(new Command(buy_player, "buy_player", HTTP_VERB::POST));
    commands.push_back(new Command(get_squad, "squad", HTTP_VERB::GET));
    commands.push_back(new Command(close_transfer_window, "close_transfer_window", HTTP_VERB::GET));
    commands.push_back(new Command(open_transfer_window, "open_transfer_window", HTTP_VERB::GET));
    commands.push_back(new Command(pass_week, "pass_week", HTTP_VERB::POST));
}

void App::execute_command(HTTP_VERB verb, string command_name, Arguments args) {
    for (Command* cmd : commands)
        if (cmd->get_name() == command_name && cmd->get_verb() == verb) {
            cmd->execute(db, cookie, args);
            return;
        }
}

void App::start() {
    string new_line;
    while (getline(cin, new_line)) {
        if (new_line.empty()) continue;
        vector<string> words = split(new_line, ' ');
        if (words.size() < 2) continue;
        try {
            execute_command(string_to_verb(words.front()), words.at(1), get_args(words));
        } catch (CustomException& e) {
            cout << e.what() << endl;
        }
    }
}