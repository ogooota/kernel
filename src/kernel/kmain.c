#include <kernel/drivers/video/video.h>
#include <kernel/utils/print.h>
#include <kernel/core/include/gdt.h>

struct gdt gdt_main;

void kinit(void)
{
        vidinit();
        gdt_init(&gdt_main);
        printk(
                "lim_0_15:    %x\n"
                "base_16_31:  %x\n"
                "base_32_39:  %x\n"
                "access_byte: %x\n"
                "lim_48_51:   %x\n"
                "flags_52_55: %x\n"
                "base_56_63:  %x\n",
                gdt_main.ds[1].lim_0_15,
                gdt_main.ds[1].base_16_31,
                gdt_main.ds[1].base_32_39,
                gdt_main.ds[1].access_byte,
                gdt_main.ds[1].lim_48_51,
                gdt_main.ds[1].flags_52_55,
                gdt_main.ds[1].base_56_63
              );

        gdt_load();
}

void kmain(void)
{
        kinit();

        printk("After GDT\n");

        viddump();
}
