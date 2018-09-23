#include "parser.h"

// Takes a char* filepath and returns a char* pointing 
// to the contents of the file in memory
char* read_file(char*);

// Takes a char* filepath and a pointer to an array of
// List pointers and writes them to the file
void write_file(char*, struct List**);

// Appends the given string to the given filepath
void append_file(char*, char*);
