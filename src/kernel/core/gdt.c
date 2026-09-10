#include <kernel/utils/print.h>

#include "include/gdt.h"

#include "include/mem.h"
#include "include/tss.h"

struct tss    tss;
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

void gdt_init(uint32 sbss)
{
        /**
         * Primeiro é nulo
         */
        gdt_dsadd(&gdt, 0, 0, 0, 0, 0);

        /**
         * Segmento de código e dados do kernel
         */
        gdt_dsadd(&gdt, 1, 0, 0xFFFFF, KERNEL_CS_ACCESS, 0xC);
        gdt_dsadd(&gdt, 2, 0, 0xFFFFF, KERNEL_DS_ACCESS, 0xC);

        /**
         * Segmento de código e dados do usuário
         */
        gdt_dsadd(&gdt, 3, 0, 0xFFFFF, USER_CS_ACCESS, 0xC);
        gdt_dsadd(&gdt, 4, 0, 0xFFFFF, USER_DS_ACCESS, 0xC);

	/**
	 * TSS 
	 */
	gdt_dsadd(&gdt, 5, (uint32)&tss, sizeof(tss), 0xE9, 0);

	memsetb((uint8 *)&tss, 0, sizeof(tss));

	tss.iobp = (uint16)sizeof(tss);
	tss.esp0 = sbss;
	tss.ss0  = 0x10;
	tss.cs   = 0;
	tss.ss   = 0x13;
	tss.ds   = 0x13;
	tss.es   = 0x13;
	tss.fs   = 0x13;
	tss.gs   = 0x13;

        gdt.ds_amt = 6;

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
