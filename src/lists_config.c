#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lists_config.h"

char* DEFAULT_FILEPATH;

char* get_default_filepath() {
        // Get the home directory
        char* home_dir = getenv("HOME");
        // Define the string to append
        char* append = "/.local/share/cli-lists/lists.toml";

        // Calculate the total length required
        size_t home_len = strlen(home_dir);
        size_t append_len = strlen(append);
        size_t length = home_len + append_len;
        // Allocate memory
        char* path = malloc(sizeof(char) * (length + 1));
        // Copy in the strings
        strncpy(path, home_dir, home_len);
        strncpy(path + home_len, append, append_len);
        // Set the end
        path[length] = '\0';

        return path;
}

void setup() {
	// Set the value of DEFAULT_FILEPATH
	DEFAULT_FILEPATH = get_default_filepath();
}
