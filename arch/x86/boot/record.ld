ENTRY (_start)
OUTPUT_FORMAT (binary)
OUTPUT(boot.img)

SECTIONS {

	.mbr 0x6000 : AT(0) {
		__mbr_start = ABSOLUTE(.);
		* (.mbr)
		ASSERT ((ABSOLUTE(.) <= (__mbr_start + 0x200)),
					 "MBR is larger than 512B");
		__mbr_end = ABSOLUTE(.);
	}

	.vbr 0x7C00 : AT(0x200) {
		__vbr_start = ABSOLUTE(.);
		* (.vbr)
		ASSERT ((ABSOLUTE(.) <= (__vbr_start + 0x200)),
					"VBR is larger than 512B");
		__vbr_end = ABSOLUTE(.);
		SHORT(0x0000);
	}

	/DISCARD/ : {
		* (.boot)
	}
}
