#include "../include/UserNum.h"
#include "../include/utilities.h"
#include <cstring>
#include <iostream>
#include <vector>

const char *WARNING = "INTERNAL ERROR: illegal Roman Numeral detected, aborting program. Report to dev.";

// NOTE: NO_MORE needs to be changed as bits are added
const size_t ZERO = 0x00,
             I_MASK = 0x01,
             V_MASK = 0x02,
	     X_MASK0 = 0x03,
             X_MASK1 = 0x04,
	     NO_MORE = 0x07;


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

//  temp: 1 - 39
//  temp to develop parser, only for X, V and I for now, may add one digit at
//  a time thinking of using bitwise logic to keep track, so let's say:
//  0x00 means the next bit can be either X, V or I     0b000
//  0x06 means the next can only be I                   0b110
//  0x07 means any next character will be rejected      0b111
//  
//  first operation performed on any current character will be a mask
//  I is illegal: AND with 0x01
//  V is illegal: AND with 0x02
//  X is illegal: AND with 0x04
//
//  the easest is V, it can only appear once in a Roman Numeral, and Xs
//  cannot appear after it, so after checking if it's legal should OR with
//  0b110 to mark both X and V as illegal for all future characters.
//  I and X will depend more on the "in-a-row" and "last" variables.
//  I can be flagged as illegal as soon as three I's in a row show up,
//  but M needs a way to be unflagged by I for the extreme case of XXXIX
//  (also to prevent stuff like XIXX from getting through, which is the main
//  reason I'm redoing my approach from scratch)
bool check_xvi(UserNum un)
{
    char last;
    size_t in_a_row = 0,
	   len = un.get_count(),
	   flags = 0x00;
    std::vector<char> uv = un.get_unv();

    for (size_t i = 0; i < len; i++) {
        char current = uv[i];

	if (i > 0) {
	    // compare flags to appropriate mask for current
	    if (!(is_current_valid(flags, current))) return false;
            
            // don't bother with the rest if last char
	    if (i < len - 1) {
                // track how many
	        if (current == last) in_a_row++;
	        else in_a_row = 1;
                // update flags
		flags = update_flags(flags, current, last, in_a_row);
	    }
	} else {
            in_a_row++; // increment first char
	    flags = set_flags(current); // first char has separate set instead
	                                // of update
	}

	last = current;
    }

    return true;
}

bool is_current_valid(size_t fl, char ch) {
    switch (ch) {
	// I/i
	case 0x49:
        case 0x69:
            if (fl & I_MASK) return false;
	    break;
	// V/v
        case 0x56:
	case 0x76:
	    if (fl & V_MASK) return false;
	    break;
	// X/x
        case 0x58:
	case 0x78:
	    if (fl & X_MASK1) return false;
	    break;
        default:
	    std::cerr << WARNING << std::endl;
	    return false;
    }

    return true;
}

//  if the first char is V (or L/D in the future), flags need to be set because
//  any further occurances means invalid Roman Numeral... in the future this
//  will get bigger... an initial I will prevent subseq. Ls or Cs, for example
size_t set_flags(char ch)
{
    switch (ch) {
	// V/v
	case 0x56:
	case 0x76:
            // nothing except I can follow a V:
            return V_MASK | X_MASK1;
	default:
	    /* do nothing, might add illegal char check for formality */
	    break;
    }

    return ZERO;
}

//  worked this out with pen and paper: trust me, it works. here be bitwise.
size_t update_flags(size_t fl, char curr, char last, size_t iar)
{
    const char *WARNING = "INTERNAL ERROR: illegal Roman Numeral detected, aborting program. Report to dev.";

    switch (curr) {
	// I/i
	case 0x49:
        case 0x69:
	    if (iar > 1 && iar < 3) {
                return fl | V_MASK | X_MASK1;
	    } else if (iar >= 3) {
                return NO_MORE;
	    }
	    if (last == 0x58 || last == 0x78) { // X/x
                return fl & X_MASK0;
	    }
	    break; 
        // V/v
	case 0x56:
        case 0x76:
	    if (last == 0x49 || last == 0x69) { // I/i
                return NO_MORE;
	    }
	    return fl | V_MASK | X_MASK1;
	// X/x
	case 0x58:
        case 0x78:
	    if (last == 0x49 || last == 0x69) { // I/i
                return NO_MORE;
	    }
            if (iar >= 3) {
                return fl | X_MASK1;
	    }
            break;
        default:
	    std::cerr << WARNING << std::endl;
	    return NO_MORE;
    }

    return fl;
}
