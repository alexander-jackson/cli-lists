#ifndef STRING_OPS_H
#define STRING_OPS_H

// Define the operations on strings

char* substring(char*, size_t, size_t);

char** split(char*, unsigned char);

char* clean(char*, char*);

char* join(char**, size_t, size_t, unsigned char);

#endif
