.section .boot, "ax", @progbits
.code32
.global mmu_32bit_enable
.global mmu_load_pagedir

mmu_32bit_enable:
	pushl %eax
	movl %cr0, %eax
	btsl $31, %eax
	movl %eax, %cr0
	popl %eax
	ret

mmu_load_pagedir:
	pushl %eax
	pushl %ebx
	movl %cr3, %ebx
	andl $0xFFF, %ebx
	orl %eax, %ebx
	movl %ebx, %cr3
	popl %ebx
	popl %eax
	ret

