#include "../include/converters.h"
#include "../include/UserNum.h"
#include <cstring>
#include <vector>

char *dec_to_rn(UserNum un)
{
    const size_t MAX_BUFF = 128,
	         SMALL_BUFF = 2;
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

    char *last = new char[MAX_BUFF];
    char str[MAX_BUFF];
    char unit1[SMALL_BUFF];
    char unit2[SMALL_BUFF];
    char unit3[SMALL_BUFF];
    
    int size = un.get_count();
    int digit = 0;
    std::vector<char> uv = un.get_unv();

    strcpy(str, EMPTY);
    strcpy(last, EMPTY);
    strcpy(unit1, AYE);
    strcpy(unit2, VEE);
    strcpy(unit3, EX);
 
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
    for (int i = size - 1; i >= 0; i--) {  // maybe should go backwards?
        //  switch statement to change characters  TODO *******
        switch (digit++) {
            case 0:
                /*  do nothing */
                break;
            case 1:
                strcpy(unit1, EX);
                strcpy(unit2, EL);
                strcpy(unit3, CEE);
                break;
            case 2:
                strcpy(unit1, CEE);
                strcpy(unit2, DEE);
                strcpy(unit3, EM);
                break;
            case 3:
                strcpy(unit1, EM);
                strcpy(unit2, UNKNOWN_5000);
                strcpy(unit3, UNKNOWN_10000);
            default:
                /*  do nothing for now TODO error message */
                break;
        }

        //  switch to distribute characters
        switch (uv[i]) {
            case 0x30:   // 0
                /*  do nothing */
                break;
            case 0x33:   // 3
                strcat(str, unit1);
                /**   FALLTHROUGH  **/
            case 0x32:   // 2
                strcat(str, unit1);
                /**   FALLTHROUGH  **/
            case 0x31:   // 1
                strcat(str, unit1);
                break;
            case 0x34:   // 4
                strcat(str, unit1);
                /**   FALLTHROUGH  **/
            case 0x35:   // 5
                strcat(str, unit2);
                break;
            case 0x36:   // 6
                strcat(str, unit2);
                strcat(str, unit1);
                break;
            case 0x37:   // 7
                strcat(str, unit2);
                strcat(str, unit1);
                strcat(str, unit1);
                break;
            case 0x38:   // 8
                strcat(str, unit2);
                strcat(str, unit1);
                strcat(str, unit1);
                strcat(str, unit1);
                break;
            case 0x39:   // 9
                strcat(str, unit1);
                strcat(str, unit3);
                break;
            default:
              /*  throw exception? might just print a message and call it a
                  day   */
                strcat(str, "This option is not yet completed.");
        }

        strcat(str, last);
        strcpy(last, str);
        strcpy(str, EMPTY);
    }

    return last;
}
