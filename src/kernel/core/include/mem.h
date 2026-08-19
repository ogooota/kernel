#ifndef __MEM_H
#define __MEM_H

#include "kdefs.h"

/**
 * Offsets:
 * {
 *      src = 4 bytes
 *      c   = 8 bytes
 *      n   = 12 bytes
 * }
 *
 * Escreve __n__ words de valor __c__
 * em __src__.
 */
extern void memsetb(void *src, int32 c, uint32 n);
extern void memsetw(void *src, int32 c, uint32 n);

/**
 * Versão para memória volátil
 */
extern void vmemsetw(volatile void *src, int32 c, uint32 n);

/**
 * Offsets:
 * {
 *      dst = 4 bytes
 *      src = 8 bytes
 *      n   = 12 bytes
 * }
 *
 * Copia __n__ words de __src__ para __dst__,
 * sendo __dst__ um ponteiro para memória volátil.
 */
extern void vmemcpyw(volatile void *restrict dst, const void *restrict src, uint32 n);

#endif
