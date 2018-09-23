#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"
#include "parser.h"

int main(void) {
	char* contents = read_file("sample.toml");

	struct List** lists = parse_file(contents);

	for (size_t i = 0; lists[i] != NULL; ++i) {
		// Display the list
		display_list(lists[i]);
	}

	// Write the list to a new file
	write_file("rewritten.toml", lists);

	// Ensure we free the lists
	for (size_t i = 0; lists[i] != NULL; ++i) {
		free_list(lists[i]);
	}

	free(lists);

	free(contents);

	return 0;
}
