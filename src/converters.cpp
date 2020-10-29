#include "../include/constants.h"
#include "../include/converters.h"
#include "../include/UserNum.h"
#include <cstdio>
#include <cstring>
#include <iostream> // debug?
#include <vector>

char *dec_to_rn(UserNum un)
{
    const char *EMPTY         = "",
	       *AYE           = "I",
	       *VEE           = "V",
	       *EX            = "X",
	       *EL            = "L",
	       *CEE           = "C",
	       *DEE           = "D",
               *EM            = "M",
	       *UNKNOWN_5000  = "?",
	       *UNKNOWN_10000 = "!";
    const char *CHAR_CHANGE_ERR = "ERROR: Decimal Arabic numerals input limited to 4 digits (max standard Roman numerals is 3999).",
	       *ILL_DIG_ERR =     "INTERNAL ERROR: illegal character detected, please report to dev.";

    char *last = new char[MAX_BUFF];
    char str[MAX_BUFF];
    char unit1[SMALL_BUFF];
    char unit2[SMALL_BUFF];
    char unit3[SMALL_BUFF];
    
    size_t size = un.get_count();
    size_t digit = 0;
    std::vector<char> uv = un.get_unv();
    bool breaker = false;

    strncpy(str, EMPTY, MAX_BUFF);
    strncpy(last, EMPTY, MAX_BUFF);
    strncpy(unit1, AYE, SMALL_BUFF);
    strncpy(unit2, VEE, SMALL_BUFF);
    strncpy(unit3, EX, SMALL_BUFF);
 
    //  remember to fill out case statement for each digit 0 - 9
    //  0 -- do
    //  1 -- I
    //  2 -- II
    //  4 -- IV
    //  etc
    //  for the next pass need to switch
    //  0 -- do nothing
    //  1 -- X
    //  2 -- XX
    //  4 -- XL
    //  etc
    //  up until 4 thousand, at least for now
    for (int i = size - 1; i >= 0; i--) {
        //  switch statement to change characters
        switch (digit++) {
            case 0:
                /*  do nothing */
                break;
            case 1:
                strncpy(unit1, EX, SMALL_BUFF);
                strncpy(unit2, EL, SMALL_BUFF);
                strncpy(unit3, CEE, SMALL_BUFF);
                break;
            case 2:
                strncpy(unit1, CEE, SMALL_BUFF);
                strncpy(unit2, DEE, SMALL_BUFF);
                strncpy(unit3, EM, SMALL_BUFF);
                break;
            case 3:
                strncpy(unit1, EM, SMALL_BUFF);
                strncpy(unit2, UNKNOWN_5000, SMALL_BUFF);
                strncpy(unit3, UNKNOWN_10000, SMALL_BUFF);
		break;
            default:
		breaker = true;
                strncpy(last, CHAR_CHANGE_ERR, MAX_BUFF); 
        }

	if (breaker) break;

        //  switch to distribute characters
        switch (uv[i]) {
            case 0x30:   // 0
                /*  do nothing */
                break;
            case 0x33:   // 3
                strncat(str, unit1, MAX_CAT);
                /**   FALLTHROUGH  **/
            case 0x32:   // 2
                strncat(str, unit1, MAX_CAT);
                /**   FALLTHROUGH  **/
            case 0x31:   // 1
                strncat(str, unit1, MAX_CAT);
                break;
            case 0x34:   // 4
                strncat(str, unit1, MAX_CAT);
                /**   FALLTHROUGH  **/
            case 0x35:   // 5
                strncat(str, unit2, MAX_CAT);
                break;
            case 0x36:   // 6
                strncat(str, unit2, MAX_CAT);
                strncat(str, unit1, MAX_CAT);
                break;
            case 0x37:   // 7
                strncat(str, unit2, MAX_CAT);
                strncat(str, unit1, MAX_CAT);
                strncat(str, unit1, MAX_CAT);
                break;
            case 0x38:   // 8
                strncat(str, unit2, MAX_CAT);
                strncat(str, unit1, MAX_CAT);
                strncat(str, unit1, MAX_CAT);
                strncat(str, unit1, MAX_CAT);
                break;
            case 0x39:   // 9
                strncat(str, unit1, MAX_CAT);
                strncat(str, unit3, MAX_CAT);
                break;
            default:
                breaker = true; 
                strncpy(last, ILL_DIG_ERR, MAX_BUFF - 1);
        }

        if (breaker) break;

        strncat(str, last, MAX_CAT);
        strncpy(last, str, MAX_BUFF - 1);
        strncpy(str, EMPTY, MAX_BUFF - 1);
    }

    return last;
}

//  Add up each character encountered, with the "lookahead exception" for
//  I (can be followed by V or X) in which case it adds -1 instead of 1.
//  Obviously this concept will have to be expanded to X when I add L and
//  C (and then D and M) to the pile.
//
//  As with dec_to_rn this function depends on previous passes through
//  validators in order to work. As noted in other comments throughout the
//  code, I chose to make multiple passes over given strings for modularity
//  and because the strings aren't terribly long to begin with (not
//  withstanding the crazy idea of adding custom Roman Numerals in order to
//  use larger numbers, but for that I'd prefer a switch to enable "interactive
//  mode" [read: menu/loop-based] instead of using command line arguments).
//
//  So XXXIV -> 1. 10, 2. 20, 3. 30, 4. 29, 5. 34
//  IX -> 1. -1 2. 9
char *rn_to_dec (UserNum un)
{
    size_t count = un.get_count();
    std::vector<char> uv = un.get_unv();
    int lc = count - 1; // last char
    int sum = 0;

    char *result = new char[MAX_BUFF];

    for (size_t i = 0; i < count; i++) {
	int value;

        switch (uv[i]) {
	    case 0x49: // I/i
            case 0x69:
		value = 1;
                if (i < lc) {
		    char la = uv[i + 1]; // lookahead
                    if (la == 0x56 || la == 0x76 || la == 0x58 || la == 0x78) {
                        value = -1;
		    }
		} 
		sum += value;
		break;
	    case 0x56:  // V/v
	    case 0x76:
	        sum += 5;
		break;
            case 0x58:  // X/x
	    case 0x78:
		value = 10;
		if (i < lc) {
                    char la = uv[i + 1]; // lookahead
	            if (la == 0x4c || la == 0x6c || la == 0x43 || la == 0x62) {
                        value = -10;
		    }
		}
		sum += value;
		break;
	    case 0x4c:  // L/l
	    case 0x6c:
		sum += 50;
		break;
	    case 0x43:  // C/c
	    case 0x63:
		sum += 100;
		break;
            default:
		std::cerr << "lol hit default" << std::endl; // TODO: lift and professionalize
	}
    }

    sprintf(result, "%d", sum);
 
    return result;
}
