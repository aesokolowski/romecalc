#include "../include/utilities.h"
#include <cstring>

bool is_numeric(const char *str)
{
   size_t i = 0;
   char next = *str;

   while (next != '\0') {
       if (next < 48 || next > 57) return false;
       else                        next = *(++i + str);
   }

   return true;
}
