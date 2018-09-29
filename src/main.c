#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "lists_config.h"
#include "controller.h"

int main(int argc, char* argv[]) {
	// Setup the config parameters
	setup();

	// Check for whether the user wants help
	if (argc < 2 || !strcmp(argv[1], "help") || !strcmp(argv[1], "--help")) {
		// Display the help menu
		help();
		return 0;
	}

	// Check for version number
	if (!strcmp(argv[1], "version") || !strcmp(argv[1], "--version")) {
		printf("cli-lists version %s\n", VERSION_NUMBER);
		return 0;
	}

	// Get the second argument
	char* command = argv[1];

	// Run it
	run_command(command, argc, argv);

	// Free the memory used by the filepath
	free(DEFAULT_FILEPATH);

	return 0;
}
