
.section .boot

.global gdt_desc
.global __gdt_start, __gdt_end

.global code_seg, data_seg

__gdt_start:
.Lnull_gdt:
	.quad 0
.Lcode_gdt:
	.word 0xFFFF
	.word 0x0000
	.byte 0b00000000
	.byte 0b10011110
	.byte 0b11001111
	.byte 0b00000000
.Ldata_gdt:
	.word 0xFFFF
	.word 0x0000
	.byte 0b00000000
	.byte 0b10010010
	.byte 0b11001111
	.byte 0b00000000
__gdt_end:

gdt_desc:
	.word __gdt_end - __gdt_start - 1
	.word __gdt_start
	.word 0

code_seg = .Lcode_gdt - __gdt_start
data_seg = .Ldata_gdt - __gdt_start

