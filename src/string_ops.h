#ifndef STRING_OPS_H
#define STRING_OPS_H

// Define the operations on strings

// Given a string and 2 positions in the string, return the substring on
// the interval [a, b)
char* substring(char*, size_t, size_t);

// Given a string and a delimiter, return the string split at each
// delimiter
char** split(char*, unsigned char);

// Given an input string and a string containing characters to remove,
// return the string cleaned of all these chars
char* clean(char*, char*);

// Given a string array, a start, an end and a char, return the
// joining of the strings between [s, e), with the char separating them
char* join(char**, size_t, size_t, unsigned char);

#endif
