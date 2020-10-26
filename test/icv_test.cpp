#include "../include/utilities.h"
#include <cstring>
#include <iostream>

//  simple testing for is_current_value helper function in utilities

int main(int argc, char **argv)
{
    if (argc < 3) {
        std::cerr << "Provide flag and character to test.\n"
		  << "./testme [flag bits] [roman numeral character]\n"
		  << "Example:\n./testme 110 x --> false\n./testme 001 x --> "
		  << "true" << std::endl;
	return 1;
    }

    if (argc > 3) {
        std::cerr << "Too many arguments." << std::endl;
	return 1;
    }

    //  check valid flag, for now length = 3:
    char *c_fl = argv[1];
    size_t len = strlen(c_fl);
    if (len != 3) {
        std::cerr << "Current flag length must be 3." << std::endl;
	return 1;
    }

    std::cout << "No errors!" << std::endl;

    return 0;
}
