#ifndef __IDT_H
#define __IDT_H

#include "kdefs.h"


struct idt_entry_gate
{
        /** Primeira palavra do endereço da ISR */
        uint16 offset_0_15;

        /**
         * Seletor de segmento.
         * Deve apontar para um segmento de código
         * válido da GDT.
         */
        uint16 seg_16_31;
        uint8  res_32_39; /** Reservado */

        /**
         * Flags incluem:
         * - Gate Type: Valor de 4 bits que define o tipo
         *              de portão que a entrada representa
         *              - 0101 ou 0x5: Portão de tarefa.
         *                             Para usar este, o offset deve
         *                             ser 0.
         *              - 0110 ou 0x6: Portão de interrupção
         *                             de 16 bits.
         *              - 0111 ou 0x7: Portão de armadilha
         *                             de 16 bits.
         *              - 1110 ou 0xE: Portão de interrupção
         *                             de 32 bits.
         *              - 1111 ou 0xF: Portão de armadilha
         *                             de 32 bits.
         * - Zero: é sempre zero.
         * - DPL: 2 bits que decidem o nível de privilégio necessário
         *        para acessar a interrupção via instrução INT. O
         *        Hardware ignora esse mecanismo.
         *
         * - P: Bit presente. Deve ser 1 para entrada válida.
         */
        uint8 flags_40_47;

        /** Segunda palavra do endereço da ISR */
        uint16 offset_48_63;
} _packed;

struct idtptr
{
        uint16 limit;
        uint32 base;
} _packed;

void
set_idt_gate
(int    n,
 uint32 addr,
 uint16 seg,
 uint8  flags);

void idt_init();

#include "isr.h"
void print_exception(struct regs *registers);

extern void idt_load(struct idtptr *pidt);

#endif
