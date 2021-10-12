ENTRY (_start)
OUTPUT_FORMAT (binary)
OUTPUT(haruhios.bin)

SECTIONS {
	. = 0x7C00;
	__mbr_start = .;

	.mbr_text : {
		arch.o (.mbr_text)
	}

	__mbr_end = .;
	
	.text : {
		* (.text)
	}
	
	.data : {
		* (.data)
	}

	.rodata : {
		* (.rodata)
	}

	.bss : {
		* (.bss)
	}


}

