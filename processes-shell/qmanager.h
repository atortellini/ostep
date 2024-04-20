#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include "queue.h"

struct Queue_Manager {
	struct Queue inbuilt_q;
	struct Queue command_q;
};


void initQManager(struct Queue_Manager *qmanager);

void managedEnQueue(struct Queue_Manager *qmanager, struct Command *command);

#endif

