// Takes a char* filepath and returns a char* pointing 
// to the contents of the file in memory
char* read_file(char*);

// Takes a char* filepath and char* string to write 
// and writes it to the given filepath
void write_file(char*, char*);

// Appends the given string to the given filepath
void append_file(char*, char*);
