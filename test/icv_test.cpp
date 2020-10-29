#include "../include/utilities.h"
#include <cstring>
#include <ios>
#include <iostream>

//  simple testing for is_current_valid helper function in utilities

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

    //  check valid flag, for now length = 5:
    char *c_fl = argv[1];
    size_t len = strlen(c_fl);
    if (len != 5) {
        std::cerr << "Current flag length must be 5." << std::endl;
	return 1;
    }

    //  make sure flag only consists of 1s and 0s
    for (size_t i = 0; i < len; i++) {
        if (c_fl[i] < 0x30 || c_fl[i] > 0x31) {
            std::cerr << "Flag can only have 1s and 0s, i.e. string of bits." << std::endl;
	    return 1;
	}
    }

    //  make sure second arg is only one character long
    char *c_ch = argv[2];
    size_t ch_len = strlen(c_ch);
    if (ch_len != 1) {
        std::cerr << "Second argument must have string length of 1." << std::endl;
	return 1;
    }
    
    //  make sure valid roman numeral (add more later as scaling up)
    char ch = c_ch[0];
    switch (ch) {
	case 0x49:
        case 0x69:
        case 0x56:
	case 0x76:
	case 0x58:
	case 0x78:
        case 0x4C:
	case 0x6C:
	case 0x43:
	case 0x63:
	    /*** do nothing ***/
	    break;
        default:
	    std::cerr << "Current valid list of characters for second argument"
		      << ":\nI i V v X x L l C c" << std::endl;
	    return 1;
    }

    //  convert flag to int
    int nf = 0,
	add = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (c_fl[i] == 0x31) nf += add;
	add *= 2;
    }

    //  display result of conversion
    std::cout << "Bit string: " << c_fl << "\nDecimal: " << nf << "\nHex: "
	      << std::hex << nf << std::dec << std::endl;   
    //  finally call function for test
    if (is_current_valid(nf, ch)) {
        std::cout << "is_current_valid returned true." << std::endl;
    } else {
        std::cout << "is_current_valid returned false." << std::endl;
    }

    return 0;
}
