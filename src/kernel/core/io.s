

global outb
global inb

;;
;; Offsets:
;; {
;;      [esp + 8] = uchar  data
;;      [esp + 4] = uint16 port
;; }
;;
;; Envia um byte para uma porta I/O
;;
;; De acordo com a convenção de chamada __cdecl,
;; argumentos devem ser providos na stack.
;;
outb:
        mov al, [esp + 8]
        mov dx, [esp + 4]
        out dx, al
        ret

;;
;; Offsets:
;; {
;;      [esp + 4] = uint16 port
;; }
;;
;; Lê um byte de uma porta I/O
;;
inb:
        mov dx, [esp + 4]
        in al, dx
        ret
