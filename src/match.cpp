#include <iostream>
#include "match.hpp"

using namespace std;

int Match::get_week() {
    return week;
}

void Match::print_result() {
    cout << home->get_name() << " " << result.first << " | " << away->get_name() << " " << result.second << endl;
}
