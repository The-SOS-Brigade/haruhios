ENTRY (_start)
OUTPUT_FORMAT (binary)
OUTPUT (haruhios.bin)

SECTIONS {
	.boot 0x7C00 : AT(0) {
		__mbr_start = .;
		boot/mbr.o (.boot)
		__mbr_end = .;
		ASSERT ((__mbr_end <= (__mbr_start + 0x200)), 
					"MBR is larger than 512B");
		* (.boot)
	}

	. = 0x100000;

	.text : AT(0x800) {
		* (.text)
	}
	
	.data : AT(LOADADDR(.text) + SIZEOF(.text)) {
		* (.data)
	}

	.rodata : AT(LOADADDR(.data) + SIZEOF(.data)) {
		* (.rodata)
	}

	.bss : AT(LOADADDR(.data) + SIZEOF(.data)) {
		* (.bss)
	}
}

