#ifndef __VGA_H
#define __VGA_H

#include <kernel/kdefs.h>

#define VGA_ADDR   0x000B8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_AREA   (VGA_WIDTH * VGA_HEIGHT)

enum vga_color
{
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE,
        VGA_COLOR_GREEN,
        VGA_COLOR_CYAN,
        VGA_COLOR_RED,
        VGA_COLOR_MAGENTA,
        VGA_COLOR_BROWN,
        VGA_COLOR_LIGHT_GREY,
        VGA_COLOR_DARK_GREY,
        VGA_COLOR_LIGHT_BLUE,
        VGA_COLOR_LIGHT_GREEN,
        VGA_COLOR_LIGHT_CYAN,
        VGA_COLOR_LIGHT_RED,
        VGA_COLOR_LIGHT_MAGENTA,
        VGA_COLOR_LIGHT_BROWN,
        VGA_COLOR_WHITE,
        VGA_COLOR_SIZE
};

uint16 vga_mkcell(const uchar c, enum vga_color fg, enum vga_color bg);
void vga_clear(const uint16 cell);
void vga_init();
void vga_putcell(const uint16 cell);
void vga_putcell_abs(const uint16 cell, const uint16 pos);
void vga_putstream(const uint16 *stream, const uint32 size);

struct vga_cursor
{
        uint16 x;
        uint16 y;
        uint16 abs;
};

void vga_cursor_init(struct vga_cursor *cursor);
void vga_cursor_move(const uint16 x, const uint16 y);

void vga_atos(const char *s, uint32 size, uint16 *out);

#endif
