#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"
#include "parser.h"

int main(void) {
	char* contents = read_file("sample.toml");

	parse_file(contents);

	free(contents);

	return 0;
}
