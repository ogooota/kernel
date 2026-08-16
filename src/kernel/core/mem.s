
global memsetb
global memsetw
global vmemsetw

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
        mov edi, [esp + 4]
        mov al,  [esp + 8]
        mov ecx, [esp + 12]

        rep stosb

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
        mov edi, [esp + 4]
        mov ax,  [esp + 8]
        mov ecx, [esp + 12]

        rep stosw

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
vmemsetw:
        mov edi, [esp + 4]
        mov ax,  [esp + 8]
        mov ecx, [esp + 12]

        rep stosw

        ret
