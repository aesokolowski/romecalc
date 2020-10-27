# Roman Numeral converter/calculator tool for command line (C++)

So far just a converter. Arabic to Roman up to 4 digits:

rocal 1 -> I

rocal 45 -> XLV

rocal 3999 -> MMMCMXCIX

Arabic numerals 4000 - 9999 will give output, but ? is used to represent 5000 and ! is used to represent 10000.

rocal 4500 -> M?D

rocal 9000 -> M!

Roman numeral to Arabic decimal partially implemented. Parses I, V and X for now (1-39). Implementing L and C next, then D and M.

rocal i -> 1
rocal xx -> 20
rocal xxxiv -> 34

targets:

1. check Mac (*nix?) compatibility and write bash scripts for compilation

2. scale up Roman-to-Arabic function incrementally

3. fix pipe / redirect issue

4. implement optget-long (argument parser) and add help menu

5. calculator functions

6. multiple bases for Arabic numerals

COMPILATION:

my scripts use g++ (GNU) and are intended to be run from the root directory:

compile program (Windows):

.\scripts\x64comp.ps1

run:

.\rocal [Arabic or Roman numeral]

compile tests (Windows):

.\scripts\x64test.ps1

outputs multiple test programs that accept arguments. Windows sticks a .exe at the end of the file but you don't need to include it:

.\testutils [arabic or Roman numerals]

.\testconvs [arabic or Roman numerals]

.\testicv [bitfield] [character]

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

2. don't really see a reason to use std::string for this program. User input is represented as a vector of chars internally. Also I'm more familiar with the <cstring> library than <string> since I've done more C lately than C++.