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
	} else if (!strcmp(command, "add")) {
		add_item(argc, argv);
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
	free_list_pointer_array(lists);

	// Free the output of read_file
	free(lines);
}

void add_item(int argc, char** argv) {
	// Query should be ./list add {list name} ...
	// ... is the item they wish to add
	char* list_name = argv[2];
	char* item_text = join(argv, 3, argc, ' ');

	// Check that the item_text exists
	if (item_text[0] == '\0') {
		fputs("You cannot enter a string of length 0.\n", stderr);
		free(item_text);
		exit(1);
	}

	// Read the contents of the file
	char* lines = read_file("output.toml");
	// Parse the file
	struct List** lists = parse_file(lines);

	// Find the list with the name the user has specified
	int pos = 0;

	while (1) {
		if (lists[pos] == NULL) {
			pos = -1;
			break;
		}

		if (!strcmp(lists[pos]->title, list_name)) {
			break;
		}

		++pos;
	}

	// If pos == -1 then the list wasn't found
	if (pos == -1) {
		fprintf(stderr, "The list '%s' was not found within the file.\n", list_name);
		free(item_text);
		free(lines);
		free_list_pointer_array(lists);
		exit(1);
	}

	// Get the list pointer
	struct List* to_update = lists[pos];

	// Reallocate memory and update the list
	size_t item_count = to_update->item_count;
	to_update->items = realloc(to_update->items, sizeof(char*) * (item_count + 2));
	// Null terminate the items
	to_update->items[item_count + 1] = NULL;
	// Add the new item
	to_update->items[item_count] = item_text;

	// Write to the new file
	write_file("output.toml", lists);

	// Free the file lines
	free(lines);

	// Free the list pointers
	free_list_pointer_array(lists);
}
