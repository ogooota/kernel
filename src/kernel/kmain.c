#include <kernel/drivers/video.h>

struct vga_cursor      cursor;
struct vga_framebuffer fb;

void kmain(void)
{
        if (video_vga_fb_init(&fb) < 0)
        {
                /**
                 * I'm still going to find out
                 * what to do in case this fails
                 */
                return;
        }

        video_vga_fb_write_string
                (&fb,
                 cursor,
                 "Hello world!\n",
                 VGA_COLOR_LIGHT_GREY,
                 VGA_COLOR_BLACK);

        video_vga_fb_swap(&fb);
}

