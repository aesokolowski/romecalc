# Roman Numeral converter/calculator tool for command line (C++)

compiles, runs as expected on both my Mac and Windows 10 machines... for now...

targets:

1. clean up current code (save literals other than 1, 0 -1 in constants kind of stuff)
2. errors for inputting an argument that is not implemented yet (so anything other than a decimal integer between 0 - 3999 inclusive)
3. a function to determine if a string containing valid Roman numeral characters has them in the correct order (I also think the max is 15 characters long for 3888) and another function to actually parse it, I feel making multiple passes helps
modularize the the code for future changes
4. help menu

future:

support different bases (especially for Arabic numerals), expand for list of arguments, Roman fractions


doesn't even do as advertised yet -- works the easy way, 0 - 3999 base-10 Arabic numerals to Roman numerals

compile (GNU):

g++ src/*.cpp -o rocal

run:

./rocal [base-10 Arabic integer]

tests:

g++ test/*.cpp src/utilities.cpp src/UserNum -o testme

./testme [string to test]
