#ifndef __VIDEO_H
#define __VIDEO_H

#include <kernel/core/include/kdefs.h>

void vidinit();
void vidcsrmv(const uint8 x, const uint8 y);
void vidputc(const char c);
void vidputs(const char *s);
void viddump();

#endif
