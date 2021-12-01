.text
.code32

.global int_default

int_default:
	cli
	pushal

	/* nothing */

	popal
	sti
	iret

