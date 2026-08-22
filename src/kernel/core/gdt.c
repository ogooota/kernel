#include "include/gdt.h"

#include <kernel/utils/print.h>

struct gdt    gdt;
struct gdtptr pgdt;

static void gdt_dsadd
(struct gdt *table,
 uint8       n,
 uint32      base,
 uint32      lim,
 uint8       access,
 uint8       flags)
{
        if (table == NULL ||
            n >= MAXDS)
        {
                printk("could not add descriptor entry\n");
                return;
        }

        struct gdt_segdesc *ds = &table->ds[n];

        ds->lim_0_15    = lim & 0xFFFF;
        ds->lim_48_51   = (lim >> 16) & 0x0F;
        ds->flags_52_55 = flags & 0x0F;

        ds->base_16_31 = base & 0xFFFF;
        ds->base_32_39 = (base >> 16) & 0xFF;
        ds->base_56_63 = (base >> 24) & 0xFF;

        ds->access_byte = access;
}

extern void gdt_load();

void gdt_init()
{
        uint8 i = 0;

        /**
         * Primeiro é nulo
         */
        gdt_dsadd(&gdt, i++, 0, 0, 0, 0);

        /**
         * Segmento de código e dados do kernel
         */
        gdt_dsadd(&gdt, i++, 0, 0xFFFFF, KERNEL_CS_ACCESS, 0xC);
        gdt_dsadd(&gdt, i++, 0, 0xFFFFF, KERNEL_DS_ACCESS, 0xC);

        /**
         * Segmento de código e dados do usuário
         */
        gdt_dsadd(&gdt, i++, 0, 0xFFFFF, USER_CS_ACCESS, 0xC);
        gdt_dsadd(&gdt, i++, 0, 0xFFFFF, USER_DS_ACCESS, 0xC);

        gdt.ds_amt = i;

        pgdt.limit = (sizeof(struct gdt_segdesc) * MAXDS) - 1;
        pgdt.base  = (uint32)&gdt.ds;

        gdt_load();
}

void gdt_show_desc(int n)
{
        struct gdt_segdesc curr = gdt.ds[n];

        printk("Descriptor number %d:\n", n);

        printk("lim_0_15:    %x\n"
               "base_16_31:  %x\n"
               "base_32_39:  %x\n"
               "access_byte: %x\n"
               "lim_48_51:   %x\n"
               "flags_52_55: %x\n"
               "base_56_63:  %x\n\n",
               curr.lim_0_15,
               curr.base_16_31,
               curr.base_32_39,
               curr.access_byte,
               curr.lim_48_51,
               curr.flags_52_55,
               curr.base_56_63);
}
