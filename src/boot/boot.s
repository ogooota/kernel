global loader

extern kmain

;;
;; Essas variáveis são todas definidas no linker
;;

;; Começo da memória virtual do kernel 
extern __kernel_vstart
;; Final da memória virtual do kernel
extern __kernel_vend 
;; Começo da memória física do kernel
extern __kernel_pstart
;; Final da memória física do kernel
extern __kernel_pend

;; Umas coisas do GRUB

MAGIC_NUMBER      equ 0x1BADB002
ALIGN_MODULES	  equ 0x00000001
FLAGS             equ ALIGN_MODULES
CHECKSUM          equ -(MAGIC_NUMBER + FLAGS)
;; 16kb para o kernel
KERNEL_STACK_SIZE equ 0x4000 

section .multiboot

align 4
        dd MAGIC_NUMBER 
        dd FLAGS
        dd CHECKSUM

section .text

loader:
        mov esp, kernel_stack + KERNEL_STACK_SIZE

	push eax	;; Isso é o MULTIBOOT_BOOTLOADER_MAGIC
	push ebx	;; Isso é a estrutura multiboot_info

        call kmain
.loop:
	hlt 	   ;; Isso não vai acontecer.
	jmp .loop

section .bss
align 4
kernel_stack: resb KERNEL_STACK_SIZE
