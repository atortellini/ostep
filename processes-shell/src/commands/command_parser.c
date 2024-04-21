#include <stdbool.h>
#include <queue/qmanager.h>
#include "command_parser.h"

#include <stdlib.h>
#include <string.h>







int parser(struct Queue_Manager *qmanager, char **line_buff, size_t *lbuff_size, FILE *restrict fp, char **file_out) {
	if (qmanager == NULL || fp == NULL) return 1;

	char *cmd = NULL, *delim = " \n"; // Think about moving delim initializaiton since will occur every time parser is called
	ssize_t linelen;


	if ((linelen = getline(line_buff, lbuff_size, fp)) == -1) {
		return 1;
	}
	*file_out = NULL;
	cmd = strtok(*line_buff, delim);
	if (cmd == NULL) return 1;
	do {
		switch(*cmd) {
		case '>': case '&':
			fprintf(stderr, "An error has occurred\n");
			return 1;
		}

		struct Command *new_command = createCommand(cmd);
		char *arg;
		while ((arg = strtok(NULL, delim)) != NULL) {
			if (*arg == '&') {
				managedEnQueue(qmanager, new_command);
				break; // With how I'm checking this it also allows for input of: cmd0 & cmd1 &, to work without error
			}
			if (*arg == '>') {
				char *file = strtok(NULL, delim);
				char *check_end = strtok(NULL, delim);
				if (file == NULL || check_end != NULL) {
					fprintf(stderr, "An error has occurred\n");
					deleteCommand(new_command);
					return 1;
				} // For right now im just going to assume that the user doesnt screw with outputting to file
				managedEnQueue(qmanager, new_command);
				char *temp = strdup(file);
				if (temp == NULL) {
					fprintf(stderr, "Failed to duplicate file output string.\n");
					deleteCommand(new_command);
					return 1;
				}
				*file_out = temp;
				return 0;
			}
		
			setArgs(new_command, arg);
		}
		if (arg == NULL) managedEnQueue(qmanager, new_command);

	} while ((cmd = strtok(NULL, delim)) != NULL);

	return 0;
}	


