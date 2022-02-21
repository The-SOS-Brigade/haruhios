.section .vbr
.code16

bpb_skip:
	jmp vbr_boot
	nop
bpb_oemid:			.ascii "HARUHIOS" /* 8 bytes */
bpb_bps:			.word 0
bpb_spc:			.byte 0
bpb_reserved_sectors:		.word 0
bpb_fat_count:			.byte 0
bpb_root_entries:		.word 0
.word 0
bpb_media_descriptor_type:	.byte 0
.word 0
bpb_spt:			.word 0
bpb_hpc:			.word 0
bpb_hidden_sectors:		.word 0, 0
bpb_total_sectors:		.word 0, 0

ebpb_spf:			.word 0, 0
ebpb_flags:			.word 0
ebpb_fat_version:		.word 0
ebpb_root_cluster:		.word 0, 0
ebpb_fsinfo_sector:		.word 0
ebpb_backup_sector:		.word 0
ebpb_reserved0:			.word 0, 0
ebpb_reserved1:			.word 0, 0
ebpb_reserved2:			.word 0, 0
ebpb_drive_number:		.byte 0
ebpb_nt_flags:			.byte 0
ebpb_signature:			.byte 0
ebpb_volumeid:			.word 0, 0
ebpb_volume_label:		.ascii "haruhios   " /* 11 bytes */
ebpb_systemid_string:		.ascii "FAT32   " /* 8 bytes */

__fat_start = 0x7E00
__loader_start = 0x500

vbr_boot:
	cli
	ljmp $0, $1f
1:
	xorw %ax, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %ss
	movw $0x7C00, %bp
	movw %bp, %sp

	sti

	movb %dl, ebpb_drive_number
fix_drive_params:
	movb $8, %ah
	xorw %di, %di
	int $0x13
	jc halt_system
	pushw %cx
	xorb %ch, %ch
	andb $0b00111111, %cl
	movw %cx, bpb_spt
	popw %cx
	shrb $6, %cl
	xchgb %ch, %cl
	movb %dh, %dl
	xorb %dh, %dh
	incb %dl
	movw %dx, bpb_hpc

	xorl %eax, %eax
	movb bpb_fat_count, %al
	mull ebpb_spf
	addw bpb_reserved_sectors, %ax
	addl bpb_hidden_sectors, %eax
	movl %eax, ebpb_reserved0

load_rootdir:
	movl ebpb_root_cluster, %eax
	xorw %bx, %bx
	movw %bx, %es
	movw $0x9000, %bx
	call read_cluster

	/* Search for BOOT.SYS */
	movw $8, %cx
	movw %bx, %si
search_loader:
	cld
	pushw %cx
	movw $loader_filename, %di
	pushw %si
	movw $0xB, %cx
	repe cmpsb
	popw %si
	je loader_found
	addw $32, %si
	popw %cx
	loop search_loader
loader_not_found:
	movw $loader_not_found_msg, %si
	call bios_print
	jmp halt_system
loader_found:
	addw $2, %sp
	movl 20(%si), %eax
	shll $16, %eax
	movw 26(%si), %ax
	xorw %bx, %bx
	movw %bx, %es
	movw $__loader_start, %bx
	call read_file
	ljmp $0, $__loader_start

	jmp halt_system
read_cluster:
	pusha
	xorw %cx, %cx
	subw $2, %ax
	movb bpb_spc, %cl
	mulw %cx
	addl ebpb_reserved0, %eax
	call read_sectors_lba
	popa
	ret

read_file:
	pusha
	pushw %ax
	xorw %cx, %cx
	movw bpb_bps, %ax
	movb bpb_spc, %cl
	mulw %cx
	movw %ax, %cx
	popw %ax
1:
	call read_cluster
	addw %cx, %bx

	pushw %bx
	pushw %ax
	movw $__fat_start, %bx
	shll $2, %eax
	divw bpb_bps
	addw bpb_reserved_sectors, %ax
	addw bpb_hidden_sectors, %ax
	pushw %cx
	movb bpb_spc, %cl
	call read_sectors_lba
	popw %cx
	popw %ax

	addw %dx, %bx
	movl (%bx), %eax
	andl $0x0FFFFFFF, %eax
	cmpl $0x0FFFFFF8, %eax
	popw %bx
	jb 1b
	popa
	ret

read_sectors_lba:
	pusha

	pushw %cx
	xorw %dx, %dx
	divw bpb_spt
	incb %dl
	movb %dl, %cl /* sector */
	xorw %dx, %dx
	divw bpb_hpc
	movb %al, %ch /* cylinder */
	shlb $6, %ah
	orb %ah, %cl
	movb %dl, %dh /* head */

	popw %ax
	movb ebpb_drive_number, %dl /* drive */
	movb $2, %ah
	int $0x13
	jc read_error

	popa
	ret

read_error:
	movw $load_error_msg, %si
	call bios_print
	jmp halt_system

halt_system:
	hlt
	jmp .

load_error_msg: .asciz "disk read error\n\r"
loader_not_found_msg: .asciz "BOOT.SYS not found\n\r"
loader_filename: .ascii "BOOT    SYS"

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

.org 0x1FE
.word 0xAA55
