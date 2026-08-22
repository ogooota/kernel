#include "include/idt.h"
#include "include/isr.h"

#include <kernel/utils/print.h>
#include <kernel/drivers/video/video.h>

#define MAXENTRIES 256

/**
 * Esse vetor de entradas
 * deve ser preenchido
 * com os endereços das ISRs.
 * Ver isr_install() em isr.c.
 */
struct idt_entry_gate idt_entries[MAXENTRIES];
struct idtptr         pidt;

void
set_idt_gate
(int    n,
 uint32 addr,
 uint16 seg,
 uint8  flags)
{
        struct idt_entry_gate *entry = &idt_entries[n];

        entry->offset_0_15  = addr & 0xFFFF;
        entry->offset_48_63 = (addr >> 16) & 0xFFFF;
        entry->seg_16_31    = seg;
        entry->flags_40_47  = flags;
}


void idt_init()
{

        pidt.limit = (sizeof(struct idt_entry_gate) * MAXENTRIES) - 1;
        pidt.base  = (uint32)&idt_entries;

        isr_install();

        idt_load(&pidt);
}

static void panic()
{
        printk("\nKERNEL PANIC\n");

        viddump();

        while (1)
        {
                asm volatile("hlt");
        }
}

void print_exception(struct regs *registers)
{
        printk("INTERRUPTION NUMBER: %d\n"
               "ERROR CODE:          %d\n",
               registers->intno,
               registers->errcode ? registers->errcode : 0);

        panic();
}
