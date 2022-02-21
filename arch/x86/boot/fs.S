.section .boot
.code32

#include <asm/bpb.h>

.global read_cluster
read_cluster:
	pusha
	xorl %ecx, %ecx
	subl $2, %eax
	movb BPB_SPC, %cl
	mulb %cl
	addl EBPB_RESERVED0, %eax
	call ata_pio28_read
	popa
	ret

.global read_file
read_file:
	pusha
	xorl %ebx, %ebx
	xorl %ecx, %ecx
	pushl %eax
	xorl %eax, %eax
	movw BPB_BPS, %ax
	movb BPB_SPC, %cl
	mull %ecx
	movl %eax, %ecx
	popl %eax
1:
	call read_cluster
	jc 1f
	addl %ecx, %edi

	pushl %eax
	movl %edi, %ebx
	movl $0x7E00, %edi
	shll $2, %eax
	xorl %edx, %edx
	divw BPB_BPS
	addw BPB_RESERVED, %ax
	addl BPB_HIDDEN, %eax
	pushl %ecx
	xorl %ecx, %ecx
	movb BPB_SPC, %cl
	call ata_pio28_read
	popl %ecx
	popl %eax
	jc 1f

	addl %edx, %edi
	movl (%edi), %eax
	andl $0x0FFFFFFF, %eax
	cmpl $0x0FFFFFF8, %eax
	movl %ebx, %edi
	jb 1b
1:
	popa
	ret
