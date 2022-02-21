BOOT_SIGNATURE = 0xAA55

.section .mbr, "ax"
.code16

.type _start STT_FUNC
.global _start

__mbr_start = 0x6000
__mbr_end = __mbr_start + 0x200
__vbr_start = 0x7C00
__vbr_end = __vbr_start + 0x200

_start:
	cli

	xorw %ax, %ax
	movw %ax, %ds
	movw %ax, %gs
	movw %ax, %fs
	movw %ax, %es
	movw %ax, %ss

	movw $__mbr_start, %bp
	movw %bp, %sp

	movw $0x7C00, %si
	movw $0x6000, %di
	movw $0x200, %cx
	cld
	rep movsb
	ljmp $0, $1f
1:
	sti
	movb %dl, drive_number

	mov $4, %cx
	movw $partition1_bootable - 0x10, %bx
1:
	addw $0x10, %bx
	cmpb $0x80, (%bx)
	je load_partition
	loop 1b
	jmp no_boot

load_partition:
	movw $1, %ax
	pushw %ax
	movb $2, %ah
	movw 2(%bx), %cx
	movb 1(%bx), %dh
	movb drive_number, %dl
	movw $__vbr_start, %bx
	int $0x13
	jc load_error
	movw %bx, %si
	popw %bx
	cmpb %al, %bl
	jne load_error
	cmpw $BOOT_SIGNATURE, __vbr_end - 2
	jne no_boot
	ljmp $0, $__vbr_start

load_error:
	movw $.Lload_error_message, %si
	jmp error

no_boot:
	movw $.Lno_boot_error, %si
	jmp error

error:
	movb $4, %bl
	call bios_set_bgcolor
	call bios_print

.Lload_error_message:	.asciz "BIOS read sectors failed"
.Lno_boot_error:	.asciz "No bootable partition found"

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

bios_set_bgcolor:
        pusha
        movb $0x0B, %ah
        xorb %bh, %bh
        int $0x10
        popa
        ret

drive_number: .byte 0

.org 0x1BE

partition1_bootable:		.byte 0x00
partition1_start_head:		.byte 0x00
partition1_start_sector:	.byte 0x00 /* bits 6-7 cylinder */
partition1_start_cylinder:	.byte 0x00
partition1_systemid:		.byte 0x00
partition1_end_head:		.byte 0x00
partition1_end_sector:		.byte 0x00 /* bits 6-7 cylinder */
partition1_end_cylinder:	.byte 0x00
partition1_start_lba:		.word 0x0000, 0x0000
partition1_total_sectors:	.word 0x0000, 0x0000
partition2_bootable:		.byte 0x00
partition2_start_head:		.byte 0x00
partition2_start_sector:	.byte 0x00 /* bits 6-7 cylinder */
partition2_start_cylinder:	.byte 0x00
partition2_systemid:		.byte 0x00
partition2_end_head:		.byte 0x00
partition2_end_sector:		.byte 0x00 /* bits 6-7 cylinder */
partition2_end_cylinder:	.byte 0x00
partition2_start_lba:		.word 0x0000, 0x0000
partition2_total_sectors:	.word 0x0000, 0x0000
partition3_bootable:		.byte 0x00
partition3_start_head:		.byte 0x00
partition3_start_sector:	.byte 0x00 /* bits 6-7 cylinder */
partition3_start_cylinder:	.byte 0x00
partition3_systemid:		.byte 0x00
partition3_end_head:		.byte 0x00
partition3_end_sector:		.byte 0x00 /* bits 6-7 cylinder */
partition3_end_cylinder:	.byte 0x00
partition3_start_lba:		.word 0x0000, 0x0000
partition3_total_sectors:	.word 0x0000, 0x0000
partition4_bootable:		.byte 0x00
partition4_start_head:		.byte 0x00
partition4_start_sector:	.byte 0x00 /* bits 6-7 cylinder */
partition4_start_cylinder:	.byte 0x00
partition4_systemid:		.byte 0x00
partition4_end_head:		.byte 0x00
partition4_end_sector:		.byte 0x00 /* bits 6-7 cylinder */
partition4_end_cylinder:	.byte 0x00
partition4_start_lba:		.word 0x0000, 0x0000
partition4_total_sectors:	.word 0x0000, 0x0000

.org 0x1FE
.word BOOT_SIGNATURE

