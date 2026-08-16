#include <kernel/core/kdefs.h>
#include <kernel/core/mem.h>
#include <kernel/core/string.h>
#include <kernel/drivers/video/vga.h>
#include <kernel/drivers/video/video.h>

struct vidbuf     fb;
struct vga_cursor cursor;

void kmain(void)
{
        vidbuf_init(&fb);

        const char *s = "Hello world!";
        uint32 size   = strlen(s);
        uint16 xpos   = (VGA_WIDTH / 2) - (size / 2);
        uint16 ypos   = VGA_HEIGHT / 2;

        vga_cursor_move(xpos, ypos);

        vidbuf_puts(&fb, "Hello world!");
}
