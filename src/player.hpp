#ifndef PLAYER_HEADERFILE
#define PLAYER_HEADERFILE

#include <string>
#include <vector>

#include "club.hpp"
#include "player_stats.hpp"

const int WEEKS_NEEDED_TO_RECOVER_INJURY = 4;

enum PLAYER_POSITION {
    GOALKEEPER,
    DEFENDER,
    MIDFIELDER,
    FORWARD
};

const std::vector<PLAYER_POSITION> POSITIONS_IN_ORDER { GOALKEEPER, DEFENDER, MIDFIELDER, FORWARD };

class Player {
private:
    std::string name;
    Club* team;
    PLAYER_POSITION position;
    double total_points;
    int weeks_left_until_injury_recovery;
    int yellow_cards_count;
    bool availablity;
    std::vector<PlayerStats> stats;
public:
    Player(Club* team_, std::string name_, PLAYER_POSITION position_) {
        team = team_;
        name = name_;
        position = position_;
        total_points = 0;
        weeks_left_until_injury_recovery = 0;
        availablity = true;
    }
    std::string get_name();
    Club* get_team();
    PLAYER_POSITION get_position();
    void get_injured();
    void recieve_yellow_card();
    void recieve_red_card();
    void set_score(double score);
    void initialize_new_week_stats();
    double get_current_week_score();
    double get_week_score(int week);
    std::string get_position_shortened();
    bool is_available();
    void recover_one_week();
};

#endif
