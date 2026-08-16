#ifndef __KEYBOARD_INPUT_QUEUE_H
#define __KEYBOARD_INPUT_QUEUE_H

#include "input.h"

#define IEQ_MAX 64

struct event_queue
{
        struct input_event data[IEQ_MAX];
        uint8              head;
        uint8              tail;
};

void eventq_push(struct input_event ev);
void eventq_pop(struct input_event *out);

#endif
