#ifndef UTILITIES
#define UTILITIES

#include "UserNum.h"

// needed: is_standard, is_roman only checks for the particular letters,
// not if they're in standard format (as we recognize in 21st century)

bool is_numeric(UserNum);
bool is_roman(UserNum);

#endif //UTILITIES
