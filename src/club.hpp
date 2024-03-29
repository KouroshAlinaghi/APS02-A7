#ifndef CLUB_HEADERFILE
#define CLUB_HEADERFILE

#include <string>

class Club {
private:
    std::string name;
    int points;
    int goals_scored;
    int goals_conceded;
public:
    Club(std::string name_) {
        name = name_;
        points = 0;
        goals_scored = 0;
        goals_conceded = 0;
    }
    std::string get_name();
    void inc_goals_scored(int goals);
    void inc_goals_conceded(int goals);
    void inc_points(int points_);
    int get_points();
    int get_goals_scored();
    int get_goals_conceded();
    int get_goals_diff();
    void print_row(int index);
};

#endif
