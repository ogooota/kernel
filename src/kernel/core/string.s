bits 32

global strlen

section .text

;;
;; Offsets
;; {
;;      [esp + 4] = const char *s
;; }
;;
;; Conta quantos caracteres existem em
;; __s__, desconsiderando o terminador
;; nulo.
;;
strlen:
        push edi

        mov edi, [esp + 8]
        xor ecx, ecx
.loop:
        cmp byte [edi + ecx], 0
        jz .done

        inc ecx
        jmp .loop
.done:
        mov eax, ecx
        pop edi
        ret
