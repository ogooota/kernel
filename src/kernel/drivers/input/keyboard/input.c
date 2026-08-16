#include "input.h"
#include "input-queue.h"

/**
 *      Implementação da input queue
 */

/**
 *      Fila de inputs global
 */
static struct event_queue input_evq;

void eventq_push(struct input_event ev)
{
        uint8 currsz = input_evq.tail - input_evq.head;

        if (currsz >= IEQ_MAX)
        {
                return;
        }

        uint8 i     = input_evq.tail & (IEQ_MAX - 1);
        input_evq.data[i] = ev;
        input_evq.tail++;
}

void eventq_pop(struct input_event *out)
{
        if (input_evq.head == input_evq.tail)
        {
                return;
        }

        uint8 i = input_evq.head & (IEQ_MAX - 1);
        *out    = input_evq.data[i];
        input_evq.head++;
}

/**
 *      Implementação do módulo de input
 */

/**
 * TODO
 */


