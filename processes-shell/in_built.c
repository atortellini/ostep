
#include "in_built.h"


#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>

void cd_ib(char **args, unsigned const num_args) {
	if (num_args > 1) {
		fprintf(stderr, "An error has occurred\n");
		return;
	}

	int rv = chdir(args[0]);
	if (rv) {
		fprintf(stderr, "An error has occurred\n");
	}

}


void path_ib(char **args, unsigned const num_args, struct Path *curr_path) {
	if (args == NULL) {
		fprintf(stderr, "NULL args passed to path.\n");
		return;
	}
	if (!num_args) {
		clearPath(curr_path);
		return;
	}

	setPath(curr_path, args, num_args);
}



void exit_ib(unsigned const num_args) {
	if (num_args) {
		fprintf(stderr, "An error has occured\n");
		return;
	}
	exit(0);
}


