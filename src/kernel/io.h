#ifndef __INCLUDE_IO_H
#define __INCLUDE_IO_H

#define FRAMEBUFFER_COMMAND_PORT 0x3D4
#define FRAMEBUFFER_DATA_PORT    0x3D5

#define FRAMEBUFFER_HIGH_BYTE_COMMAND 14
#define FRAMEBUFFER_LOW_BYTE_COMMAND  15

void outb(unsigned short port, unsigned char data);

#endif
