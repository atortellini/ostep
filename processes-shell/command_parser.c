#include "command_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parser(struct Queue *restrict inbuilt_q, struct Queue *restrict command_q, FILE *restrict fp) {
	if (inbuilt_q == NULL || commmand_q == NULL || fp == NULL) return;

	char *line_buff = NULL, *cmd = NULL, *space = " "; size_t lbuff_size = 0; // Should think about, once I get this to work, if I want to constantly have line_buff redeclared and intiailzied every time a line needs to be parsed
	ssize_t linelen;

	while (cmd == NULL) {
		if ((linelen = getline(&line_buff, &lbuff_size, fp)) == -1) {
			fprintf(stderr, "Failed to read line from input.\n");
			return;
		}
		cmd = strtok(line_buff, space);
		if (cmd == NULL) continue;
		switch(*cmd) {
			case '>': case '&': 
				fprintf(stderr, "An error has occured.\n");
				cmd = NULL;
				continue;
		}
	}
	// Should prob figure out how to simplify all code below this line to be a while loop
	struct Command *new_command = createCommand(cmd);
	
	char *arg = strtok(NULL, space);
	if (arg == NULL) {
		switch(new_command->type) {
			case NOT: enQueue(command_q, new_command); free(line_buff); return;
			default: enQueue(inbuilt_q, new_command); free(line_buff); return;
		}
	}

	switch (*arg) {
		case '&': case '>':
			if (new_command->type == NOT) {
				enQueue(command_q, new_command);
				arg = strtok(NULL, space);
			} else {
				enQueue(inbuilt_q, new_command);
				free(line_buff);
				return;
			}
	}

}	