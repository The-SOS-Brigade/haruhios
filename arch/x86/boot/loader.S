
.section .boot
.code16
.org 0

.type _loader STT_FUNC
.global _loader

_loader:
	cli

	lgdt gdt_desc

	movl %cr0, %eax
	orl $1, %eax
	movl %eax, %cr0

	ljmp $code_seg, $pm_entry

.code32
.extern kernel_entry

PGTABADDR = 0x1000000

pm_entry:
	movw $data_seg, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movl $0x00FFFFFF, %ebp
	movl %ebp, %esp

	inb $0x92, %al
	orb $2, %al
	outb %al, $0x92

	movl $4, %eax
	movl $50, %ecx
	movl $__kernel_start_phys, %edi
	call ata_pio28_read
	jc .Lread_error
	movl $PGTABADDR, %edi
	
	call pg_mapk2hh

	movl $PGTABADDR, %eax
	call mmu_load_pagedir
	call mmu_32bit_enable

	call kernel_entry
_exit:
.Lread_error:
	jmp _exit

