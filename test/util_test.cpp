#include "../include/utilities.h"
#include "../include/UserNum.h"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 1) {
        std::cerr << "Provide a string to test." << std::endl;
        return 1;
    }

    if (argc > 2) {
        std::cerr << "Too many arguments." << std::endl;
	return 1;
    }

    UserNum user_num(argv[1]);

    std::cout << "Test 1: is_numeric(UserNum): " << is_numeric(user_num)
         << std::endl;
    std::cout << "Test 2: is_roman(UserNum): " << is_roman(user_num)
         << std::endl;
    std::cout << "Test 3: check_xvi(UserNum): "
	      << check_xvi(user_num) << std::endl;

    return 0;
}
