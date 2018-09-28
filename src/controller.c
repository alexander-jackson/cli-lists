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
	if (!strcmp(command, "create")) {
		create_list(argc, argv);
	} else if (!strcmp(command, "append")) {
		append_item(argc, argv);
	} else if (!strcmp(command, "display")) {
		display_lists(argc, argv);
	} else if (!strcmp(command, "delete")) {
		delete_list(argc, argv);
	} else if (!strcmp(command, "remove")) {
		remove_item(argc, argv);
	}
}

void create_list(int argc, char** argv) {
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

void append_item(int argc, char** argv) {
	// Query should be ./list append {list name} ...
	// ... is the item they wish to append
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

void display_lists(int argc, char** argv) {
	// Read the file
	char* lines = read_file("output.toml");
	// Parse it
	struct List** lists = parse_file(lines);

	// Check the value of argc
	if (argc <= 2) {
		for (size_t i = 0; lists[i] != NULL; ++i) {
			display_list(lists[i]);
		}
	} else {
		// Get the name of the list
		char* list_name = argv[2];

		// Iterate through the list and see if we find it
		int found = 0;

		for (size_t i = 0; lists[i] != NULL; ++i) {
			if (!strcmp(lists[i]->title, list_name)) {
				// Display this list
				display_list(lists[i]);
				// Set the value of found
				found = 1;
			}
		}

		// If we didn't find the list then complain
		if (!found) {
			fprintf(stderr, "Couldn't find the list by the name of '%s'.\n", list_name);
		}
	}

	// Cleanup the memory
	free(lines);
	free_list_pointer_array(lists);
}

void delete_list(int argc, char** argv) {
	if (4 <= argc) {
		printf("Ignoring arguments past number 4.\n");
	}

	// Read the file
	char* lines = read_file("output.toml");
	// Parse the file
	struct List** lists = parse_file(lines);
	// Find the list by name
	char* list_title = argv[2];
	int pos = -1;

	for (size_t i = 0; lists[i] != NULL; ++i) {
		if (!strcmp(lists[i]->title, list_title)) {
			pos = i;
		}
	}

	if (pos == -1) {
		// We didn't find the list
		fprintf(stderr, "The list '%s' does not exist.\n", list_title);
		free(lines);
		free_list_pointer_array(lists);
		exit(1);
	}

	// Free the element at pos
	free_list(lists[pos]);
	lists[pos] = NULL;
	// Move all the lists back
	for (size_t i = (size_t) pos; lists[i + 1] != NULL; ++i) {
		lists[i] = lists[i + 1];
	}

	// Now write all the elements to the file
	write_file("output.toml", lists);

	// Perform the cleanup operations
	free(lines);
	free_list_pointer_array(lists);
}

void remove_item(int argc, char** argv) {
	// Check they entered enough parameters
	if (argc <= 3) {
		fprintf(stderr, "Please enter a list to delete from and the name of the item.\n");
		fprintf(stderr, "The following format is used: lists remove {title} {item}\n");
		exit(1);
	}

	// Get the list title
	char* list_title = argv[2];
	// Get the item text
	char* item_text = join(argv, 3, argc, ' ');

	// Read the file and then parse it
	char* lines = read_file("output.toml");
	struct List** lists = parse_file(lines);

	// Find the list that this item belongs to
	int list_pos = -1;

	for (size_t i = 0; lists[i] != NULL; ++i) {
		if (!strcmp(lists[i]->title, list_title)) {
			list_pos = i;
		}
	}

	if (list_pos == -1) {
		fprintf(stderr, "The following list title was not found: '%s'\n", list_title);
		free(item_text);
		free(lines);
		free_list_pointer_array(lists);
		exit(1);
	}

	// Get the pointer to the list we found
	struct List* to_update = lists[list_pos];
	// Get the position of the item
	int item_pos = -1;

	for (size_t i = 0; i < to_update->item_count; ++i) {
		if (!strcmp(to_update->items[i], item_text)) {
			item_pos = i;
		}
	}

	if (item_pos == -1) {
		fprintf(stderr, "While the list '%s' exists, the item '%s' is not within it.\n", list_title, item_text);
		free(item_text);
		free(lines);
		free_list_pointer_array(lists);
		exit(1);
	}

	// Free the item and set it to NULL, then move everything back
	free(to_update->items[item_pos]);
	to_update->items[item_pos] = NULL;

	for (size_t i = item_pos; to_update->items[i + 1] != NULL; ++i) {
		to_update->items[i] = to_update->items[i + 1];
	}

	// Write the file
	write_file("output.toml", lists);

	// Free everything
	free(item_text);
	free(lines);
	free_list_pointer_array(lists);
}
