#include "../include/UserNum.h"
#include <iostream>

//  I want this constructor to push each character of str onto the
//  vector<char>, and I guess that's about it
UserNum::UserNum(const char *str)
{
    if (str) {
        size_t i = 0;
        char next = *str;

        while (next != '\0') {
            this->user_num.push_back(next);
            next = *(++i + str);
        }
    }
}
