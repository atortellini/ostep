#include <stdbool.h>
#include <queue/qmanager.h>
#include <commands/command_parser.h>
#include <path/path.h>
#include "forker.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	struct Path pth; initializePath(&pth, "/bin");
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
			break;
		}
		switch (giveNonEmptyQ(&manager)) {
			case -1: continue;
			case 0: executor(&(manager.inbuilt_q), &pth); break;
			case 1: forker(&(manager.command_q), &pth, file_out); break;

		}
	}

	return 0;
}

