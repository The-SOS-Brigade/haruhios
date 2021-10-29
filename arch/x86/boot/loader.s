
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
	movl $0x100000, %edi
	call ata_pio28_read
	jc .Lread_error

	call kernel_entry
_exit:
.Lread_error:
	jmp _exit

