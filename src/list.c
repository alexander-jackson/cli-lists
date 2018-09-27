#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void free_list(struct List* list) {
	// Free the title
	free(list->title);

	// Iterate through each item and free it
	for (size_t i = 0; list->items[i] != NULL; ++i) {
		free(list->items[i]);
	}

	// Free the actual items pointer
	free(list->items);

	// Free the list itself
	free(list);
}

void free_list_pointer_array(struct List** lists) {
	for (size_t i = 0; lists[i] != NULL; ++i) {
		free_list(lists[i]);
	}

	free(lists);
}

void display_list(struct List* list) {
	// Display the title
	printf("List Title: %s\n", list->title);

	// Display the item count
	printf("Item count: %zu\n", list->item_count);

	// Display the items
	for (size_t i = 0; list->items[i] != NULL; ++i) {
		printf("%s\n", list->items[i]);
	}
}
