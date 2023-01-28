.section .boot, "ax", @progbits
.code32
.global pg_idmap
.global pg_mapk2hh
.global pg_enable_pse

pg_enable_pse:
	pushl %eax
	movl %cr4, %eax
	btc $4, %eax
	movl %eax, %cr4
	popl %eax
	ret

/* setup identity map using 4 MiB pages (requires PSE) */
pg_idmap:
	pusha

	movl %edi, %eax
	xorl %eax, %eax
	orl $0b10000011, %eax
	movl $0x400, %ecx
	cld
.Lidmap_0:
	stosl
	addl $0x400000, %eax
	loop .Lidmap_0

	popa
	ret

/* map kernel to higher half using 4 MiB pages (requires PSE) */
pg_mapk2hh:
	pusha

	call pg_idmap
	movl $__kernel_start, %eax
	shrl $22, %eax
	movl $4, %ebx

	movl $0x1000, %ecx
	subl %eax, %ecx

	mull %ebx
	addl %eax, %edi

	movl $__kernel_start_phys, %eax
	andl $0xffc00000, %eax
	orl $0b10000011, %eax
	cld

.Lmapk2hh_0:
	stosl
	addl $0x400000, %eax
	loop .Lmapk2hh_0

	popa
	ret

