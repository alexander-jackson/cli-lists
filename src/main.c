#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

int main(void) {
	char* contents = read_file("sample.toml");

	printf("%s\n", contents);

	free(contents);

	return 0;
}
