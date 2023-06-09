#include <iostream>

#include "club.hpp"

using namespace std;

string Club::get_name() {
    return name;
}

void Club::inc_goals_scored(int goals) {
    goals_scored += goals;
}

void Club::inc_goals_conceded(int goals) {
    goals_conceded += goals;
}

void Club::inc_points(int points_) {
    points += points_;
}

int Club::get_points() {
    return points;
}

int Club::get_goals_scored() {
    return goals_scored;
}

int Club::get_goals_conceded() {
    return goals_conceded;
}

int Club::get_goals_diff() {
    return goals_scored - goals_conceded;
}

void Club::print_row(int index) {
    cout << index << ". " << get_name() << ": score: " << get_points() << " | GF: " << get_goals_scored() << " | GA: " << get_goals_conceded() << endl;
}
