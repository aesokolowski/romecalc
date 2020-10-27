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
    char *res1 = dec_to_rn(user_num);
    std::cout << res1 << std::endl;
    delete res1; res1 = NULL;
    std::cout << "Test 2: rn_todec(UserNum): ";
    char *res2 = rn_to_dec(user_num);
    std::cout << res2 << std::endl;
    delete res2; res2 = NULL;

    return 0;
}
