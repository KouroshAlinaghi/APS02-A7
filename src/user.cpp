#include "user.hpp"
#include "command.hpp"
#include "player.hpp"
#include <iostream>

using namespace std;

bool User::is_admin() {
    return false;
}

int User::get_players_sold_this_week() {
    return players_sold_this_week;
}

int User::get_players_bought_this_week() {
    return players_bought_this_week;
}

void User::reset_transfers_counts() {
    players_sold_this_week = 0;
    players_bought_this_week = 0;
}

bool User::has_player(Player* player_) {
    for (Player* player : squad)
        if (player == player_)
            return true;
    return false;
}

void User::sell_player(Player* player_) {
    vector<Player*> new_squad;
    for (Player* player : squad)
        if (player != player_)
            new_squad.push_back((player));
    squad = new_squad;
}
    
void User::inc_solds_count() {
    players_sold_this_week++;
}

int User::get_number_of_players(PLAYER_POSITION position) {
    int counter = 0;
    for (Player* player : squad)
        if (player->get_position() == position)
            counter++;
    return counter;
}

void User::buy_player(Player* player_) {
    squad.push_back(player_);
    if (squad.size() == NUM_OF_PLAYERS_IN_SQUAD) 
        completed_squad = true;
}
    
void User::inc_boughts_count() {
    players_bought_this_week++;
}

bool User::is_complted() {
    return squad.size() == NUM_OF_PLAYERS_IN_SQUAD;
}

vector<Player*> User::get_squad() {
    return squad;
}

int User::get_total_points() {
    return total_points;
}

void User::update_total_points() {
    for (Player* player : squad)
        total_points += player->get_current_week_score();
}

bool User::had_completed_squad() {
    return completed_squad;
}
