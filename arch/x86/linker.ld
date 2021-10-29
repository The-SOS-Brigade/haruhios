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

	.text 1M : AT(0x800) {
		* (.text)
	}

	.data :  {
		* (.data)
	}

	.rodata : {
		* (.rodata)
	}

	.bss : {
		* (COMMON)
		* (.bss)
	}
}

