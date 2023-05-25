#ifndef MATCH_HEADERFILE
#define MATCH_HEADERFILE

#include "club.hpp"

typedef std::pair<int, int> Result;

class Match {
private:
    Club* home;
    Club* away;
    Result result;
    int week;
public:
    Match(Club* home_, Club* away_, Result result_, int week_) {
        home = home_;
        away = away_;
        result = result_;
        week = week_;
    }
    int get_week();
    void print_result();
};

#endif
