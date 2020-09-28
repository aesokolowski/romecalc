#include "../include/utilities.h"
#include <cstring>

//  may want to change this to return an int (0, 1, -1) with -1 meaning a
//  string is numeric, but contains one (and only one) decimal point
bool is_numeric(const char *str)
{
    size_t i = 0;
    char next = *str;

    while (next != '\0') {
        if (next < 0x30 || next > 0x39) return false;
        else                            next = *(++i + str);
    }

    return true;
}

//                  1 5 10 50 100 500 1000
//  roman numerals: I V  X  L   C   D    M
//                  i v  x  l   c   d    m
//                  ----------------------
//  ordered:        C D  I  L   M   V    X
//                  c d  i  l   m   v    x
//  ASCII (hex):    43   49     4D       58
//                    44    4C      56
//               add hex 20 for lowercase
bool is_roman(const char *str)
{
    size_t i = 0;
    char next = *str;

    while (next != '\0') {
        switch (next) {
            case 0x43:
            case 0x44:
            case 0x49:
            case 0x4c:
            case 0x4d:
            case 0x56:
            case 0x58:
            case 0x63:
            case 0x64:
            case 0x69:
            case 0x6c:
            case 0x6d:
            case 0x76:
            case 0x78:
                next = *(++i + str);
                break;
            default:
                return false;
        }
    }

    return true;
}
