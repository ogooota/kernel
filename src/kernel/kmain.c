#include <kernel/drivers/video/video.h>
#include <kernel/utils/print.h>
#include <kernel/core/include/gdt.h>
#include <kernel/core/include/idt.h>

void kinit(void)
{
        vidinit();
        gdt_init();
        idt_init();
        gdt_show_desc(3);
        gdt_show_desc(4);
}

void kmain(void)
{
        kinit();

        printk("After GDT\n");
        printk("After IDT\n");

        viddump();
}
