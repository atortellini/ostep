#ifndef QUEUE_H
#define QUEUE_H






#include "command.h"

struct Queue {
	struct Command *head;
	struct Command *rear;
};



#endif