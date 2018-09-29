#ifndef LISTS_CONFIG_H
#define LISTS_CONFIG_H

extern char* DEFAULT_FILEPATH;
extern char* VERSION_NUMBER;

// Allocates and gets the default filepath for the program to write lists
// to in ~/.local/share/cli-lists/lists.toml
char* get_default_filepath();

// Executes the functions required to setup external variables defined in
// this file
void setup();

#endif
