#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


enum mode {BATCH, INTER};

struct Shell_S {
	// char **path;
	enun mode state;
	const char *error_message;
} Shell;


int main(int argc, char *argv[]) {

}