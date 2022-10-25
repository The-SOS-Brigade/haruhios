.section .boot, "ax", @progbits
.code32
.global pg_idmap
.global pg_mapk2hh

pg_idmap:
	pusha

	movl %edi, %eax
	addl $0x1000, %eax
	push %eax
	orl $0b011, %eax
	movl $0x400, %ecx

	cld

.Lidmap_0:
	stosl
	addl $0x1000, %eax
	loop .Lidmap_0

	popl %edi
	movl $0b011, %eax
	movl $0x100000, %ecx
.Lidmap_1:
	stosl
	addl $0x1000, %eax
	loop .Lidmap_1

	popa
	ret

pg_mapk2hh:
	pusha

	call pg_idmap
	movl $__kernel_start_phys, %eax
	orl $0b011, %eax
	movl $0x40000, %ecx
	addl $0x301000, %edi

	cld

.Lmapk2hh_0:
	stosl
	addl $0x1000, %eax
	loop .Lmapk2hh_0

	popa
	ret

