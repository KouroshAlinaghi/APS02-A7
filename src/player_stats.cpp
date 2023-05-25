#include <iostream>

#include "player_stats.hpp"

using namespace std;

void PlayerStats::set_injury(bool is_injured) {
    injured = is_injured;
}

void PlayerStats::set_yellow_card(bool y_c) {
    yellow_card = y_c;
}

void PlayerStats::set_red_card(bool r_c) {
    red_card = r_c;
}

void PlayerStats::set_score(double score_) {
    score = score_;
}

double PlayerStats::get_score() {
    return score;
}

bool PlayerStats::had_yellow_card() {
    return yellow_card;
}

bool PlayerStats::had_red_card() {
    return red_card;
}
