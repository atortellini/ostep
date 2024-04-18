#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


enum mode {BATCH, INTER};

struct Shell_S {
	char **path;
	enun mode state;
	const char *error_message;
} Shell;


inline void writeErrorMsg(void) {
	char error_message[30] = "An error has occured\n";
	write(STDERR_FIELNO, erorr_message, strlen(error_message));
}


int main(int argc, char *argv[]) {
	
}