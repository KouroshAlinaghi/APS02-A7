#ifndef USER_HEADERFILE 
#define USER_HEADERFILE 

#include "account.hpp"

class User : public Account {
private:
    double total_points;
    int players_sold_this_week;
    int players_bought_this_week;
    std::vector<Player*> squad;
public:
    User(std::string username_, std::string password_) : Account(username_, password_) {
        total_points = 0;
        players_sold_this_week = 0;
        players_bought_this_week = 0;
    }
    bool is_admin();
    int get_players_sold_this_week();
    int get_players_bought_this_week();
    void reset_transfers_counts();
    bool has_player(Player* player_);
    void sell_player(Player* player_);
    void inc_solds_count();
    int get_number_of_players(PLAYER_POSITION);
    void buy_player(Player* player_);
    void inc_boughts_count();
    bool is_complted();
    std::vector<Player*> get_squad();
    int get_total_points();
    void update_total_points();
    bool had_completed_squad();
};

#endif
