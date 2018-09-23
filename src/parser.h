typedef struct List {
	char* title;
	char** items;
} List;

void free_list(struct List*);
void display_list(struct List*);

int next_instance_of(unsigned char, char*, size_t);
char* substring(char*, size_t, size_t);
char** split(char*, unsigned char);
char* clean(char*, char*);

struct List* extract_list(char*, size_t, size_t);
struct List** parse_file(char*);
