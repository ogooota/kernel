#include <kernel/drivers/video/video.h>
#include <kernel/utils/print.h>
#include <kernel/core/include/gdt.h>
#include <kernel/core/include/idt.h>

void kinit(void)
{
        vidinit();
        gdt_init();
        idt_init();

        // asm volatile("ud2");
        asm volatile("int $0x3");
}

void kmain(void)
{
        kinit();

        printk("After GDT\n");
        printk("After IDT\n");

        viddump();
}
