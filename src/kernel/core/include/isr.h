#ifndef __ISR_H
#define __ISR_H

#include "kdefs.h"

/**
 * ISRs chamados pela CPU
 * quando ocorre alguma exceção
 */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

struct regs
{
        /**
         * Devem ser empilhados ao final
         * para garantir que o kernel
         * possa consultar os segmentos
         * de dados e restaurá-los depois.
         */
        uint32 gs;
        uint32 fs;
        uint32 es;
        uint32 ds;

        /**
         * Empurrados pela instrução
         * 'pusha' em ordem reversa à leitura.
         */
        uint32 edi;
        uint32 esi;
        uint32 ebp;
        uint32 esp;
        uint32 ebx;
        uint32 edx;
        uint32 ecx;
        uint32 eax;

        /**
         * Número da interrupção
         * e código de erro, caso
         * seja uma exceção.
         */
        uint32 intno;
        uint32 errcode;

        /**
         * Valores empilhados automaticamente
         * pela CPU.
         */
        uint32 eip;
        uint32 cs;
        uint32 eflags;
        uint32 useresp;
        uint32 ss;
} _packed;

void isr_install();

#endif
