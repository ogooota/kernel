#ifndef __GDT_H
#define __GDT_H

#include "kdefs.h"

struct gdt_segdesc
{
        uint16 lim_0_15;
        uint16 base_16_31;
        uint8  base_32_39;

        /**
         * Byte de Acesso:
         * +---+---+---+---+---+----+----+---+
         * | 7 | 6 | 5 | 4 | 3 |  2 |  1 | 0 |
         * +---+-------+---+---+----+----+---+
         * | P |  DPL  | S | E | DC | RW | A |
         * +---+-------+---+---+----+----+---+
         *
         * P:   Bit presente. Permite com que a
         *      entrada se refira a um segmento
         *      válido.
         *
         * DPL: (D)escriptor (P)rivilege (L)evel.
         *      Nível de privilégio do descritor.
         *      Descreve qual anel de acesso o
         *      segmento possui.
         *              Anel 0:      Kernel
         *              Anéis 1 e 2: Não utilizados (por enquanto).
         *              Anel 3:      Usuário.
         *
         * S:   Bit de tipo do descritor.
         *      0 para segmentos de Código/Dados.
         *      1 para segmento de sistema (ver TSS).
         *
         * E:   Bit executável.
         *      0 para segmento de dados.
         *      1 para segmento de código.
         *
         * DC:  Bit de direção/conformidade.
         *      Para dados:
         *              Bit de direção.
         *              0 para crescer para cima (ex.: Heap).
         *              1 para crescer para baixo (ex.: Stack).
         *
         *      Para código:
         *              Bit de conformidade.
         *              0 para configurar a execução
         *              apenas para o anel do DPL.
         *              1 para configurar a execução
         *              para anéis iguais (==) ou
         *              menores que (<) o DPL atual.
         *
         * RW:  (R)eadable/(W)ritable bit.
         *      Bit de leitura/escrita.
         *      Para dados:
         *              Bit de escrita.
         *              0 para não poder escrever.
         *              1 para poder escrever.
         *              Leitura é sempre ativa para
         *              segmentos de dados.
         *
         *      Para código:
         *              Bit de leitura.
         *              0 para não poder ler.
         *              1 para poder ler.
         *              Escrita NUNCA é ativa para
         *              segmentos de código.
         *
         * A:   Bit acessado.
         *      A própria CPU seta esse bit quando
         *      o segmento é acessado, a não ser
         *      que ele já esteja setado.
         *      Caso esteja setado, joga uma page-fault,
         *      por isso é melhor sempre setar.
         */
        uint8  access_byte;

        uint8  lim_48_51: 4;

        /**
         * Flags:
         *
         * +---+----+---+-----------+
         * | 3 |  2 | 1 |     0     |
         * +---+----+---+-----------+
         * | G | DB | L | Reservado |
         * +---+----+---+-----------+
         *
         * G: Bit de granularidade (IMPORTANTE!!!)
         *    Dita o a escala que o Limit é multiplicado.
         *    0 para 1 byte.
         *    1 para 4kb.
         *
         * DB: Flag de tamanho.
         *     0 para segmento protegido de 16 bits.
         *     1 para segmento protegido de 32 bits.
         *
         * L:  Modo Longo
         *     1 para ativar o modo 64 bits.
         *     Caso seja 1, o DB deve ser 0.
         *     Deve sempre ser 0.
         */
        uint8  flags_52_55: 4;


        uint8  base_56_63;
} _packed;

/**
 * Número máximo de descritores admitidamente roubado de
 * https://github.com/hllustosa/feso-operating-system/blob/master/src/kernel/include/Gdt.h
 */
#define MAXDS 24

/**
 * Bytes de acesso
 */
#define KERNEL_CS_ACCESS 0x9A
#define KERNEL_DS_ACCESS 0x92
#define USER_CS_ACCESS   0xFA
#define USER_DS_ACCESS   0xF2
#define TSS_ACCESS       0x89

struct gdt
{
        struct gdt_segdesc ds[MAXDS];
        uint8              ds_amt;
} _packed;

struct gdtr
{
        uint16 limit;
        uint32 base;
} _packed;

void gdt_dsadd
(struct gdt *table,
 uint8       n,
 uint32      base,
 uint32      lim,
 uint8       access,
 uint8       flags);

void gdt_init(struct gdt *table);

extern void gdt_load();

#endif
