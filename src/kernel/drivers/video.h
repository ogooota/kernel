#ifndef __VIDEO_DRIVER_H
#define __VIDEO_DRIVER_H

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

struct vga_cursor
{
        unsigned int y;
        unsigned int x;
};

#define VGA_FRAMEBUFFER_ADDR 0x000B8000

#define VGA_FRAMEBUFFER_WIDTH  80
#define VGA_FRAMEBUFFER_HEIGHT 25
#define VGA_FRAMEBUFFER_AREA   (VGA_FRAMEBUFFER_WIDTH * VGA_FRAMEBUFFER_HEIGHT)

struct vga_cell
{
        unsigned char c;
        enum vga_color color;
};

struct vga_framebuffer
{
        struct vga_cell data[VGA_FRAMEBUFFER_AREA];
};

int video_vga_fb_init(struct vga_framebuffer *);
void video_vga_fb_swap(const struct vga_framebuffer *);

void video_vga_fb_write_cell
(struct vga_framebuffer *,
 const struct vga_cursor,
 const struct vga_cell);

void video_vga_fb_write_string
(struct vga_framebuffer *,
 struct vga_cursor,
 const char *,
 enum vga_color,
 enum vga_color);

#endif
