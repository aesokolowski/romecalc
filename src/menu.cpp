#include "../include/converters.h"
#include "../include/menu.h"
#include "../include/UserNum.h"
#include "../include/utilities.h"
#include <cstring>
#include <iostream>

/*  eventual scheme:
    0 arg provided:
        message on how to access help menu

    1 arg provided:
        rocal 3
           III
        rocal III
           3
        rocal -h
        rocal --help
           help menu

    2 args or more provided:
    3 and more args will probably be processed using some sort of loop
    wonder if it will be beneficial to limit 2 args to its own case block
    if I can think of options that require only 2

    change base:
        rocal --base 2 11
        rocal -b 2 11
            III
        rocal -b 2 III
            11
    add:
        rocal -a 4 6
            X
        rocal -a 4 6 9
            XIX
    convert list:
        rocal 1 2 3 4 5
            I II III IV V
        rocal I II III IV V
            1 2 3 4 5
*/

void initial(int argc, char **argv)
{
    const size_t MAX_BUFF = 128;
    const char *MSG_0_ARGS = "Please provide an argument.",
	       *INVALID_INPUT = "Input must be a positive decimal integer in Arabic numerals or standard Roman Numerals.",
               *TOO_MANY_ARGS = "Too many arguments... for now...";


    // this will need to be replaced by an argument parser when I move on
    // to more than one argument and start adding switches but for now,
    // let's just assume the first argument is either Arabic decimal or
    // Roman numeral to be converted to the other
    UserNum user_num(argv[1]);
    char *solution;

    switch (argc) {
        case 1:
            solution = new char[MAX_BUFF];
            strncpy(solution, MSG_0_ARGS, MAX_BUFF - 1);
            break;
        case 2:
	    if (is_numeric(user_num)) {
                solution = dec_to_rn(user_num);
	    } else if (is_roman(user_num) && check_xvi(user_num)) {
		solution = rn_to_dec(user_num);
	    } else {
	        solution = new char[MAX_BUFF];
                strncpy(solution, INVALID_INPUT, MAX_BUFF - 1);
	    }
            break;
        default:
            solution = new char[MAX_BUFF];
	    strncpy(solution, TOO_MANY_ARGS, MAX_BUFF - 1);
	    break;
    }

    if (solution) {
        std::cout << solution << std::endl;
        delete [] solution;
        solution = NULL;
    }

    return;
}
