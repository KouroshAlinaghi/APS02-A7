#ifndef GENERAL_HEADERFILE
#define GENERAL_HEADERFILE

#include <string>

#include "command.hpp"

HTTP_VERB string_to_verb(std::string str);
Arguments get_args(std::vector<std::string> words);

#endif
