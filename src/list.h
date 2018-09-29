#ifndef LIST_H
#define LIST_H

// Define a list structure as having a title, an array of char* items
// and a length such that len(items) == item_count
typedef struct List {
	char* title;
	char** items;
	size_t item_count;
} List;

// Define the operations on the list

// Given a list structure, free all elements of the list struct as well
// as the pointer to the list itself
void free_list(struct List*);

// Given a pointer to an array of list pointers, iterate through and
// free all the lists, along with the pointer to the array
void free_list_pointer_array(struct List**);

// Given a list structure, display the list structure to standard
// output with formatting
void display_list(struct List*);

#endif
