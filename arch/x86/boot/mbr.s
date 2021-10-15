
BOOT_SIGNATURE = 0xAA55

.section .mbr_text, "ax"
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

	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %gs
	mov %ax, %fs
	mov %ax, %es
	mov %ax, %ss

	mov $__mbr_start, %bp
	mov %bp, %sp

	sti

	inc %al
	push %ax
	mov $2, %ah
	mov $0x7E00, %bx
	xor %ch, %ch
	mov $2, %cl
	int $0x13
	jc load_error
	pop %bx
	cmp %al, %bl
	jne load_error
	jmp _loader

load_error:
	mov $4, %bl
	call bios_set_bgcolor
	mov $.Lload_error_message, %si
	call bios_print
	jmp .

.Lload_error_message: .ascii "Couldn't load the second stage loader into memory"

.org 0x1FE
.word BOOT_SIGNATURE

