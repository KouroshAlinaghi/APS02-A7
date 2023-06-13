#ifndef INPUT_HEADERFILE
#define INPUT_HEADERFILE

#include <vector>
#include <string>

const std::string LEAGUE_CSV_FILE_PATH = "./data/premier_league.csv";
const std::string WEEK_STATS_CSV_FILE_PATH = "./data/weeks_stats/week";
const std::string OWN_GOAL = "OWN_GOAL";

enum WEEK_STATS_COLUMNS {
    MATCH, RESULT, INJURED, YELLOW_CARD, RED_CARD, GOALS_AND_ASSISTS, HOME_SQUAD, AWAY_SQUAD
};

typedef std::vector<std::string> Arguments;
    
const char DELIMITERS[10] = {':', ':', ';', ';', ';', ';', ';', ';', ';'};
const WEEK_STATS_COLUMNS COLUMNS[10] = { MATCH, RESULT, INJURED, YELLOW_CARD, RED_CARD, GOALS_AND_ASSISTS, HOME_SQUAD, AWAY_SQUAD };

std::string trim(std::string sr);
Arguments split(std::string str, char delim);

#endif
