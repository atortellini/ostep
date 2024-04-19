#include "in_built.h"
#include "path.h"

#include <unistd.h>
#include "stdio.h"

void cd_ib(char const **args, int const num_args) {
	if (num_args != 1) {
		fprintf(stderr, "An error has occurred\n");
		return;
	}

	int rv = chdir(args[0]);
	if (rv) {
		fprintf(stderr, "An error has occurred\n");
	}

}


void path_ib(char const **args, int const num_args, struct Path *curr_path) {
	if (args == NULL) {
		fprintf("NULL args passed to path.\n");
		return;
	}


}



void exit(int const num_args) {

}