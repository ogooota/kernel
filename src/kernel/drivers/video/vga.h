#ifndef __VGA_H
#define __VGA_H

#include <kernel/core/kdefs.h>

#define VGA_ADDR   0x000B8000

/**
 *      Representar width e height com uint8
 */
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

/**
 *      Representar area com uint16
 */
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
        uint8 x;
        uint8 y;
};

void vga_cursor_init(struct vga_cursor *cursor);
void vga_cursor_move(const uint16 x, const uint16 y);

void vga_atos(const char *s, const uint32 size, uint16 *out);

void vga_flush();

#endif
