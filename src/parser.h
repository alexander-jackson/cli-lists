#ifndef PARSER_H
#define PARSER_H

int next_instance_of(unsigned char, char*, size_t);
char* substring(char*, size_t, size_t);
char** split(char*, unsigned char);
char* clean(char*, char*);

struct List* extract_list(char*, size_t, size_t);
struct List** parse_file(char*);

#endif // PARSER_H
