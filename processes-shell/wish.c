#include "qmanager.h"
#include "command_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


enum mode {BATCH, INTER};

// struct Shell_S {
// 	// char **path;
// 	enum mode state;
// 	const char *error_message;
// } Shell;


int main(int argc, char *argv[]) {
	FILE *parse_input = (argc == 1) ? stdin : fopen(argv[1], "r"); // Temporary
	if (parse_input == NULL) {
		fprintf(stderr, "Unable to open batch file.\n");
		exit(1);
	}
	struct Queue_Manager manager; initQManager(&manager);
	char *file_out = NULL, *line_buff = NULL;
	size_t lbuff_size = 0;
	while (1) {
		if (argc == 1) printf("wish> ");
		if (parser(&manager, &line_buff, &lbuff_size, parse_input, &file_out) == 1) {
			continue;
		}

		// printf("Command: %s\t Args: %s\n", manager.command_q.rear->cmd, manager.command_q.rear->args[0]);

	}



	return 0;
}


