bits 32

global gdt_load

extern pgdt

section .text

gdt_load:
        lgdt [pgdt]

        mov ax, 0x10
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        jmp 0x08:.ret

.ret:
        ret


global idt_load
;;
;; Offsets
;; {
;;      [esp + 4] = struct idtptr *pidt
;; }
;;
;; Recebe um ponteiro
;; para uma entrada que
;; representa um ponteiro
;; para a idt
;;
idt_load:
        mov eax, [esp + 4]
        lidt [eax]
        ret

;;
;; Declarações de ISRs
;;
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

extern isr_common_stub

;;
;; Divide Error
;;
isr0:
        cli
        push byte 0
        push byte 0
        jmp isr_common_stub
;;
;; Debug Exception
;;
isr1:
        cli
        push byte 0
        push byte 1
        jmp isr_common_stub

;;
;; NMI(Non Maskable Interrupt) Exception
;;
isr2:
        cli
        push byte 0
        push byte 2
        jmp isr_common_stub

;;
;; Breakpoint
;;
isr3:
        cli
        push byte 0
        push byte 3
        jmp isr_common_stub
;;
;; Overflow
;;
isr4:
        cli
        push byte 0
        push byte 4
        jmp isr_common_stub
;;
;; Out of Bounds
;;
isr5:
        cli
        push byte 0
        push byte 5
        jmp isr_common_stub
;;
;; Ivalid Opcode
;;
isr6:
        cli
        push byte 0
        push byte 6
        jmp isr_common_stub
;;
;; Device Not Available
;;
isr7:
        cli
        push byte 0
        push byte 7
        jmp isr_common_stub
;;
;; Double Fault
;; Tem errcode.
;;
isr8:
        cli
        push byte 8
        jmp isr_common_stub
;;
;; Coprocessor Segment Overrun
;;
isr9:
        cli
        push byte 0
        push byte 9
        jmp isr_common_stub
;;
;; Invalid TSS(Task State Segment)
;; Tem errcode.
;;
isr10:
        cli
        push byte 0xA
        jmp isr_common_stub
;;
;; Segment Not Present
;; Tem errcode.
;;
isr11:
        cli
        push byte 0xB
        jmp isr_common_stub

;;
;; Stack-Segment Fault
;; Tem errcode.
;;
isr12:
        cli
        push byte 0xC
        jmp isr_common_stub
;;
;; General Protection
;; Tem errcode.
;;
isr13:
        cli
        push byte 0xD
        jmp isr_common_stub
;;
;; Page Fault
;; Tem errcode.
;;
isr14:
        cli
        push byte 0xE
        jmp isr_common_stub
;;
;; Reservado. Não utilizar
;;
isr15:
        cli
        push byte 0
        push byte 0xF
        jmp isr_common_stub
;;
;; Floating-Point Error
;;
isr16:
        cli
        push byte 0
        push byte 0x10
        jmp isr_common_stub
;;
;; Alignment Check
;; Tem errcode.
;;
isr17:
        cli
        push byte 0x11
        jmp isr_common_stub
;;
;; Machine Check
;;
isr18:
        cli
        push byte 0
        push byte 0x12
        jmp isr_common_stub
;;
;; SIMD Floating-Point Exception
;;
isr19:
        cli
        push byte 0
        push byte 0x13
        jmp isr_common_stub
;;
;; Virtualization Exception
;;
isr20:
        cli
        push byte 0
        push byte 0x14
        jmp isr_common_stub
;;
;; Control Protection
;; Tem errcode.
;;
isr21:
        cli
        push byte 0x15
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr22:
        cli
        push byte 0
        push byte 0x16
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr23:
        cli
        push byte 0
        push byte 0x17
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr24:
        cli
        push byte 0
        push byte 0x18
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr25:
        cli
        push byte 0
        push byte 0x19
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr26:
        cli
        push byte 0
        push byte 0x1A
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr27:
        cli
        push byte 0
        push byte 0x1B
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr28:
        cli
        push byte 0
        push byte 0x1C
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr29:
        cli
        push byte 0
        push byte 0x1D
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr30:
        cli
        push byte 0
        push byte 0x1E
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr31:
        cli
        push byte 0
        push byte 0x1F
        jmp isr_common_stub

extern print_exception

isr_common_stub:
        pusha
        push ds
        push es
        push fs
        push gs

        mov eax, esp
        push eax

        call print_exception

        pop eax
        pop gs
        pop fs
        pop es
        pop ds
        popa
        add esp, 8
        iret

