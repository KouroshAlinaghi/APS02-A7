#ifndef PLAYER_STATS_HEADERFILE
#define PLAYER_STATS_HEADERFILE

class PlayerStats {
private:
    bool injured;
    bool yellow_card;
    bool red_card;
    double score;
public:
    PlayerStats() {
        injured = false;
        yellow_card = false;
        red_card = false;
        score = 0;
    }
    void set_injury(bool is_injured);
    void set_yellow_card(bool y_c);
    void set_red_card(bool r_c);
    void set_score(double score_);
    double get_score();
    bool had_yellow_card();
    bool had_red_card();
};

#endif
