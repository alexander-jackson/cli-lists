#ifndef LIST_H
#define LIST_H

typedef struct List {
	char* title;
	char** items;
	size_t item_count;
} List;

// Define the operations on the list

void free_list(struct List*);

void free_list_pointer_array(struct List**);

void display_list(struct List*);

#endif
