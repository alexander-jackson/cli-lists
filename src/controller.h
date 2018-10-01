#ifndef CONTROLLER_H
#define CONTROLLER_H

// Given a char* command to run, decide the function to run and
// call it with the given arguments argc and argv
void run_command(char*, int, char**);

// Given a list name, create the list and add it to the file
void create_list(int, char**);

// Given a list name and an item text, append the given item
// text to the appropriate list
void append_item(int, char**);

// Given either nothing or a name of a list, if nothing then
// display all the lists in the file, otherwise the specific
// one that the user asked for
void display_lists(int, char**);

// Given the name of a list, delete the list entirely
void delete_list(int, char**);

// Given the name of a list and the name of an item within the
// list, remove that item
void remove_item(int, char**);

// Given the current name of a list and the desired name for it,
// rename the list in the file
void rename_list(int, char**);

#endif
