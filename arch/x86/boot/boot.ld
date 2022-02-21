ENTRY (_loader)
OUTPUT_FORMAT (binary)
OUTPUT (BOOT.SYS)

SECTIONS {

	__kernel_start_phys = 0x100000;
	__kernel_start = 0xC0000000;
	kernel_entry = __kernel_start;

	.boot 0x500 : AT(0) {
		* (.boot.entry)
		* (.boot)
	}

	/DISCARD/ : {
		* (.mbr)
		* (.vbr)
	}
}
