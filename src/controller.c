#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller.h"
#include "string_ops.h"
#include "file_io.h"
#include "list.h"
#include "lists_config.h"

void run_command(char* command, int argc, char** argv) {
	// Check which command to run
	if (!strcmp(command, "new")) {
		new_list(argc, argv);
	}
}

void new_list(int argc, char** argv) {
	// Get the name of the list to add
	char* list_title = join(argv, 2, argc, ' ');
	// Display the name of the list
	printf("Attempting to add a list by the name of '%s'\n", list_title);

	// Read the contents of the file
	char* lines = read_file("output.toml");
	// Parse the file
	struct List** lists = parse_file(lines);

	// Count the number of lists so far
	size_t list_count = 0;
	while (lists[list_count] != NULL)
		++list_count;

	// Reallocate space, including the new list and NULL pointer
	lists = realloc(lists, sizeof(struct List*) * (list_count + 2));

	// Create a new list and set the information
	struct List* new_list = malloc(sizeof(struct List));
	new_list->title = list_title;
	new_list->items = malloc(sizeof(char*));
	new_list->items[0] = NULL;
	new_list->item_count = 0;

	// Add this to the lists
	lists[list_count] = new_list;

	// Move the NULL pointer
	lists[list_count + 1] = NULL;

	// Write the contents to a new file
	write_file("output.toml", lists);

	// Free all the lists
	for (size_t i = 0; lists[i] != NULL; ++i) {
		free_list(lists[i]);
	}

	// Free the pointer to lists
	free(lists);

	// Free the output of read_file
	free(lines);
}
