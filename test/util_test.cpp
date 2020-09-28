#include "../include/utilities.h"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 1) {
      std::cout << "Provide a string to test.\n" << std::endl;
      return 1;
    }

    std::cout << "Test 1: is_numeric(const char *): " << is_numeric(argv[1])
         << std::endl;
    std::cout << "Test2: is_roman(const char *): " << is_roman(argv[1])
         << std::endl;

    return 0;
}
