#include "include/irq.h"
#include "include/io.h"
#include "kernel/core/include/idt.h"

#include <kernel/utils/print.h>

#include <kernel/drivers/video/video.h>

static void irqrmp()
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

#define PIC_EOI 0x20

static void eoi(int intno)
{
        if (intno >= 40)
        {
                outb(PIC_SLAVE_CMD, PIC_EOI);
        }

        outb(PIC_MASTER_CMD, PIC_EOI);
}

void irq_init()
{
        irqrmp();

        set_idt_gate(32, (uint32)irq0, 0x08, 0x8E);
        set_idt_gate(33, (uint32)irq1, 0x08, 0x8E);
        set_idt_gate(34, (uint32)irq2, 0x08, 0x8E);
        set_idt_gate(35, (uint32)irq3, 0x08, 0x8E);
        set_idt_gate(36, (uint32)irq4, 0x08, 0x8E);
        set_idt_gate(37, (uint32)irq5, 0x08, 0x8E);
        set_idt_gate(38, (uint32)irq6, 0x08, 0x8E);
        set_idt_gate(39, (uint32)irq7, 0x08, 0x8E);
        set_idt_gate(40, (uint32)irq8, 0x08, 0x8E);
        set_idt_gate(41, (uint32)irq9, 0x08, 0x8E);
        set_idt_gate(42, (uint32)irq10, 0x08, 0x8E);
        set_idt_gate(43, (uint32)irq11, 0x08, 0x8E);
        set_idt_gate(44, (uint32)irq12, 0x08, 0x8E);
        set_idt_gate(45, (uint32)irq13, 0x08, 0x8E);
        set_idt_gate(46, (uint32)irq14, 0x08, 0x8E);
        set_idt_gate(47, (uint32)irq15, 0x08, 0x8E);
}

void irq_handler(struct regs *regs)
{
        printk("INTNO:   %d\n"
               "ERRCODE: %d\n\n",
               regs->intno,
               regs->errcode);

        eoi(regs->intno);
}
