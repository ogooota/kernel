

global outb

;;
;; Sends a byte to an I/O port
;;
;; Following the __cdecl calling convention,
;; arguments should be provided on the stack.
;; Stack: [esp + 8] the data byte
;;        [esp + 4] the I/O port
;;        [esp]     return address
;;
outb:
        mov al, [esp + 8]
        mov dx, [esp + 4]
        out dx, al
        ret
