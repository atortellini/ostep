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
