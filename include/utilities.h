#ifndef UTILITIES
#define UTILITIES

#include "UserNum.h"

// functions that are useless to call from outside are labeled helper,
// they'd be private if contained inside a class

bool is_numeric(UserNum);
bool is_roman(UserNum);

/*  removed for now and probably forever
bool is_valid_roman(UserNum);
bool m_check(char, size_t *);  // helper
bool c_check(char, size_t *);  // helper
*/

// temp, may be expanded into actual is_valid_roman or rewritten:
bool check_xvi(UserNum);
bool is_current_valid(size_t, char); // helper
size_t set_flags(char); // helper, 1st char
size_t update_flags(size_t, char, char, size_t); // helper, other chars

#endif //UTILITIES
