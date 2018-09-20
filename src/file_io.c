#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

char* read_file(char* filepath) {
	// Open the file
	FILE* f = fopen(filepath, "r");
	if (f == NULL) {
		fprintf(stderr, "The following file failed to open for reading: %s\n", filepath);
		exit(1);
	}

	// Seek to the end
	if (fseek(f, 0L, SEEK_END) != 0) {
		fprintf(stderr, "Failed to seek to the end of %s\n", filepath);
		fclose(f);
		exit(1);
	}

	// Get the length of the file
	long int file_length = ftell(f);
	if (file_length < 0) {
		fprintf(stderr, "Failed to get the size of the file %s\n", filepath);
		fclose(f);
		exit(1);
	}

	// Seek back to the start
	if (fseek(f, 0L, SEEK_SET) != 0) {
		fprintf(stderr, "Failed to seek to the start of %s\n", filepath);
		fclose(f);
		exit(1);
	}

	// Allocate memory for the resulting file
	char* contents = malloc(sizeof(char) * (file_length + 1));
	if (contents == NULL) {
		fprintf(stderr, "Failed to allocate memory for the file %s\n", filepath);
		fclose(f);
		exit(1);
	}

	// Read the file into memory
	size_t read_size = fread(contents, sizeof(char), file_length, f);
	if (read_size != (size_t) file_length) {
		fprintf(stderr, "Failed to read all of the file %s into memory\n", filepath);
		fclose(f);
		free(contents);
		exit(1);
	}

	// Null terminate the buffer
	contents[file_length] = '\0';
	// Close the file
	fclose(f);
	// Return the contents of the file
	return contents;
}