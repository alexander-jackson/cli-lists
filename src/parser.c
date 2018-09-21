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

struct List* extract_list(char* content, size_t start, size_t end) {
	// Get the substring
	char* substr = substring(content, start, end);

	// Split the string
	char** lines = split(substr, '\n');

	// Free the substring
	free(substr);

	// Get the title of the list
	size_t len_title = strlen(lines[0]);
	char* title = substring(lines[0], 1, len_title - 1);

	// Get the number of items within the list
	size_t count = 0;
	for (size_t i = 1; lines[i] != NULL; ++i) {
		if (lines[i][0] != '\0') ++count;	
	}

	// Allocate the memory required
	char** items = malloc(sizeof(char*) * (count + 1));

	for (size_t i = 1; i <= count; ++i) {
		items[i - 1] = lines[i];
	}

	// Null terminate the buffer
	items[count] = NULL;

	free(lines);
	free(lines[0]);
	free(lines[count + 1]);

	// Create the List structure
	struct List* list = malloc(sizeof(struct List));
	list->title = title;
	list->items = items;

	display_list(list);

	free_list(list);
}

// [uni stuff]
// chicken breast
// beef
// pasta
// rice

struct List** parse_file(char* content) {
	// Calculate the number of lists
	size_t num_lists = 0;
	for (size_t i = 0; content[i] != '\0'; ++i) {
		if (content[i] == '[') ++num_lists;
	}

	printf("%zu lists.\n", num_lists);

	// Allocate space for the lists
	List** lists = malloc(sizeof(struct List*) * (num_lists + 1));

	char* list_title = NULL;

	for (size_t i = 0; content[i] != '\0'; ++i) {
		if (content[i] == '[') {
			// Find the next one
			int end = next_instance_of('[', content, i);
			if (end == -1) end = strlen(content);

			struct List* extracted = extract_list(content, i, end);

			i = end - 1;
		}
	}
	/*
	for (size_t i = 0; content[i] != '\0'; ++i) {
		if (content[i] == '[') {
			if (list_title != NULL) free(list_title);
			int end = next_instance_of(']', content, i);
			if (end == -1) break;

			list_title = substring(content, i + 1, end);
			printf("List title: %s\n", list_title);
		}
		else if (content[i] == '\n') {
			int end = next_instance_of('\n', content, i);
			if (end == -1) break;

			char* substr = substring(content, i + 1, end);
			if (substr[0] == '[' || substr[0] == '\0') {
				free(substr);
				continue;
			}
			printf("List title: %s, Current line: %s\n", list_title, substr);
			free(substr);
		}
	}
	*/
	
	free(list_title);
	free(lists);

	puts("End of parser.");
}
