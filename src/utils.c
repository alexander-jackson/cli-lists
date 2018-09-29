#include <stdio.h>

#include "utils.h"
#include "lists_config.h"

void help() {
	// Display the help for the project
	printf("Welcome to cli-lists!\n");
	printf("This project is designed to allow you to work with lists from the command line.\n");
	printf("This includes anything such as shopping or things you need to do.\n\n");
	printf("Commands:\n");
	printf("\tlists create {list_name} => Creates a list with the name $list_name\n");
	printf("\tlists delete {list_name} => Deletes the list with the name $list_name if it exists\n");
	printf("\tlists append {list_name} {item} => Appends $item to $list_name\n");
	printf("\tlists remove {list_name} {item} => Removes $item from $list_name\n");
	printf("\tlists display {list_name} => Displays the contents of $list_name. If $list_name is empty, displays all lists\n");
}
