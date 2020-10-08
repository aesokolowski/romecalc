#include "../include/UserNum.h"
#include "../include/utilities.h"
#include <cstring>
#include <iostream>  // debug
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

//   determine whether or not a Roman numeral is valid, scanning from
//   left to right
//   this function assumes is_roman has already returned true, since all
//   1-character strings should pass
bool is_valid_roman(UserNum un)
{
    size_t len = un.get_count(),
	   in_a_row = 0;
    std::vector<char> uv = un.get_unv();

    for (size_t i = 0; ii < len; i++) {
        if (i > 0) {
	    char el = uv[i - 1];

            switch (uv[i]) {
	        case 0x4d:  // M
	        case 0x6d:  // m
	            // don't like nest switch statements, so putting a function
		    // call here
                    if (m_check(uv[i - 1], &in_a_row)) {
                        if (in_a_row == 0) in_a_row = 2;
		        else in_a_row++;
		    } else {
                        return false;
		    }

		    break;
		case 0x44:  // D
		case 0x64:  // d
		    if (!(el == 0x4d || el == 0x6d)) return false;
		    break;
		default:
		    return false;
	    }
	}
    }

    return true;
}

bool m_check(char ch, size_t *iar)
{
    //std::cout << "ch: " << ch << "\n" << "*iar" << *iar << "\n";
    switch (ch) {
        case 0x4d:  // M
        case 0x6d:  // m
	    if (*iar >= 3) return false;
	    break;
	case 0x43:  // C
	case 0x63:  // c
	    *iar = 2; // more than one M cannot follow a C
	    break;
	default:
	    return false; // nothing other than M or C can precede M
    }

    return true;
}
