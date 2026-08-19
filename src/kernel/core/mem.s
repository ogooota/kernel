bits 32

global memsetb
global memsetw
global vmemsetw
global vmemcpyw

section .text

;;
;; Offsets:
;; {
;;      [esp + 12] = uint32 n
;;      [esp + 8]  = int32  c
;;      [esp + 4]  = void  *dst
;; }
;;
;; Escreve __n__ bytes de valor __c__
;; em __dst__.
;;
memsetb:
        push edi

        mov edi, [esp + 8]

        mov eax, [esp + 12]
        and eax, 0xFF ;; Zera todos os bytes menos o último

        mov ecx, [esp + 16]

        rep stosb

        pop edi

        ret
;;
;; Offsets:
;; {
;;      [esp + 12] = uint32 n
;;      [esp + 8]  = int32  c
;;      [esp + 4]  = void  *dst
;; }
;;
;; Escreve __n__ words de valor __c__
;; em __dst__.
;;
memsetw:
        push edi

        mov edi, [esp + 8]

        mov eax, [esp + 12]
        and eax, 0xFFFF ;; Zera todas as words menos a última

        mov ecx, [esp + 16]

        rep stosw

        pop edi

        ret

;;
;; Offsets:
;; {
;;      [esp + 12] = uint32 n
;;      [esp + 8]  = int32  c
;;      [esp + 4]  = void  *dst
;; }
;;
;; Escreve __n__ words de valor __c__
;; em __dst__, sendo __dst__ um ponteiro
;; para memória volátil.
;;
;; A diferença entre 'vmemsetw' e 'memsetw' é
;; apenas na declaração contida em 'mem.h',
;; por isso é executado apenas um pulo para
;; 'memsetw'.
;;
vmemsetw:
        jmp memsetw


;;
;; Offsets:
;; {
;;      [esp + 12] = uint32      n
;;      [esp + 8]  = const void *src
;;      [esp + 4]  = void       *dst
;; }
;;
;; Copia __n__ words de __src__ para __dst__,
;; sendo __dst__ um ponteiro para memória volátil.
;;
vmemcpyw:
        push edi
        push esi

        mov esi, [esp + 16]
        mov edi, [esp + 12]
        mov ecx, [esp + 20]

        rep movsw

        pop esi
        pop edi

        ret
