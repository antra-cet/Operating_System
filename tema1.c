#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tema1_functions.h"


int main () {
	// Declaring the string that will read the commands
	// and allocating the necessary memory for it
	char *command = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);

	// Declaring the current directory which we start with,
	// in our case, the home directory and initializing all
	// its fields
	Dir *home = malloc(sizeof(Dir));
	home->name = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);

	strcpy(home->name, "home");
	home->next = NULL;
	home->parent = NULL;
	home->head_children_files = NULL;
	home->head_children_dirs = NULL;

	// Declaring another variable to surf through directories
	Dir *curr_dir = home;

	do
	{
		// Reading the command
		scanf("%s", command);

		// Calling the function that verifies the command
		// and calls the wanted function but not the stop function
		call_command(command, &curr_dir, home);

	} while (strcmp(command, "stop"));

	// Freeing the remaining used memory
	free(home->name);
	free(home);
	free(command);
	
	return 0;
}
