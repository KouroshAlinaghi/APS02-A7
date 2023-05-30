#include "general.hpp"
#include "command.hpp"
#include "custom_exceptions/bad_request_exception.hpp"
#include <vector>

using namespace std;

HTTP_VERB string_to_verb(string str) {
    if (str == "GET") return HTTP_VERB::GET;
    if (str == "POST") return HTTP_VERB::POST;
    if (str == "PUT") return HTTP_VERB::PUT;
    if (str == "DELETE") return HTTP_VERB::DELETE;
    return HTTP_VERB::NO_VERB;
}

Arguments get_args(vector<string> words) {
    Arguments res;
    for (int i = 2; i < (int)words.size(); i++)
        res.push_back(words[i]);
    return res;
}

PLAYER_POSITION shortened_to_position(string pos) {
    if (pos == "fw")
        return FORWARD;
    if (pos == "md")
        return MIDFIELDER;
    if (pos == "df")
        return DEFENDER;
    if (pos == "gk")
        return GOALKEEPER;

    throw BadRequestException();
}
