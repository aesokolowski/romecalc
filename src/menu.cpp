#include "../include/menu.h"
#include <iostream>

const char *MSG_0_ARGS = "Please provide an argument.\n";
const char *TOO_MANY_ARGS = "Too many arguments... for now...\n";

void initial(int argc, char **argv)
{
  switch (argc) {
    case 1:
      std::cout << MSG_0_ARGS << std::endl;
      break;
    case 2:
      std::cout << "You entered: " << *(argv + 1) << ".\n" << std::endl;
      break;
    default:
      std::cout << TOO_MANY_ARGS << std::endl;
  }

  return;
}
