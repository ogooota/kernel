#include "include/isr.h"
#include "include/idt.h"

#include <kernel/utils/print.h>

void isr_install()
{
        int i = 0;
        set_idt_gate(i++, (uint32)isr0, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr1, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr2, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr3, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr4, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr5, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr6, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr7, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr8, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr9, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr10, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr11, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr12, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr13, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr14, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr15, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr16, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr17, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr18, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr19, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr20, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr21, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr22, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr23, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr24, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr25, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr26, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr27, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr28, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr29, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr30, 0x08, 0x08E);
        set_idt_gate(i++, (uint32)isr31, 0x08, 0x08E);
}

