#include "../include/UserNum.h"
#include "../include/utilities.h"
#include <cctype>
#include <cstring>
#include <iostream>
#include <vector>

const char *WARNING = "INTERNAL ERROR: illegal Roman Numeral detected, aborting program. Report to dev.";

// NOTE: NO_MORE needs to be changed as bits are added,
// as well as 0 masks
const size_t ZERO    = 0x00,
             I_MASK  = 0x01,
             V_MASK  = 0x02,
	     X_MASK0 = 0x1a,
             X_MASK1 = 0x04,
	     L_MASK  = 0x08,
	     C_MASK0 = 0x0f,
	     C_MASK1 = 0x10,
	     NO_MORE = 0x1f; 

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

/********  outdated comment but not deleting because it decribes original
 *         thought process
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
//  *******/

// this function didn't need any changes for expansion
bool check_xvi(UserNum un)
{
    char last;
    size_t in_a_row = 0,
	   len = un.get_count(),
	   flags = ZERO;
    std::vector<char> uv = un.get_unv();

    for (size_t i = 0; i < len; i++) {
        char current = uv[i];

	if (i > 0) {
	    // compare flags to appropriate mask for current
	    if (!(is_current_valid(flags, current))) return false;
            
            // don't bother with the rest if last char
	    if (i < len - 1) {
                // track how many
	        if (toupper(current) == toupper(last)) in_a_row++;
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

// returns false if matching bit is set, true if not set
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
	// L/l
	case 0x4c:
	case 0x6c:
	    if (fl & L_MASK) return false;
	    break;
	// C/c
	case 0x43:
	case 0x63:
            if (fl & C_MASK1) return false;
	    break;
        default:
	    std::cerr << WARNING << std::endl;
	    return false;
    }

    return true;
}

//  if the first char is V, L, or D, flags need to be set because
//  any further occurances means invalid Roman Numeral. I can rule out
//  M D C and L.
size_t set_flags(char ch)
{
    switch (ch) {
	// V/v
	case 0x56:
	case 0x76:
            //  nothing except I can follow a V:
            return C_MASK1 | L_MASK | V_MASK | X_MASK1;
	// I/i
	case 0x49:
        case 0x69:
	          /** FALLTHROUGH **/
	// L/l
	case 0x4c:
	case 0x6c:
	    //  C and L cannot follow an I or L:
	    return C_MASK1 | L_MASK;
	default:
	    /* do nothing, might add illegal char check for formality */
	    break;
    }

    return ZERO;
}

//  updates flags from second character onward. This function assumes
//  curr is already marked as valid (passed is_current_value) and assumes
//  set_flags was used on the first character of the string. Simple example:
//  if the current value is V then C, L, X and V are all marked as illegal
//  for further characters. If the last character was an I, however, all characters
//  are marked as illegal since nothing can follow IV.

//  more complicated example:
//  Let's say we're given XXXIXX (39 with an illegal extra X at the end)
//  let's trace each character and resulting bitfield:
//  X   -  00000   (a solitary X doesn't make anything in the current bit field
//                 illegal)
//  X   -  11000   (no more C's or L's)
//  X   -  11100   (no more X's)
//  I   -  11000   (I sees that X was last and unsets X, sets C and L if not
//                  already set)
//  X   -  11111   (all further characters made illegal when X follows an I)
//  X   -  11111 & 00100 so return false (logic in is_current_valid function)
//
//  here be bitwise!
size_t update_flags(size_t fl, char curr, char last, size_t iar)
{
    switch (curr) {
	// I/i
	case 0x49:
        case 0x69:
	    if (iar > 1 && iar < 3) {
                return fl | X_MASK1 | V_MASK;
	    }
	    if (iar >= 3) {
                return NO_MORE;
	    }
	    if (last == 0x58 || last == 0x78 ||   // X/x
                    last == 0x4c || last == 0x6c || // L/l
		    last == 0x43 || last == 0x63) { // C/c
                return (fl & X_MASK0) | C_MASK1 | L_MASK;
	    }
	    return C_MASK1 | L_MASK;
        // V/v
	case 0x56:
        case 0x76:
	    if (last == 0x49 || last == 0x69) { // I/i
                return NO_MORE;
	    }
	    return fl | C_MASK1 | L_MASK | X_MASK1 | V_MASK;
	// X/x
	case 0x58:
        case 0x78:
	    if (last == 0x49 || last == 0x69) { // I/i
                return NO_MORE;
	    }
	    if (last == 0x4c || last == 0x6c) { // L/l
                return fl & C_MASK1 | L_MASK;
	    } 
	    if (iar > 1 && iar < 3) {
                return fl | C_MASK1 | L_MASK;
	    }
            if (iar >= 3) {
                return fl | X_MASK1;
	    }
	    if (last == 0x43 || last == 0x63) {  // C/c
                return fl & C_MASK0;
	    }
            return C_MASK1;
        // L/l
	case 0x4c:
	case 0x6c:
            if (last == 0x58 || last == 0x78) { // X/x
                return fl | C_MASK1 | L_MASK | X_MASK1;
	    }
	    return fl | C_MASK1 | L_MASK;
        // C/c
	case 0x43:
        case 0x63:
            if (last == 0x58 || last == 0x78) { // X/x
                return fl | C_MASK1 | L_MASK | X_MASK1;
	    }
	    if (iar >= 3) {
                return fl | C_MASK1;
	    }
	    break;
        default:
	    std::cerr << WARNING << std::endl;
	    return NO_MORE;
    }

    return fl;
}
