#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

void free_list(struct List* list) {
	// Free the title
	free(list->title);

	// Iterate through each item and free it
	for (size_t i = 0; list->items[i] != NULL; ++i) {
		free(list->items[i]);
	}

	// Free the actual items pointer
	free(list->items);

	// Free the list itself
	free(list);
}

void display_list(struct List* list) {
	// Display the title
	printf("List Title: %s\n", list->title);

	// Display the items
	for (size_t i = 0; list->items[i] != NULL; ++i) {
		printf("%s\n", list->items[i]);
	}
}

int next_instance_of(unsigned char find, char* str, size_t start) {
	for (size_t i = start + 1; str[i] != '\0'; ++i) {
		if (str[i] == find) return i;
	}

	return -1;
}

char* substring(char* str, size_t start, size_t end) {
	if (end < start) {
		fprintf(stderr, "Cannot get a substring of negative length %zu - %zu from '%s'\n", end, start, str);
		exit(1);
	}

	// Get the string length
	size_t str_len = strlen(str);
	if (str_len <= start || str_len < end) {
		fprintf(stderr, "Cannot get a substring out of bounds of the string '%s', start=%zu, end=%zu", str, start, end);
		exit(1);
	}

	// Calculate the size of the substring
	size_t substring_len = end - start;
	// Allocate memory
	char* substr = malloc(sizeof(char) * (substring_len + 1));
	// Check it allocated properly
	if (substr == NULL) {
		fprintf(stderr, "Failed to allocate memory for substring of '%s', start=%zu, end=%zu", str, start, end);
		exit(1);
	}

	// Copy the string into memory
	strncpy(substr, str + start, substring_len);
	// Add the null terminator
	substr[substring_len] = '\0';
	return substr;
}

char** split(char* str, unsigned char delimiter) {
	// Count number of splits needed
	size_t delim_count = 0;
	for (size_t i = 0; str[i] != '\0'; ++i) {
		if (str[i] == delimiter) ++delim_count;
	}

	// Allocate memory
	char** result = malloc(sizeof(char*) * (delim_count + 1));

	// Store the last instance of the delimiter and the count so far
	size_t last = 0, count = 0;
	// Iterate through the string and find each substring needed
	for (size_t i = 0; str[i] != '\0'; ++i) {
		if (str[i] == delimiter) {
			// Get the substring and allocate it
			result[count++] = substring(str, last, i);
			// Update our values
			last = i + 1;
		}
	}

	// Null terminate the buffer
	result[delim_count] = NULL;

	return result;
}

char* clean(char* str, char* rem) {
	size_t removeable = 0, size;
	// Iterate through once
	for (size = 0; str[size] != '\0'; ++size) {
		for (size_t i = 0; rem[i] != '\0'; ++i) {
			if (str[size] == rem[i])
				++removeable;
		}
	}

	// Allocate memory for the new size of the string
	char* final = malloc(sizeof(char) * (size - removeable + 1));
	// Store the current position
	size_t pos = 0;

	for (size_t i = 0; str[i] != '\0'; ++i) {
		size_t flag = 1;

		for (size_t j = 0; rem[j] != '\0'; ++j) {
			if (str[i] == rem[j])
				flag = 0;
		}

		if (flag)
			final[pos++] = str[i];
	}

	return final;
}

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
