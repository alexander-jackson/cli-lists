#include <stdio.h>
#include <stdlib.h>

#include "lists_config.h"
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

	setup();

	// Get the second argument
	char* command = argv[1];

	// Run it
	run_command(command, argc, argv);

	return 0;
}
