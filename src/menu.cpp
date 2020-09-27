#include "../include/menu.h"
#include "../include/UserNum.h"
#include <iostream>

const char *MSG_0_ARGS = "Please provide an argument.\n";
const char *TOO_MANY_ARGS = "Too many arguments... for now...\n";

/*  changes: I honestly don't think I'm going to need to go out of this scope,
    so I can probably stick user_vector on the stack (and rename it to
    user_num) since there's no main loop or anything... more importantly --
    the scope should probably also be limited to the case blocks
*/

/*  eventual scheme:
    0 arg provided:
        message on how to access help menu

    1 arg provided:
        rocal 3
           III
        rocal III
           3
        rocal -h
        rocal --help
           help menu

    2 args or more provided:
    3 and more args will probably be processed using some sort of loop
    wonder if it will be beneficial to limit 2 args to its own case block
    if I can think of options that require only 2 or more

    change base:
        rocal --base 2 11
        rocal -b 2 11
            III
        rocal -b 2 III
            11
    add:
        rocal -a 4 6
            X
        rocal -a 4 6 9
            XIX
    convert list:
        rocal 1 2 3 4 5
            I II III IV V
        rocal I II III IV V
            1 2 3 4 5
*/

void initial(int argc, char **argv)
{
  UserNum *user_vector = new UserNum(*(argv + 1));

  switch (argc) {
    case 1:
      std::cout << MSG_0_ARGS << std::endl;
      break;
    case 2:
      std::cout << "You entered: " << *(argv + 1) << ".\n";
      break;
    default:
      std::cout << TOO_MANY_ARGS << std::endl;
  }

  delete user_vector;
  return;
}
