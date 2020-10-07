#include "../include/UserNum.h"
#include <cstring>
#include <iostream>

//  saves string as c-string and vector of chars so I can easily access either
//  type whether I'm parsing or using for arithmatic
UserNum::UserNum(const char *str)
{
    if (str) {
        size_t i = 0;
        char next = *str;

        strcpy(this->user_nums, str);
        while (next != '\0') {
            this->user_numv.push_back(next);
            next = *(++i + str);
        }
    }
}
