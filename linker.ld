ENTRY(loader)

SECTIONS
{
        . = 0x00100000;
	

        PROVIDE(__kernel_pstart = .);

        /**
         * Garantindo que a seção
         * .multiboot vem antes de
         * qualquer outra coisa,
         * para evitar o erro 13 do
         * GRUB de não encontrar o
         * formato correto de ELF
         */
        .multiboot ALIGN (4K) :         {
                *(.multiboot)
        }

        .text ALIGN (4K) :         {
                *(.text)
        }

        .rodata ALIGN (4K) : 
        {
                *(.rodata*)
        }

        .data ALIGN (4K) : 
        {
                *(.data)
        }

        .bss ALIGN (4K) : 
        {
                *(COMMON*)
                *(.bss)
        }

        PROVIDE(__kernel_pend = .);

        /DISCARD/ :
        {
                *(.eh_frame .note.GNU-stack)
        }
}
