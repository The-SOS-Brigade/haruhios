
BOOT_SIGNATURE = 0xAA55

.section .boot, "ax"
.code16
.org 0

.type _start STT_FUNC
.global _start

.extern __mbr_start
.extern _loader

_start:
	ljmp $0, $.L0
.L0:
	cli

	xorw %ax, %ax
	movw %ax, %ds
	movw %ax, %gs
	movw %ax, %fs
	movw %ax, %es
	movw %ax, %ss

	movw $__mbr_start, %bp
	movw %bp, %sp

	sti

	incb %al
	pushw %ax
	movb $2, %ah
	movw $0x7E00, %bx
	xorb %ch, %ch
	movb $2, %cl
	int $0x13
	jc load_error
	popw %bx
	cmpb %al, %bl
	jne load_error
	jmp _loader

load_error:
	movb $4, %bl
	call bios_set_bgcolor
	movw $.Lload_error_message, %si
	call bios_print
	jmp .

.Lload_error_message: .asciz "Couldn't load the second stage loader into memory"

.global bios_print
bios_print:
        pusha
        movb $0x0E, %ah
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
        movb $0x0B, %ah
        xorb %bh, %bh
        int $0x10
        popa
        ret

.org 0x1FE
.word BOOT_SIGNATURE

