ENTRY(loader)

SECTIONS
{
        . = 0x00100000;

        PROVIDE(__kernel_start = .);

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
