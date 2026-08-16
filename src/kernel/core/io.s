

global outb

global inb

;;
;; Envia um byte para uma porta I/O
;;
;; De acordo com a convenção de chamada __cdecl,
;; argumentos devem ser providos na stack.
;; Stack: [esp + 8] O byte
;;        [esp + 4] A porta I/O
;;
outb:
        mov al, [esp + 8]
        mov dx, [esp + 4]
        out dx, al
        ret

;;
;; Lê um byte de uma porta I/O
;;
;; Stack: [esp + 4] A porta I/O
;;
inb:
        mov dx, [esp + 4]
        in al, dx
        ret
