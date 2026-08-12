#include <kernel/kdefs.h>
#include <kernel/io.h>
#include <kernel/drivers/video.h>

volatile unsigned char *mem_fb = (volatile unsigned char *)VGA_FRAMEBUFFER_ADDR;

static inline void vga_cell_set_color
(struct vga_cell *cell,
 enum vga_color   foreground,
 enum vga_color   background)
{
        cell->color = (background << 4) | foreground;
}

int video_vga_fb_init(struct vga_framebuffer *fb)
{
        if (fb == NULL)
        {
                return -1;
        }

        for (unsigned int i = 0; i < VGA_FRAMEBUFFER_AREA; i++)
        {
                fb->data[i].c = ' ';
                vga_cell_set_color(&fb->data[i], VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        }

        return 0;
}

void video_vga_fb_swap(const struct vga_framebuffer *fb)
{
        unsigned int mem_i = 0;
        unsigned int i     = 0;

        while (mem_i < VGA_FRAMEBUFFER_AREA * 2 &&
               i < VGA_FRAMEBUFFER_AREA)
        {
                mem_fb[mem_i]     = fb->data[i].c;
                mem_fb[mem_i + 1] = fb->data[i].color;

                i++;
                mem_i += 2;
        }
}

void video_vga_fb_write_cell
(struct vga_framebuffer *fb,
 const struct vga_cursor cursor,
 const struct vga_cell   cell)
{
        if (fb         == NULL                   ||
            cursor.x   >= VGA_FRAMEBUFFER_WIDTH  ||
            cursor.y   >= VGA_FRAMEBUFFER_HEIGHT ||
            cell.color >= VGA_COLOR_SIZE)
        {
                return;
        }

        fb->data[cursor.y * VGA_FRAMEBUFFER_WIDTH + cursor.x] = cell;
}

void video_vga_fb_write_string
(struct vga_framebuffer *fb,
 struct vga_cursor       cursor,
 const char             *s,
 enum vga_color          foreground,
 enum vga_color          background)
{
        if (fb         == NULL                   ||
            cursor.x   >= VGA_FRAMEBUFFER_WIDTH  ||
            cursor.y   >= VGA_FRAMEBUFFER_HEIGHT ||
            s          == NULL                   ||
            foreground >= VGA_COLOR_SIZE         ||
            background >= VGA_COLOR_SIZE)
        {
                return;
        }

        for (unsigned int i = 0; s[i]; i++)
        {
                video_vga_fb_write_cell
                        (fb,
                         cursor,
                         (struct vga_cell)
                         {
                                .c = s[i],
                                .color = (background << 4) | foreground
                         });

                cursor.x++;
        }
}
