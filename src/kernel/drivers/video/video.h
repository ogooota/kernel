#ifndef __VIDEO_H
#define __VIDEO_H

#include "vga.h"

struct vidbuf
{
        uint8 w;
        uint8 h;
        uint16 data[VGA_AREA];
};

void vidbuf_init(struct vidbuf *fb);
void vidbuf_putc(struct vidbuf *fb, const char c, const uint8 x, const uint8 y);
void vidbuf_puts(struct vidbuf *fb, const char *s, const uint8 x, const uint8 y);

#endif
