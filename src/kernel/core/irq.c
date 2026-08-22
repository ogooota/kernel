#include "include/irq.h"
#include "include/io.h"

void irqrmp()
{
        uint8 master_offset = 0x20;
        uint8 slave_offset  = 0x28;

        outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);
        outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4);

        outb(PIC_MASTER_DATA, master_offset);
        outb(PIC_SLAVE_DATA, slave_offset);

        outb(PIC_MASTER_DATA, (1 << CASCADE_IRQ));
        outb(PIC_SLAVE_DATA, CASCADE_IRQ);

        outb(PIC_MASTER_DATA, ICW4_8086);
        outb(PIC_SLAVE_DATA, ICW4_8086);

        outb(PIC_MASTER_DATA, 0);
        outb(PIC_SLAVE_DATA, 0);
}

