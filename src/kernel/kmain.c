#include <kernel/core/kdefs.h>
#include <kernel/drivers/video/vga.h>
#include <kernel/drivers/video/video.h>
#include <kernel/core/mem.h>

struct vidbuf     fb;
struct vga_cursor cursor;

void kmain(void)
{
  vidbuf_init(&fb);
  vidbuf_puts(&fb, "Hello world!");
}
