#ifndef __KEYBOARD_INPUT_H
#define __KEYBOARD_INPUT_H

#include <kernel/core/include/kdefs.h>
#include <kernel/drivers/input/input-keycodes.h>

struct input_event
{
        enum keycode code;
        uchar        c;
        uint8        flags;
};

#endif
