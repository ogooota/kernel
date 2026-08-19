#ifndef __INCLUDE_IO_H
#define __INCLUDE_IO_H

#include "kdefs.h"

/**
 * Portas I/O
 */
#define CRTC_CTL_PORT         0x3D4
#define CRTC_DATA_PORT        0x3D5
#define CRTC_HIGH_BYTE_REG    0x0E
#define CRTC_LOW_BYTE_REG     0x0F

extern void outb(uint16 port, uchar data);
extern uint8 inb(uint16 port);

#endif
