#include "video.h"

#include <kernel/core/mem.h>
#include <kernel/core/string.h>

void vidbuf_init(struct vidbuf *fb)
{
        if (fb == NULL)
        {
                return;
        }

        fb->w = VGA_WIDTH;
        fb->h = VGA_HEIGHT;

        vga_init();
}

void vidbuf_putc(struct vidbuf *fb, const char c, const uint8 x, const uint8 y)
{
        if (fb == NULL      ||
            x  >= VGA_WIDTH ||
            y  >= VGA_HEIGHT)
        {
                return;
        }

        uint16 cell = vga_mkcell(c, VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        uint16 abs  = y * VGA_WIDTH + x;

        fb->data[abs] = cell;
}

void vidbuf_puts(struct vidbuf *fb, const char *s, const uint8 x, const uint8 y)
{
        if (fb == NULL      ||
            s  == NULL      ||
            x  >= VGA_WIDTH ||
            y  >= VGA_HEIGHT)
        {
                return;
        }

        uint32 len = strlen(s);

        for (uint32 i = 0; i < len; i++)
        {
                vidbuf_putc(fb, s[i], x + i, y);
        }
}

