#include "qmanager.h"
#include "command_parser.h"

#include <stdlib.h>
#include <string.h>







int parser(struct Queue_Manager *qmanager, char **line_buff, size_t *lbuff_size, FILE *restrict fp, char **file_out) {
	if (qmanager == NULL || fp == NULL) return 1;

	char *cmd = NULL, *delim = " \n"; // Think about moving delim initializaiton since will occur every time parser is called
	ssize_t linelen;


	if ((linelen = getline(line_buff, lbuff_size, fp)) == -1) {
		fprintf(stderr, "Failed to read line from input.\n");
		return 1;
	}
	*file_out = NULL;
	cmd = strtok(*line_buff, delim);
	if (cmd == NULL) return 1;
	do {
		switch(*cmd) {
		case '>': case '&':
			fprintf(stderr, "An error has occured.\n");
			return 1;
		}

		struct Command *new_command = createCommand(cmd);
		char *arg;
		while ((arg = strtok(NULL, delim)) != NULL) {
			switch(*arg) {
				case '&': managedEnQueue(qmanager, new_command); continue; // With how I'm checking this it also allows for input of: cmd0 & cmd1 &, to work without error
				case '>': {
					managedEnQueue(qmanager, new_command);
					char *file = strtok(NULL, delim); // For right now im just going to assume that the user doesnt screw with outputting to file
					char *temp = strdup(file);
					if (temp == NULL) {
						fprintf(stderr, "Failed to duplicate file output string.\n");
						return 1;
					}
					*file_out = temp;
					return 0;
				}
			}
			setArgs(new_command, arg);
		}
		managedEnQueue(qmanager, new_command);

	} while ((cmd = strtok(NULL, delim)) != NULL);

	return 0;
}	


