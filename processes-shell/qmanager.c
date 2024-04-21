#include <stdbool.h>
#include "queue.h"
#include "qmanager.h"
#include <stdlib.h>

void initQManager(struct Queue_Manager *qmanager) {
	if (qmanager == NULL) return;
	initializeQueue(&(qmanager->inbuilt_q));
	initializeQueue(&(qmanager->command_q));
}

void managedEnQueue(struct Queue_Manager *qmanager, struct Command *command) {
	if (qmanager == NULL || command == NULL) return;

	switch(command->type) {
		case PROG: enQueue(&(qmanager->command_q), command); return;
		default: enQueue(&(qmanager->inbuilt_q), command);
	}
}

// Thing to note about this function is that if both are nonempty, only inbuilt commands will be flagged
int giveNonEmptyQ(struct Queue_Manager *qmanager) {
	if (qmanager == NULL) return -1;
	if (!(isEmpty(&(qmanager->inbuilt_q)))) return 0;
	if (!(isEmpty(&(qmanager->command_q)))) return 1;
	return -1;

}
