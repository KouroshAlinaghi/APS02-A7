#ifndef ACCOUNT_HEADERFILE
#define ACCOUNT_HEADERFILE

#include "string"
#include "vector"

#include "player.hpp"

class Account {
protected:
    std::string username;
    std::string password;
    bool completed_squad;
public:
    Account(std::string username_, std::string password_) {
        username = username_;
        password = password_;
        completed_squad = false;
    }
    virtual bool is_admin() = 0;
    std::string get_username();
    bool check_password(std::string password_);
    virtual void reset_transfers_counts() {}
    virtual bool has_player(Player*) { return false; }
    virtual int get_players_sold_this_week() { return 0; }
    virtual int get_players_bought_this_week() { return 0; }
    bool had_completed_squad();
    virtual void sell_player(Player*) {}
    virtual void inc_solds_count() {}
    virtual int get_number_of_players(PLAYER_POSITION) { return 0; }
    virtual void buy_player(Player*) {}
    virtual void inc_boughts_count() {}
    virtual bool is_complted() { return false; }
    virtual std::vector<Player*> get_squad() { return std::vector<Player*>(); }
    virtual int get_total_points() { return 0; }
    virtual void update_total_points() {}
};

#endif
