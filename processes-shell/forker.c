#include <stdbool.h>
#include "queue.h"
#include "in_built.h"
#include "forker.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>



void executor(struct Queue *queue, struct Path *pth) {
	while (!isEmpty(queue)) {
		struct Command *cmd = deQueue(queue);
		switch(cmd->type) {
			case EXIT: exit_ib(cmd->num_args); break;
			case PATH: path_ib(cmd->args, cmd->num_args, pth); break;
			case CD: cd_ib(cmd->args, cmd->num_args); break;
			case PROG: break; // Any program command should not be here but the compiler is being annoying
		}
		deleteCommand(cmd);
	}
}

void forker(struct Queue *queue, struct Path *pth, char const *file_out) {
	while (!isEmpty(queue)) {
		struct Command *cmd = deQueue(queue);
		int rv = fork();
		if (rv == -1) {
			fprintf(stderr, "Error forking process.\n");
			exit(1);
		}
		if (rv == 0) {
			char path_buff[100];
			unsigned pths = pth->num_paths;
			for (unsigned i=0;i<pths;i++) {
				size_t len = strlcpy(path_buff, pth->path_arr[i], 100);
				if (len >= 98) {
					fprintf(stderr, "Path overflowed buffer.\n");
					exit(1);
				}
				if (path_buff[len-1] != '/') {
					path_buff[len] = '/'; path_buff[len+1] = '\0';
				}

				len = strlcat(path_buff, cmd->cmd, 100);
				if (len >= 100) {
					fprintf(stderr, "Path with command overflowed buffer.\n");
					exit(1);
				}
				int acr = access(path_buff, X_OK);
				if (acr == -1) continue;
				if (file_out != NULL) {
					close(STDOUT_FILENO);
					int fd = open(file_out, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

					if (fd == -1) {
						fprintf(stderr, "Failed to open and create file.\n");
						exit(1);
					}
				}
				// printf("THESE ARE THE ARGS: %s\n", cmd->args[1]);
				execv(path_buff, cmd->args);

			}
			fprintf(stderr, "An error has occured.\n");
		}
		deleteCommand(cmd);
	}

	while (errno != ECHILD) wait(NULL);

}
