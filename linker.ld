ENTRY(loader)

SECTIONS
{
        . = 0x00100000;

        PROVIDE(__kernel_start = .);

        /**
         * Garantindo que a seção
         * .multiboot vem antes de
         * qualquer outra coisa,
         * para evitar o erro 13 do
         * GRUB de não encontrar o
         * formato correto de ELF
         */
        .multiboot ALIGN (4K) :
        {
                *(.multiboot)
        }

        .text ALIGN (4K) :
        {
                *(.text)
        }

        PROVIDE(etext = .);

        .rodata ALIGN (4K) :
        {
                *(.rodata*)
        }

        PROVIDE(data = .);

        .data ALIGN (4K) :
        {
                *(.data)
        }

        PROVIDE(edata = .);

        .bss ALIGN (4K) :
        {
                *(COMMON*)
                *(.bss)
        }

        PROVIDE(__kernel_end = .);

        /DISCARD/ :
        {
                *(.eh_frame .note.GNU-stack)
        }
}
