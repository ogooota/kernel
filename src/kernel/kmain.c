#include <kernel/core/kdefs.h>
#include <kernel/core/mem.h>
#include <kernel/core/string.h>
#include <kernel/drivers/video/vga.h>
#include <kernel/drivers/video/video.h>

struct vidbuf fb;

void kmain(void)
{
        vidbuf_init(&fb);

        const char *s = "Hello world!";
        uint32 size   = strlen(s);
        uint8 xpos    = (VGA_WIDTH / 2) - (size / 2);
        uint8 ypos    = VGA_HEIGHT / 2;

        vidbuf_puts(&fb, "Hello world!", xpos, ypos);

        vga_flush(fb.data);
}
