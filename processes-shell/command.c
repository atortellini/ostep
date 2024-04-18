#include "command.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


static bool strsEqual(restrict const char *str1, restrict const char *str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2) return false;
		str1++; str2++;
	}

	if (*str1 == '\0' && *str2 == '\0') return true;
	return false;
}


static void checkInBuilt(restrict struct Command *command) {
	if (command == NULL) return;
	if (command->cmd == NULL) return;


	if (strsEqual(command->cmd, "cd")) {
		command->type = CD;
		return;
	}
	if (strsEqual(command->cmd, "path")) {
		command->type = PATH;
		return;
	}
	if (strsEqual(command->cmd, "exit")) {
		command->type = EXIT;
		return;
	}

	command->type = PROG;

}

struct Command *createComamnd(const char *cmd) {
	struct Command *new_command = (struct Command *)malloc(sizeof(struct Command));
	if (new_command == NULL) {
		fprintf(stderr, "Malloc failed to create new Command.\n");
		exit(1);
	}
	new_command->cmd = strdup(cmd);
	if (new_command->cmd == NULL) {
		fprintf(stderr, "Failed to duplicate string in Command creation.\n");
		exit(1);
	}

	checkInBuilt(new_command);

	new_command->num_args = 0;
	new_command->next = NULL;
}



struct Command *setArgs(struct Command *cmd, )
