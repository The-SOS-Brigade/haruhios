.text
.code32

.global int_default

.macro BUILDINT name:req, handler:req
.extern \handler
.global \name
\name\():
	cli
	pushal
	call \handler
	popal
	sti
	iret
.endm

int_default:
	cli
	pushal

	/* nothing */

	popal
	sti
	iret


BUILDINT irq_task0, timer_irq_handler
BUILDINT irq_task1, keyboard_irq_handler
BUILDINT irq_task3, comm2_irq_handler
BUILDINT irq_task4, comm1_irq_handler
BUILDINT irq_task6, floppy_irq_handler
BUILDINT irq_task7, lpt1_irq_handler
BUILDINT irq_task8, clock_irq_handler
BUILDINT irq_task9, cga_irq_handler
BUILDINT irq_task12, ps2_irq_handler
BUILDINT irq_task13, fpu_irq_handler

BUILDINT int_syscall, syscall_int_handler

