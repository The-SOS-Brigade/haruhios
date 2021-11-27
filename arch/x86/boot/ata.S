
.section .boot, "ax"
.code32

.global ata_pio28_read

ata_pio28_read:
	pusha
	
	pushl %eax
	pushl %eax

	movw $0x1F2, %dx
	movb %cl, %al
	outb %al, %dx

	popl %eax

	incw %dx
	outb %al, %dx

	incw %dx
	shrw $8, %ax
	outb %al, %dx

	incw %dx
	shrw $8, %ax
	outb %al, %dx

	popl %eax

	incw %dx
	shrl $24, %eax
	orb $0xE0, %al
	outb %al, %dx

	incw %dx
	movb $0x20, %al
	outb %al, %dx

	xorw %ax, %ax
.Lpio28_read_poll0:
	inb %dx, %al
	btw $7, %ax
	jc .Lpio28_read_poll0
	btw $3, %ax
	jnc .Lpio28_read_poll0
	jmp .Lpio28_read_ready

.Lpio28_read_poll1:
	inb %dx, %al
	btw $7, %ax
	jc .Lpio28_read_poll1

.Lpio28_read_ready:
	pushl %ecx

	movl $0x100, %ecx
	xorw $7, %dx
	cld
	rep insw

	orw $7, %dx
	inb %dx, %al
	inb %dx, %al
	inb %dx, %al
	inb %dx, %al

	popl %ecx

	loop .Lpio28_read_poll1
	clc
	jmp .Lpio28_read_done

.Lpio28_read_done:
	popa
	ret

