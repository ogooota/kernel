#include "include/gdt.h"

#include <kernel/utils/print.h>

struct gdtr gdtr;

void gdt_dsadd
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

void gdt_init(struct gdt *table)
{
        if (table == NULL)
        {
                printk("null table\n");
                return;
        }

        uint8 i = 0;

        /**
         * Primeiro é nulo
         */
        gdt_dsadd(table, i++, 0, 0, 0, 0);

        /**
         * Segmento de código e dados do kernel
         */
        gdt_dsadd(table, i++, 0, 0xFFFFF, KERNEL_CS_ACCESS, 0xC);
        gdt_dsadd(table, i++, 0, 0xFFFFF, KERNEL_DS_ACCESS, 0xC);

        /**
         * Segmento de código e dados do usuário
         */
        gdt_dsadd(table, i++, 0, 0xFFFFF, USER_CS_ACCESS, 0xC);
        gdt_dsadd(table, i++, 0, 0xFFFFF, USER_DS_ACCESS, 0xC);

        table->ds_amt = i;

        gdtr.limit = (sizeof(struct gdt_segdesc) * i) - 1;
        gdtr.base  = (uint32)&table->ds;
}

