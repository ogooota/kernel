#include <kernel/drivers/video/video.h>
#include <kernel/utils/print.h>
#include <kernel/core/include/gdt.h>
#include <kernel/core/include/idt.h>
#include <kernel/core/include/irq.h>

void kinit(void)
{
        vidinit();
        gdt_init();

        idt_init();
        irq_init();

        asm volatile("int $0x28");
}

void kmain(void)
{
        kinit();

        printk("After GDT\n");
        printk("After IDT\n");

        viddump();
}
