#ifndef QUEUE_H
#define QUEUE_H






#include "command.h"

struct Queue {
	struct Command *head;
	struct Command *rear;
};

void initializeQueue(struct Queue *queue);


void enQueue(struct Queue *queue, struct Command *command);

struct Command *deQueue(struct Queue *queue);

inline void emptyQueue(struct Queue *queue);

#endif
