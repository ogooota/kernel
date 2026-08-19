#include <kernel/drivers/video/video.h>
#include <kernel/utils/print.h>

void kinit(void)
{
        vidinit();
}

void kmain(void)
{
        kinit();

        const char *fmt = "formatted strings!";
        printk("Hey! Now I can print %s\n", fmt);

        viddump();
}
