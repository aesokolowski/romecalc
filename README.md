# Roman Numeral converter/calculator tool for command line (C++)

compiles, runs as expected on both my Mac and Windows 10 machines... for now...

targets:

**** since the last attempt at parsing given roman numerals had a very clear bug, I'm going to  rewrite the function to validate proper order of Roman numerals. Still left-to-right, but will have more flags to keep track, and will build incrementally my first test ****

1. errors for inputting an argument that is not implemented yet (so anything other than a decimal integer between 0 - 3999 inclusive)
2. a function to determine if a string containing valid Roman numeral characters has them in the correct order (I also think the max is 15 characters long for 3888) and another function to actually parse it, I feel making multiple passes helps modularize the the code for future changes
3. actually parsing the number from a known valid string
4. learn optget and implement it
5. help menu

future:

support different bases (especially for Arabic numerals), expand for list of arguments, Roman fractions


doesn't even do as advertised yet -- works the easy way, 0 - 3999 base-10 Arabic numerals to Roman numerals but even that can't be piped or inserted (Mac) because the file/program will just take "Too many arguments."

compile (GNU):

g++ src/*.cpp -o rocal

run:

./rocal [base-10 Arabic integer]

tests:

g++ test/*.cpp src/utilities.cpp src/UserNum -o testme

./testme [string to test]

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

2. don't really see a reason to use std::string for this program, the only thing I really dislike about cstrings is that long literals have no choice but to spill over to the next line but I try to stick them all in consts in one specific section anyway to not uglify the whole file.
