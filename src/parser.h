#ifndef PARSER_H
#define PARSER_H

// Given a file split into lines and an index for the list beginning, count
// the number of elements in the list
size_t count_items(char**, size_t);

// Given a file split into lines and an index for the list beginning,
// extract the items in the list into an array of char*
char** get_list_items(char**, size_t);

// Given the output of read_file(), parse the file into an array of
// List structures
struct List** parse_file(char*);

#endif // PARSER_H
