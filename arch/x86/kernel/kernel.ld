ENTRY (kernel_entry)
OUTPUT_FORMAT (binary)
OUTPUT (KERNEL.SYS)

SECTIONS {
	. = 0xC0000000;

	__kernel_start_phys = 0x400000;
	__kernel_start = .;

	.text :  {
		* (.text.entry)
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

	__kernel_end = .;
	__kernel_end_phys = __kernel_start_phys +
				(__kernel_end - __kernel_start);

	. = 0xC1000000;
	__pgt_start_phys = 0x1000000;
	__pgt_start = .;

	. = __pgt_start + 0x401000;

	__pgt_end_phys = __pgt_start_phys + 0x401000;
	__pgt_end = .;
}
