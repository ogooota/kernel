#include "vga.h"

#include <kernel/core/mem.h>
#include <kernel/core/io.h>

static volatile uint16 *vmem = (volatile uint16 *)VGA_ADDR;
static struct vga_cursor cursor;

uint16 vga_mkcell(const uchar c, enum vga_color fg, enum vga_color bg)
{
        /**
         * Color byte:
         * {
         *    0000 -> Holds the background color -> Black
         *    0111 -> Holds the foregound color  -> Light Grey
         * }
         */
        uint8 color = (uint8)(((bg << 4) & 0xFFu) |
                               (fg & 0xFFu));

         /**
         * Cell word:
         * {
         *    0000 0111 -> Holds the color     -> (Black, Light Grey)
         *    0110 1000 -> Holds the character -> H
         * }
         */
        uint16 cell = (uint16)((uint16)c |
                                (uint16)(color << 8));

        return cell;
}

void vga_clear(const uint16 cell)
{
        vmemsetw(vmem, cell, VGA_AREA);
}

void vga_init()
{
        uint16 cell = vga_mkcell(' ', VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        vga_clear(cell);
        vga_cursor_init(&cursor);
        vga_cursor_move(0, 0);
}

void vga_cursor_move(const uint16 x, const uint16 y)
{
        if (x >= VGA_WIDTH ||
            y >= VGA_HEIGHT)
        {
          return;
        }

        uint16 pos = y * VGA_WIDTH + x;

        /**
         * Prepara o registrador do low byte
         * para receber um valor, escrevendo seu
         * endereço na porta de controle.
         */
        outb(CRTC_CTL_PORT, CRTC_LOW_BYTE_REG);

        /**
         * Escreve o byte inferior de 'pos'
         * no registrador do low byte,
         * escrevendo seu valor na porta de dados.
         */
        outb(CRTC_DATA_PORT, (pos & 0xFF));

        /**
         * Prepara o registrador do high byte
         * para receber um valor, escrevendo seu
         * endereço na porta de controle.
         */
        outb(CRTC_CTL_PORT, CRTC_HIGH_BYTE_REG);

        /**
         * Escreve o byte superior de 'pos'
         * no registrador do high byte,
         * escrevendo seu valor na porta de dados.
         */
        outb(CRTC_DATA_PORT, ((pos >> 8) & 0xFF));

        /**
         * Atualizar x e y do cursor
         */
        cursor.x = x;
        cursor.y = y;
}

void vga_putcell(const uint16 cell)
{
        vmem[cursor.y * VGA_WIDTH + cursor.x] = cell;
}

void vga_putcell_abs(const uint16 cell, const uint16 pos)
{
        vmem[pos] = cell;
}

void vga_putstream(const uint16 *stream, const uint32 size)
{
        if (stream == NULL)
        {
                return;
        }

        uint8 x = cursor.x;
        uint8 y = cursor.y;

        uint16 abs = y * VGA_WIDTH + x;

        if (abs + size >= VGA_AREA)
        {
                /**
                 * TODO: Decidir o que fazer quando o texto
                 * for maior do que a tela.
                 *
                 * Opção 1: Resetar o cursor para (0, 0)
                 * Opção 2: Calcular a posição com móulo para
                 *          quando x >= largura ou y >= altura
                 */
                return;
        }

        for (uint16 i = 0; i < size; i++)
        {
                vga_putcell_abs(stream[i], abs + i);
        }
}

void vga_cursor_init(struct vga_cursor *cursor)
{
        if (cursor == NULL)
        {
                return;
        }

        memsetb(cursor, 0, sizeof(*cursor));
}

void vga_atos(const char *s, const uint32 size, uint16 *out)
{
        if (s   == NULL ||
            out == NULL)
        {
                return;
        }

        for (uint32 i = 0; i < size; i++)
        {
                out[i] = vga_mkcell(s[i], VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        }
}

void vga_flush(const uint16 *stream)
{
        vmemcpyw(vmem, stream, VGA_AREA);
}
