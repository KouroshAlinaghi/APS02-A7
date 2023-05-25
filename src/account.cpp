#include "account.hpp"

using namespace std;

string Account::get_username() {
    return username;
}

bool Account::check_password(string password_) {
    return password_ == password;
}

bool Account::had_completed_squad() {
    return completed_squad;
}
