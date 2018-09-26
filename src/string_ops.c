#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_ops.h"

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

	final[size - removeable] = '\0';

	return final;
}

char* join(char** arr, size_t start, size_t end, unsigned char delim) {
	// Calculate the amount of memory needed
	size_t len = 0;

	for (size_t i = start; i < end; ++i) {
		len += strlen(arr[i]) + 1;
	}

	// Remove the last delimiter
	--len;
	// Allocate memory for the string
	char* joined = malloc(sizeof(char) * (len + 1));
	// Store our position
	size_t pos = 0;

	// Iterate through and copy the string in
	for (size_t i = start; i < end; ++i) {
		// Get the length of the string
		size_t current_len = strlen(arr[i]);
		// Copy into memory
		strncpy(joined + pos, arr[i], current_len);
		// Update our position
		pos += current_len;
		// Copy the delimiter in
		if (i + 1 != end)
			joined[pos++] = delim;
	}

	// Assign the null byte
	joined[len] = '\0';

	return joined;
}
