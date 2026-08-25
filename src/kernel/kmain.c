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

        /**
         * IMPORTANTE!
         *      Aqui deve-se tratar a interrupção.
         *      Devido a algumas interrupções serem classificadas
         *      como 'fault', EIP não avança quando é salvo na stack,
         *      é apenas salvo o valor atual de EIP, e por isso,
         *      acaba-se travando o sistema, porque assim que a
         *      interrupção acaba, o kernel lê de novo a
         *      instrução que a causou, fazendo um loop infinito.
         *
         *      Tenho que achar uma forma de tratar essas interrupções,
         *      não posso apenas fingir que não existem.
         */
        // asm volatile("int $0xa");
}

void kmain(void)
{
        kinit();

        printk("After GDT\n");
        printk("After IDT\n");

        viddump();
}
