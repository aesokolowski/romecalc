#include "../include/converters.h"
#include "../include/UserNum.h"
#include <cstring>
#include <iostream>
#include <vector>

char * dec_to_rn(UserNum un)
{
    char *str = new char[128];
    char unit1[2];
    char unit2[2];
    int size = un.get_count();
    int digit = 0;
    std::vector<char> uv = un.get_unv();

    strcpy(str, "");
    strcpy(unit1, "I");
    strcpy(unit2, "V");
 
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
            default:
              /*  throw exception? might just print a message and call it a
                  day   */
                strcat(str, "This option is not yet completed.");;
        }

        //digit++;   put back in when adding 10s place
    }

    return str;
}
