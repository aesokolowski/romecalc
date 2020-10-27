#include "../include/converters.h"
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

    std::cout << "Test 1: dec_to_rn(UserNum): ";
    char *result = dec_to_rn(user_num);
    std::cout << result << std::endl;
    delete result; result = NULL;

    return 0;
}
