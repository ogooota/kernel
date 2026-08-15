#include <kernel/kdefs.h>
#include <kernel/drivers/vga.h>
#include <kernel/mem.h>

struct vga_cursor cursor;

void kmain(void)
{
        vga_init();
        vga_cursor_move(5, 5);

        const char *s = "Hello world!";
        uint16 si[12];
        memsetb(si, 0, sizeof(si));

        vga_atos(s, 12, si);

        vga_putstream(si, 12);
}
