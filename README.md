# Roman Numeral converter/calculator tool for command line (C++)

So far just a converter. Arabic to Roman up to 4 digits:

rocal 1 -> I

rocal 45 -> XLV

rocal 3999 -> MMMCMXCIX

Arabic numerals 4000 - 9999 will give output, but ? is used to represent 5000 and ! is used to represent 10000.

rocal 4500 -> M?D

rocal 9000 -> M!

Roman numeral to Arabic decimal partially implemented. Parses I, V, X, C and L for now (1-399). Implementing D and M next after doing a little more false-positive hunting for the current version.

rocal i -> 1

rocal xx -> 20

rocal xxxiv -> 34

targets:

1. scale up Roman-to-Arabic function incrementally

2. fix pipe / redirect issue

(at this point I think I'm going to start on a webapp, catch up to this program in function [converter], and then develop the two in parallel [calculator])

3. redesign base around optget-long (argument parser) and add help menu

4. calculator functions

5. multiple bases for Arabic numerals

-----------

COMPILATION:

All the following scripts use g++ (GNU) and are intended to be run from the root directory:

compile program (Windows Powershell):

.\scripts\x64comp.ps1

NOTE1: If you only have CMD, you can probably just change the extension to .cmd, there's no looping or anything. Or just copy/paste the whole g++ command from the file.

NOTE2: I do not believe Windows 10 or earlier comes with GCC, which g++ is a part of. I think I have at least two copies on my machine -- one came with the Haskell Platform and the other came with Cygwin. You don't need either of these things, just Google g++ or GCC (GNU Compiler Collection) and you should be able to snag a free copy. G++ is generally standard on Mac and *nix machines.

NOTE3: x64comp is a dumb name considering this should run on 32-bit systems. Maybe I should change it.

NOTE4: if you actually want to use the program no matter what directory you are in, you should add a function that calls it to your profile script and alias said function as rocal or romecalc or whatever.

Obviously if you're using Cygwin you should folow the *nix instructions.

run:

.\rocal [Arabic or Roman numeral]

-------------------------------------

compile program (*nix/MacOs bash):

./scripts/nixcomp.sh

or if you're like me and use a shell other than bash:

bash scripts/nixcomp.sh

run:

./rocal [Arabic or Roman numeral]

Better yet, if you're ditching the code after compilation and just using the executable, stick the executable (rocal) in a directory in your PATH like ~/usr/local/bin so you can call it from anywhere! If you want to keep the code I'd recommend using a symlink. Don't add the romecalc folder to your PATH, that's silly.

-------------------------------------

compile tests (Windows Powershell):

.\scripts\x64test.ps1

outputs multiple test programs that accept arguments. Windows sticks a .exe at the end of the file but you don't need to include it:

.\testutils [arabic or Roman numerals]

.\testconvs [arabic or Roman numerals]

.\testicv [bitfield] [Roman numeral character]

-------------------

compile tests (*nix/MacOs bash):

bash scripts/nixtest.sh

As for running the tests, same as Windows, just a forward slash instead of back slash after the dot.

----------

run batch tests example (Powershell only for now):

first run both the x64comp.ps1 and x64test.ps1 from project root, then run

.\scripts\batch\random_input_1-399

results can be viewed by opening rand1-399.txt that appears in project root

-----------------

Style Notes:

1. star spacing -- for simplicity's sake, I prefer to use uniform spacing regardless of an *'s purpose, I attach it to the right-hand-side

   return pointer:

   myType *myFunction(myType myArgument) {}

   passed pointer:

   myType myFunction(myType *myArgument) {}

   declare pointer:

   myType *myPointer;

   dereference pointer:

   *myPointer = myValue;

   myVariable = *myPointer

2. don't really see a reason to use std::string for this program. User input is represented as a vector of chars internally, no raw strings from arguments get strncpy'd or strncat'd. Also I'm more familiar with the <cstring> library than <string> since I've done more C lately than C++.

3. no throwing. design preference (for this particular program) of sequential calling of functions rather than calling functions from within functions to keep things "flat" favors avoiding exceptions. when I implement the "calculator" part I'll probably run into more exceptions (been lucky so far, but there's no exception for segfaults) but I want to catch immediately. For custom errors I just like to send a warning to stderr if the function doesn't return a string and overwrite the decimal or roman output with an error message if it does.

4. old skool c++: I'm aware of new features like auto and non-standard features like itoa but I prefer not to use them, especially in a simple program like this. I find explicitly-typed variables make code easier to read, and I see no reason for itoa when I have sprintf and I see no reason for itos when I have stringstream.

5. tons o' hex: old skool C++ doesn't support binary literals so hex is an obvious choice for bitstring logic because it's so easy to mentally convert into binary. As for the ASCII, I find the hex numbers easier to remember than the decimal (i.e. just add 20 to get lowercase)