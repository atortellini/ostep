
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>



void initializeQueue(struct Queue *queue) {
	if (queue == NULL) return;

	queue->head = NULL;
	queue->rear = NULL;
}


void enQueue(struct Queue *queue, struct Command *command) {
	if (queue == NULL || command == NULL) return;


	if ((queue->head == NULL) && (queue->rear == NULL)) {
		queue->head = queue->rear = command;
		return;
	}

	queue->rear->next = command;
	queue->rear = command;

}

struct Command *deQueue(struct Queue *queue) {
	if (queue == NULL || queue->head == NULL) return NULL;

	struct Command *temp = queue->head;

	if (temp == queue->rear) {
		queue->rear = temp->next;
	}
	queue->head = temp->next;

	return temp;
}


void emptyQueue(struct Queue *queue) {
	struct Command *temp;
	while ((temp = deQueue(queue)) != NULL)
		deleteCommand(temp);
	
}

int main(void) {
	return 0;
}


