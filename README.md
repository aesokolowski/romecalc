# Roman Numeral converter/calculator tool for command line (C++)

targets (in priority):

1. create UserNum class to hold the first argument, preferably a vector of
   individual digits. making a class so that it can be reused for adding etc
   features I plan to add later
2. create a function to convert a base-10 Arabic number to Roman numerals
3. rudimentary help menu (-h --help switch)

future:

reverse, support different bases (especially for Arabic numerals), expand for list of arguments, Roman fractions


doesn't even do as advertised yet

compile (GNU):

g++ src/*.cpp

run:

./a.out [argument]

tests:

g++ test/*.cpp src/utilities.cpp -o testme

./testme [string to test]
