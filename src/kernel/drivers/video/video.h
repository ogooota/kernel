#ifndef __VIDEO_H
#define __VIDEO_H

#include "vga.h"

struct vidbuf
{
        uint16 w;
        uint16 h;
        uint16 data[VGA_AREA];
};

void vidbuf_init(struct vidbuf *fb);
void vidbuf_putc(struct vidbuf *fb, const char c);
void vidbuf_puts(struct vidbuf *fb, const char *s);

#endif
