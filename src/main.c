#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"
#include "parser.h"
#include "list.h"
#include "controller.h"

int main(int argc, char* argv[]) {
	if (argc < 2) {
		// Display the help menu
		puts("Help");

		return 0;
	}

	// Get the second argument
	char* command = argv[1];

	printf("Command: %s\n", command);

	// Run it
	run_command(command, argc, argv);

	//char* contents = read_file("sample.toml");

	//struct List** lists = parse_file(contents);

	//for (size_t i = 0; lists[i] != NULL; ++i) {
	//	// Display the list
	//	display_list(lists[i]);
	//}

	//// Ensure we free the lists
	//for (size_t i = 0; lists[i] != NULL; ++i) {
	//	free_list(lists[i]);
	//}

	//free(lists);

	//free(contents);

	return 0;
}
