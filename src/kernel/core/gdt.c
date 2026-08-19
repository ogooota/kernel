#include "include/gdt.h"


void gdt_dsadd
(struct gdt *table,
 uint8       n,
 uint32      base,
 uint32      lim,
 uint8       dpl,
 uint8       gran)
{
        struct gdt_segdesc *ds = &table->ds[n];
        ds->lim_0_15 = lim & 0xFFFF;
        ds->lim_48_51 = (lim << 16) & 0x0F;

        ds->base_16_31 = base & 0xFFFF;
        ds->base_32_39 = (base << 16) & 0xFF;
        ds->base_56_63 = (base << 24) & 0xFF;

        ds->access_byte |= (dpl << 5);
        ds->flags_52_55 |= (gran << 3);
}
