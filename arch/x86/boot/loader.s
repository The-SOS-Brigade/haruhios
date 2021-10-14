
.section .text
.code16
.org 0

.type _loader STT_FUNC
.global _loader

_loader:
	cli
	
	inb $0x92, %al
	or $2, %al
	outb %al, $0x92

	lgdt gdt_desc
	
	mov %cr0, %eax
	or $1, %eax
	mov %eax, %cr0

	ljmp $code_seg, $pm_entry

.code32
pm_entry:
	mov $data_seg, %eax
	mov %eax, %ds
	mov %eax, %ss
	mov %eax, %es
	mov %eax, %fs
	mov %eax, %gs

_exit:
	jmp _exit

