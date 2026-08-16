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
        uint16 cell = vga_mkcell(' ', VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        memsetw(fb->data, cell, VGA_AREA);

        vga_init();

}

void vidbuf_putc(struct vidbuf *fb, const char c)
{
        if (fb == NULL)
        {
                return;
        }

        uint16 cell = vga_mkcell(c, VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        vga_putcell(cell);
}

void vidbuf_puts(struct vidbuf *fb, const char *s)
{
        if (fb == NULL ||
            s  == NULL)
        {
                return;
        }

        uint32 len = strlen(s);
        uint16 stream[len];
        memsetw(stream, 0, len);

        vga_atos(s, len, stream);

        vga_putstream(stream, len);
}
