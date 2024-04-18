#ifndef COMMAND_H
#define COMMAND_H

enum IN_BUILT { EXIT, PATH, CD, PROG};

struct Command {

	char *cmd;
	char **args;
	enum IN_BUILT type;
	unsigned num_args;
	struct Command *next;
};




#endif