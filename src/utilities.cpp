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

/*

//   determine whether or not a Roman numeral is valid, scanning from
//   left to right
//   this function assumes is_roman has already returned true, since all
//   1-character strings should pass
//   The rational behind multiple passes is to generate specific error
//   messages 1. invalid letter 2. invalid order 3. internal failure during
//   actual parsing
//   also this function is made a bit simpler by skipping the first character
//   no matter what
bool is_valid_roman(UserNum un)
{
    size_t len = un.get_count(),
	   in_a_row = 0;
    std::vector<char> uv = un.get_unv();

    for (size_t i = 0; i < len; i++) {
        if (i > 0) {
	    char last = uv[i - 1];

            switch (uv[i]) {
	        case 0x4d:  // M
	        case 0x6d:  // m
	            // don't like nest switch statements, so putting a function
		    // call here
                    if (m_check(last, &in_a_row)) {
                        if (in_a_row == 0) in_a_row = 2;
		        else in_a_row++;
		    } else {
                        return false;
		    }

		    break;
		case 0x44:  // D
		case 0x64:  // d
		    // if the last character is not M return false
		    if (!(last == 0x4d || last == 0x6d)) return false;
		    // should add a flag to prevent garbage like
		    // mmmdcm from getting through -- after the first
		    // d, no more m's allowed -- then so forth and
		    // so on down the line
		    break;
		case 0x43:  // C
		case 0x63:  // c
                    if (c_check(last, &in_a_row)) {
			if (in_a_row == 0xfade) in_a_row = 1;
			else if (in_a_row == 0) in_a_row = 2;
			else in_a_row++;
		    } else {
                        return false;
		    }
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

bool c_check(char ch, size_t *iar)
{
    switch (ch) {
        case 0x4d:  // M
	case 0x6d:  // m
	case 0x44:  // D
	case 0x64:  // d
	    *iar = 0xfade;  //  flag
	    break;
	case 0x43:  // C
	case 0x63:  // c
	    //  in theory:
	    //  if C is the first letter encountered, it must be the
	    //  second C, which is set outside -- if it's not the first
	    //  C encountered then iar would have been set to 1 by now
	    if (*iar >= 3) return false;
	    std::cout.flush();
	    break;
	case 0x58:  // X
	case 0x78:  // x
            *iar = 2;  // more than one C cannot follow a X
	    break;
	default:
	    return false;
    }

    return true;
}
*/







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
