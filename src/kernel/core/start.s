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
        push byte 10
        jmp isr_common_stub
;;
;; Segment Not Present
;; Tem errcode.
;;
isr11:
        cli
        push byte 11
        jmp isr_common_stub

;;
;; Stack-Segment Fault
;; Tem errcode.
;;
isr12:
        cli
        push byte 12
        jmp isr_common_stub
;;
;; General Protection
;; Tem errcode.
;;
isr13:
        cli
        push byte 13
        jmp isr_common_stub
;;
;; Page Fault
;; Tem errcode.
;;
isr14:
        cli
        push byte 14
        jmp isr_common_stub
;;
;; Reservado. Não utilizar
;;
isr15:
        cli
        push byte 0
        push byte 15
        jmp isr_common_stub
;;
;; Floating-Point Error
;;
isr16:
        cli
        push byte 0
        push byte 16
        jmp isr_common_stub
;;
;; Alignment Check
;; Tem errcode.
;;
isr17:
        cli
        push byte 17
        jmp isr_common_stub
;;
;; Machine Check
;;
isr18:
        cli
        push byte 0
        push byte 18
        jmp isr_common_stub
;;
;; SIMD Floating-Point Exception
;;
isr19:
        cli
        push byte 0
        push byte 19
        jmp isr_common_stub
;;
;; Virtualization Exception
;;
isr20:
        cli
        push byte 0
        push byte 20
        jmp isr_common_stub
;;
;; Control Protection
;; Tem errcode.
;;
isr21:
        cli
        push byte 21
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr22:
        cli
        push byte 0
        push byte 22
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr23:
        cli
        push byte 0
        push byte 23
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr24:
        cli
        push byte 0
        push byte 24
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr25:
        cli
        push byte 0
        push byte 25
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr26:
        cli
        push byte 0
        push byte 26
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr27:
        cli
        push byte 0
        push byte 27
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr28:
        cli
        push byte 0
        push byte 28
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr29:
        cli
        push byte 0
        push byte 29
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr30:
        cli
        push byte 0
        push byte 30
        jmp isr_common_stub
;;
;; Reservado. Não utilizar.
;;
isr31:
        cli
        push byte 0
        push byte 31
        jmp isr_common_stub

extern print_exception

isr_common_stub:
        ;;
        ;; É importante ressaltar
        ;; que neste ponto do código,
        ;; a CPU já salvou automaticamente
        ;; ss, useresp, eflags, cs, eip.
        ;;
        ;;
        ;;
        ;; Logo antes da chamada desta
        ;; função, foram salvos
        ;; o código de erro, e o
        ;; número da interrupção,
        ;; respectivamente.
        ;;
        ;;
        ;;
        ;; Falta salvar o contexto
        ;; dos registradores, com
        ;; 'pusha', e os segmentos
        ;; ds, es, fs, gs,
        ;; respectivamente.
        ;;
        ;;
        ;;
        ;; Salva os registradores
        ;; nesta ordem:
        ;;      eax, ecx, edx, ebx
        ;;      esp, ebp, esi, edi
        ;;
        pusha
        push ds
        push es
        push fs
        push gs

        ;;
        ;; A partir daqui, é transferido
        ;; o segmento de dados do kernel.
        ;; (0x10 é a entrada número 2 da
        ;; GDT, que corresponde ao descritor
        ;; do segmento de dados do kernel)
        ;;
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        ;;
        ;; Então é feita a
        ;; chamada para a função de
        ;; tratamento.
        ;;
        ;; Neste ponto, apenas
        ;; mostro a interrupção
        ;; na tela.
        ;;
        mov eax, esp
        push eax
        call print_exception

        ;;
        ;; Após tratar a interrupção,
        ;; restaura-se o contexto em que
        ;; o programa se encontrava,
        ;; e segue-se normalmente.
        ;;
        pop eax
        pop gs
        pop fs
        pop es
        pop ds

        ;;
        ;; Restaura os valores contidos
        ;; nos registradores.
        ;;
        popa

        ;;
        ;; Remove o código de erro
        ;; e número de interrupção
        ;; da stack.
        ;;
        add esp, 8

        iret


;;
;; IRQs
;;
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
        cli
        push byte 0
        push byte 32
        jmp irq_common_stub
irq1:
        cli
        push byte 0
        push byte 33
        jmp irq_common_stub
irq2:
        cli
        push byte 0
        push byte 34
        jmp irq_common_stub
irq3:
        cli
        push byte 0
        push byte 35
        jmp irq_common_stub
irq4:
        cli
        push byte 0
        push byte 36
        jmp irq_common_stub
irq5:
        cli
        push byte 0
        push byte 37
        jmp irq_common_stub
irq6:
        cli
        push byte 0
        push byte 38
        jmp irq_common_stub
irq7:
        cli
        push byte 0
        push byte 39
        jmp irq_common_stub
irq8:
        cli
        push byte 0
        push byte 40
        jmp irq_common_stub
irq9:
        cli
        push byte 0
        push byte 41
        jmp irq_common_stub
irq10:
        cli
        push byte 0
        push byte 42
        jmp irq_common_stub
irq11:
        cli
        push byte 0
        push byte 43
        jmp irq_common_stub
irq12:
        cli
        push byte 0
        push byte 44
        jmp irq_common_stub
irq13:
        cli
        push byte 0
        push byte 45
        jmp irq_common_stub
irq14:
        cli
        push byte 0
        push byte 46
        jmp irq_common_stub
irq15:
        cli
        push byte 0
        push byte 47
        jmp irq_common_stub

extern irq_handler

irq_common_stub:
        pusha
        push ds
        push es
        push fs
        push gs

        mov eax, esp
        push eax
        call irq_handler

        pop eax
        pop gs
        pop fs
        pop es
        pop ds

        popa

        add esp, 8

        iret
