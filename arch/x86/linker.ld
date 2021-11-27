ENTRY (_start)
OUTPUT_FORMAT (binary)
OUTPUT (haruhios.bin)

SECTIONS {
	.boot 0x7C00 : AT(0) {
		__mbr_start = .;
		* (__mbr)
		__mbr_end = .;
		ASSERT ((__mbr_end <= (__mbr_start + 0x200)), 
					"MBR is larger than 512B");
		* (.boot)
	}

	. = 0xC0000000;

	__kernel_start_phys = 0x100000;
	__kernel_start = .;

	.text : AT(0x800) {
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

	__kernel_end_phys = __kernel_start_phys +
					(__kernel_end - __kernel_start);
	__kernel_end = .;

	. = 0xC1000000;
	__pgt_start_phys = 0x1000000;
	__pgt_start = .;

	. = __pgt_start + 0x401000;

	__pgt_end_phys = __pgt_start_phys + 0x401000;
	__pgt_end = .;

}

