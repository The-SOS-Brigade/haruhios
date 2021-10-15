
.section .boot

.code16

.global bios_print
bios_print:
        pusha
        mov $0x0E, %ah
.Lloop_bios_print:
        lodsb
        int $0x10
        cmpb $0, (%si)
        jne .Lloop_bios_print
        popa
        ret

.global bios_set_bgcolor
bios_set_bgcolor:
        pusha
        mov $0x0B, %ah
        xor %bh, %bh
        int $0x10
        popa
        ret

