#include "../include/converters.h"
#include "../include/UserNum.h"
#include <cstring>
#include <vector>

char *dec_to_rn(UserNum un)
{
    // TODO I'm going to want to use globals for at least the top bunch, need
    // to brush up on my extern-foo
    const size_t MAX_BUFF = 128,
	         SMALL_BUFF = 2,
		 MAX_CAT = 63;
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
    const char *CHAR_CHANGE_ERR = "ERROR: cannot handle input more than 4 digits long.",
	       *ILL_DIG_ERR =     "INTERNAL ERROR: illegal character detected, please report to dev.";

    char *last = new char[MAX_BUFF];
    char str[MAX_BUFF];
    char unit1[SMALL_BUFF];
    char unit2[SMALL_BUFF];
    char unit3[SMALL_BUFF];
    
    size_t size = un.get_count();
    size_t digit = 0;
    std::vector<char> uv = un.get_unv();

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
        bool breaker = false;

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

//  may help to identify groups, to map to decimal numbers i.e.
//  XXXIX = 39   XXX = 30  IX = 9
//  XXVIII = 28  XX = 20 VIII = 8
//
//  Next step would simply be to add them up and sprintf the result to a
//  string buffer and return it.
//
//  Before bothering to identify groups, I may just add up the numbers
//  with a lookahead to switch I to -1 if followed by a V or X, and simply
//  add everything up.
//  So XXXIV -> 1. 10, 2. 20, 3. 30, 4. 29, 5. 34
//  IX -> 1. -1 2. 9
char *rn_to_dec (UserNum un)
{
    const size_t MAX_BUFF = 128;
    size_t count = un.get_count();
    int lc = count - 1; // last char
    int sum = 0;

    // temp, obvs:
    char *dummy = new char[MAX_BUFF];
    strncpy(dummy, "TODO", MAX_BUFF - 1); 
    return dummy;
}
