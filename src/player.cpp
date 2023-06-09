#include <iomanip>
#include <iostream>

#include "player.hpp"
#include "player_stats.hpp"

using namespace std;

string Player::get_name() {
    return name;
}

Club* Player::get_team() {
    return team;
}

PLAYER_POSITION Player::get_position() {
    return position;
}

void Player::get_injured() {
    weeks_left_until_injury_recovery = WEEKS_NEEDED_TO_RECOVER_INJURY;
    stats.back().set_injury(true);
}

void Player::recieve_yellow_card() {
    yellow_cards_count++;
    stats.back().set_yellow_card(true);
}

void Player::recieve_red_card() {
    stats.back().set_red_card(true);
}

void Player::set_score(double score) {
    total_points += score;
    stats.back().set_score(score);
    stats.back().set_played(true);
}

void Player::initialize_new_week_stats() {
    stats.push_back(PlayerStats());
}

double Player::get_current_week_score() {
    if (stats.empty()) return 0;
    return stats.back().get_score();
}

double Player::get_week_score(int week) {
    if (stats.empty()) return 0;
    return stats[week-1].get_score();
}

string Player::get_position_shortened() {
    switch (position) {
        case GOALKEEPER:
            return "gk";
        case DEFENDER:
            return "df";
        case MIDFIELDER:
            return "md";
        default:
            return "fw";
    }
}

bool Player::is_available() {
    if (stats.empty()) return true;
    if (yellow_cards_count % 3 == 0 and stats.back().had_yellow_card()) return false;
    if (stats.back().had_red_card()) return false;
    if (weeks_left_until_injury_recovery) return false;
    return true;
}

void Player::recover_one_week() {
    weeks_left_until_injury_recovery = max(0, weeks_left_until_injury_recovery-1);
}

double Player::get_avg_score() {
    if (!get_weeks_played()) return 0;
    return total_points / get_weeks_played();
}

int Player::get_weeks_played() {
    int c = 0;
    for (PlayerStats w : stats)
        if (w.did_play())
            c++;
    return c;
}

void Player::print_week_details(int week) {
    cout << name << " | score: "<< fixed << setprecision(1) << get_week_score(week) << endl;
}

void Player::print_with_details(int index) {
    cout << index << ". name: " << name << " | role: " << get_position_shortened() << " | score: " << fixed << setprecision(1) << get_avg_score() << endl;
}
