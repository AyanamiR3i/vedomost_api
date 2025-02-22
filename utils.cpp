#include "headers/utils.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter)
{
        //разбиение строки по разделителю
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(str);

        while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
        }

        return tokens;
}
