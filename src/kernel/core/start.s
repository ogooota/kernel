bits 32

global gdt_load

extern gdtr

gdt_load:
        lgdt [gdtr]

        mov ax, 0x10
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        jmp 0x08:next

next:
        ret


