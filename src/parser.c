#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "list.h"
#include "string_ops.h"

size_t count_items(char** lines, size_t current_pos) {
	size_t items = 0;

	for (size_t i = current_pos; lines[i] != NULL; ++i) {
		if (lines[i][0] != '\0')
			++items;

		if (lines[i][0] == '[')
			return items - 1;
	}

	return items;
}

char** get_list_items(char** lines, size_t start) {
	// Get the number of items
	size_t item_count = count_items(lines, start);

	// Allocate memory for the items
	char** items = malloc(sizeof(char*) * (item_count + 1));
	// Track the position in memory
	size_t pos = 0;

	for (size_t i = start; lines[i] != NULL; ++i) {
		if (lines[i][0] != '\0')
			items[pos++] = lines[i];

		if (lines[i][0] == '[')
			break;
	}

	items[item_count] = NULL;

	return items;
}

struct List** parse_file(char* content) {
	// Split the list into lines
	char** lines = split(content, '\n');

	// Count the number of lists
	size_t list_count = 0;
	for (size_t i = 0; lines[i] != NULL; ++i) {
		if (lines[i][0] == '[')
			++list_count;
	}

	// Allocate memory for the lists
	struct List** lists = malloc(sizeof(struct List*) * (list_count + 1));
	// Track the position
	size_t pos = 0;

	for (size_t i = 0; lines[i] != NULL; ++i) {
		if (lines[i][0] == '[') {
			// Generate a new list structure
			struct List* current_list = malloc(sizeof(struct List));
			// Set the name of the list
			current_list->title = clean(lines[i], "[]");
			// Set the items within it
			current_list->items = get_list_items(lines, i + 1);
			// Add it to the memory structure
			lists[pos++] = current_list;
		}
	}

	// Free the unused parts of the data
	for (size_t i = 0; lines[i] != NULL; ++i) {
		if (lines[i][0] == '[' || lines[i][0] == '\0')
			free(lines[i]);
	}

	// Free the pointer to lines itself
	free(lines);

	// Add the NULL pointer
	lists[list_count] = NULL;

	// Return the parsed file
	return lists;
}
