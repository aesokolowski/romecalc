#ifndef UTILITIES
#define UTILITIES

#include "UserNum.h"

// needed: is_standard, is_roman only checks for the particular letters,
// not if they're in standard format (as we recognize in 21st century)
//
// functions that are useless to call from outside are labeled helper,
// they'd be private if contained inside a class

bool is_numeric(UserNum);
bool is_roman(UserNum);

/*  removed for now
bool is_valid_roman(UserNum);
bool m_check(char, size_t *);  // helper
bool c_check(char, size_t *);  // helper
*/

// temp, may be expanded into actual is_valid_roman or rewritten:
bool check_xvi(UserNum);

#endif //UTILITIES
