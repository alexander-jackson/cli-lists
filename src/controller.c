#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller.h"
#include "parser.h"
#include "string_ops.h"
#include "file_io.h"
#include "list.h"
#include "lists_config.h"

void run_command(char* command, int argc, char** argv) {
	// Check which command to run
	if (strcmp(command, "create") == 0) {
		create_list(argc, argv);
	} else if (strcmp(command, "append") == 0) {
		append_item(argc, argv);
	} else if (strcmp(command, "display") == 0) {
		display_lists(argc, argv);
	} else if (strcmp(command, "delete") == 0) {
		delete_list(argc, argv);
	} else if (strcmp(command, "remove") == 0) {
		remove_item(argc, argv);
	} else if (strcmp(command, "rename") == 0) {
		rename_list(argc, argv);
	}
}

void create_list(int argc, char** argv) {
	// Check that the user entered enough arguments
	if (argc <= 2) {
		fprintf(stderr, "Please enter the name of the list you wish to create.\n");
		exit(1);
	}

	// Get the size of argv
	size_t title_len = strlen(argv[2]);
	// Allocate memory
	char* list_title = malloc(sizeof(char) * (title_len + 1));

	// Copy into the buffer
	strncpy(list_title, argv[2], title_len);

	// Allocate the null pointer
	list_title[title_len] = '\0';

	// Read the contents of the file
	char* lines = read_file(DEFAULT_FILEPATH);
	// Parse the file
	struct List** lists = parse_file(lines);
	// Free the lines we parsed earlier
	free(lines);

	// Count the number of lists so far and ensure the list name doesn't
	// already exist
	size_t list_count = 0;
	while (lists[list_count] != NULL) {
		if (strcmp(lists[list_count]->title, list_title) == 0) {
			// A list already exists with this name
			fprintf(stderr, "A list with the name '%s' already " \
					"exists.\n", list_title);
			free(list_title);
			free_list_pointer_array(lists);
			exit(1);
		}
		++list_count;
	}

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
	write_file(DEFAULT_FILEPATH, lists);

	// Free all the lists
	free_list_pointer_array(lists);
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
	char* lines = read_file(DEFAULT_FILEPATH);
	// Parse the file
	struct List** lists = parse_file(lines);
	// Free the lines
	free(lines);

	// Find the list with the name the user has specified
	int pos = -1;

	for (size_t i = 0; lists[i] != NULL; ++i) {
		if (strcmp(lists[i]->title, list_name) == 0) {
			pos = i;
			break;
		}
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

	// Check that the list doesn't already contain the item
	for (size_t i = 0; to_update->items[i] != NULL; ++i) {
		if (strcmp(to_update->items[i], item_text) == 0) {
			// This is a duplicate item
			fprintf(stderr, "The list '%s' already contains the "\
					"item '%s'.\n", list_name, item_text);
			free(item_text);
			free_list_pointer_array(lists);
			return;
		}
	}

	// Reallocate memory and update the list
	size_t item_count = to_update->item_count;
	to_update->items = realloc(to_update->items, sizeof(char*) * (item_count + 2));
	// Null terminate the items
	to_update->items[item_count + 1] = NULL;
	// Add the new item
	to_update->items[item_count] = item_text;

	// Write to the new file
	write_file(DEFAULT_FILEPATH, lists);

	// Free the list pointers
	free_list_pointer_array(lists);
}

void display_lists(int argc, char** argv) {
	// Read the file
	char* lines = read_file(DEFAULT_FILEPATH);
	// Parse it
	struct List** lists = parse_file(lines);
	// Free the lines we read from the file
	free(lines);

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
	free_list_pointer_array(lists);
}

void delete_list(int argc, char** argv) {
	// Check that the user entered enough parameters
	if (argc <= 2) {
		fprintf(stderr, "Please enter the name of the list you wish to delete.\n");
		exit(1);
	}

	// Read the file
	char* lines = read_file(DEFAULT_FILEPATH);
	// Parse the file
	struct List** lists = parse_file(lines);
	// Free the lines we read before
	free(lines);
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
	write_file(DEFAULT_FILEPATH, lists);

	// Perform the cleanup operations
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
	char* lines = read_file(DEFAULT_FILEPATH);
	struct List** lists = parse_file(lines);
	// Free the lines we read before
	free(lines);

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
	write_file(DEFAULT_FILEPATH, lists);

	// Free everything
	free(item_text);
	free_list_pointer_array(lists);
}

void rename_list(int argc, char** argv) {
	if (argc < 4) {
		fprintf(stderr, "Please enter the name of the list currently and what you would like to change it to.\n");
		fprintf(stderr, "Command format: lists rename {current} {desired}.\n");
		exit(1);
	}

	// Get the current name of the list
	char* current = argv[2];

	// Allocate argv[3] on the heap
	size_t desired_len = strlen(argv[3]);
	char* desired = malloc(sizeof(char) * (desired_len + 1));
	strncpy(desired, argv[3], desired_len);
	desired[desired_len] = '\0';

	// Read the file
	char* lines = read_file(DEFAULT_FILEPATH);
	// Parse the file
	struct List** lists = parse_file(lines);
	// Free the lines we read earlier
	free(lines);

	// Search through the list and try to find the list to rename
	int index = -1;

	for (size_t i = 0; lists[i] != NULL; ++i) {
		if (strcmp(lists[i]->title, current) == 0) {
			index = i;
		}
	}

	// Check if we found the item
	if (index == -1) {
		fprintf(stderr, "Couldn't find the list with name '%s'.", current);
		free(desired);
		free_list_pointer_array(lists);
		exit(1);
	}

	// Otherwise update the title of the list
	lists[index]->title = desired;

	// Write this back to the file
	write_file(DEFAULT_FILEPATH, lists);

	// Free everything we need to
	free_list_pointer_array(lists);
}
