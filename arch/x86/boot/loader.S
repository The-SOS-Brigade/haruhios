.section .boot.entry
.code16

.type _loader STT_FUNC
.global _loader

_loader:
	cli
	lgdt gdt_desc

	movl %cr0, %eax
	orl $1, %eax
	movl %eax, %cr0

	ljmp $code_seg, $pm_entry

.section .boot
.code32
.extern __kernel_start
.extern kernel_entry
.extern pg_mapk2hh

#include <asm/bpb.h>

PGTABADDR = 0x1000000
kernel_filename: .ascii "KERNEL  SYS"

pm_entry:
	movw $data_seg, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movl $0x07C00, %ebp
	movl %ebp, %esp

	inb $0x92, %al
	orb $2, %al
	outb %al, $0x92

	call prepare_canary

	movl EBPB_ROOT_CLUSTER, %eax
	movl $0x9000, %edi
	call read_cluster
	jc .Lread_error
search_kernel:
	xorl %ecx, %ecx
	movw $8, %cx
	cld
1:
	pushl %ecx
	movw $11, %cx
	movl $kernel_filename, %esi
	pushl %edi
	repe cmpsb
	popl %edi
	popl %ecx
	je load_kernel
	addl $32, %edi
	loop 1b
.Lkernel_not_found:
	jmp _exit
load_kernel:
	movl 20(%edi), %eax
	shll $16, %eax
	movw 26(%edi), %ax
	movl $__kernel_start_phys, %edi
	call read_file
	jc .Lread_error
	movl $PGTABADDR, %edi

	call pg_mapk2hh

	movl $PGTABADDR, %eax
	call mmu_load_pagedir
	call mmu_32bit_enable

	call __kernel_start

.Lread_error:
_exit:
	jmp _exit

prepare_canary:
#if CONFIG_X86_CPUID
	movl $1, %eax
	xorl %ecx, %ecx
	cpuid
	testl $0x40000000, %ecx
	jz 2f
1:
	rdrand %eax
	jnc 1b
	movl %eax, 0x500
2:
#endif
	ret

