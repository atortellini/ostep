#include "command.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_ARGS 4

static bool strsEqual(char const *str1, char const *str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2) return false;
		str1++; str2++;
	}

	if (*str1 == '\0' && *str2 == '\0') return true;
	return false;
}


static void checkInBuilt(struct Command *command) {
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

struct Command *createCommand(char const *cmd) {
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

	new_command->args = (char **)malloc(sizeof(char *) * (MAX_ARGS + 1));
	if (new_command->args == NULL) {
		fprintf(stderr, "Malloc failed to allocate args array for new Command.\n");
		exit(1);
	}
	for (unsigned i = 0; i<=MAX_ARGS; i++) {
		new_command->args[i] = NULL;
	}

	new_command->num_args = 0;
	new_command->max_args = MAX_ARGS;
	checkInBuilt(new_command);

	new_command->num_args = 0;
	new_command->next = NULL;

	return new_command;
}


static void expandArgsArray(struct Command *command) {
	if (command == NULL) return;
	unsigned new_max = command->max_args + MAX_ARGS;
	command->args = realloc(command->args, sizeof(char *) * (new_max + 1));
	if (command->args == NULL) {
		fprintf(stderr, "Failed to expand args array.\n");
		exit(1);
	}
	for (unsigned i=command->max_args+1;i<=new_max;i++) {
		command->args[i] = NULL;
	}
	command->max_args = new_max;
}


void setArgs(struct Command *command, char const *arg) {
	if (command == NULL || arg == NULL) return;

	if (command->max_args == command->num_args)
		expandArgsArray(command);

	char *arg_dup = strdup(arg);
	if (arg_dup == NULL) {
		fprintf(stderr, "Failed to duplicate arg for command.\n");
		return;
	}

	command->args[command->num_args++] = arg_dup;

}


void deleteCommand(struct Command *command) {
	if (command == NULL) return;

	free(command->cmd);

	for (unsigned i=0;i<command->num_args;i++) {
		free(command->args[i]);
	}
	free(command->args);
	free(command);
}


