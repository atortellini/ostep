#ifndef COMMAND_H
#define COMMAND_H

enum IN_BUILT { EXIT, PATH, CD, PROG};

struct Command {

	char *cmd;
	char **args;
	unsigned num_args;
	unsigned max_args;
	enum IN_BUILT type;
	struct Command *next;
};

struct Command *createCommand(const char *cmd);

void setArgs(struct Command *command, const char *arg);

void deleteCommand(struct Command *command);

#endif
