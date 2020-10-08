#include "../include/UserNum.h"
#include "../include/utilities.h"
#include <cstring>
#include <vector>

//  may want to change this to return an int (0, 1, -1) with -1 meaning a
//  string is numeric, but contains one (and only one) decimal point
bool is_numeric(UserNum un)
{
    size_t len = un.get_count();
    std::vector<char> uv = un.get_unv();

    for (size_t i = 0; i < len; i++) {
	char el = uv[i];

        if (el < 0x30 || el > 0x39) return false;
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
bool is_roman(UserNum un)
{
    size_t len = un.get_count();
    std::vector<char> uv = un.get_unv();

    for (size_t i = 0; i < len; i++) {
        char el = uv[i];

        switch (el) {
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
                /* do nothing */
                break;
            default:
                return false;
        }
    }

    return true;
}
