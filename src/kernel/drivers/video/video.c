#include "video.h"
#include "vga.h"

#include <kernel/core/string.h>
#include <kernel/core/mem.h>

struct vidcsr
{
        uint8 x;
        uint8 y;
};

unsigned char vdata[VGA_AREA];
struct vidcsr csr;

void vidinit()
{
        memsetb(vdata, 0, sizeof(vdata));
        vidcsrmv(0, 0);
        vga_init();
}

void vidcsrmv(const uint8 x, const uint8 y)
{
        csr.x = x;
        csr.y = y;
}

void vidputc(const char c)
{
        if (c == '\n' || c == '\r')
        {
                vidcsrmv(0, csr.y + 1);
                return;
        }

        vdata[csr.y * VGA_WIDTH + csr.x] = c;

        csr.x++;
        if (csr.x > VGA_WIDTH)
        {
                vidcsrmv(0, csr.y + 1);
        }
}

void vidputs(const char *s)
{
        while (*s)
        {
                vidputc(*s);
                s++;
        }
}

void viddump()
{
        vga_flush();
}
