BOOT_SRCS_S	:= $(shell find boot -type f -name '*.S')
BOOT_SRCS_C	:= $(shell find boot -type f -name '*c')
KERNEL_SRCS_S	:= $(shell find kernel -type f -name '*.S')
KERNEL_SRCS_C	:= $(shell find kernel -type f -name '*.c')

BOOT_OBJS	+= $(BOOT_SRCS_S:%.S=%.o) $(BOOT_SRCS_C:%.c=%.o)
KERNEL_OBJS	+= $(KERNEL_SRCS_S:%.S=%.o) $(KERNEL_SRCS_C:%.c=%.o)

LDFLAGS	:= -static
CFLAGS	+= -masm=att
INCLUDE	+= -Iinclude -include "asm/config.h"

DD	:= dd
MKDIR	:= mkdir
MOUNT	:= mount
UMOUNT	:= umount
LOSETUP	:= losetup
FDISK	:= fdisk
MKFS	:= mkfs.vfat
CP	:= cp
RM	:= rm
TARGET	:= boot.img BOOT.SYS KERNEL.SYS

__all: $(TARGET)

boot.img: boot/mbr.o boot/vbr.o
	$(LD) -Tboot/record.ld $^ $(LDFLAGS) -o$(BUILDDIR)/$@
	$(DD) if=$(BUILDDIR)/$@ of=$(BUILDDIR)/mbr.img bs=512 count=1
	$(DD) if=$(BUILDDIR)/$@ of=$(BUILDDIR)/vbr.img bs=512 count=1 skip=1

BOOT.SYS: $(BOOT_OBJS)
	$(LD) -Tboot/boot.ld $^ $(LDFLAGS) -o$(BUILDDIR)/$@

KERNEL.SYS: $(KERNEL_OBJS)
	$(LD) -Tkernel/kernel.ld $^ $(LDFLAGS) -o$(BUILDDIR)/$@

%.o: %.S
	$(GCC) -E $< -o $(patsubst %.S, %.i, $<) $(CFLAGS) $(INCLUDE)
	$(AS) $(patsubst %.S, %.i, $<) -o $@ $(ASFLAGS)

%.o: %.c
	$(GCC) $< -c -o $@ $(CFLAGS) $(INCLUDE)

LOOPDEV := /dev/loop42

PHONY := install_loop
install_loop:
	$(MKDIR) -p build
	-$(UMOUNT) -d $(LOOPDEV)
	$(DD) if=/dev/zero of=$(BUILDDIR)/hd.img bs=516096c count=1000
	$(DD) if=$(BUILDDIR)/mbr.img of=$(BUILDDIR)/hd.img bs=512 count=1 conv=notrunc
	printf "n\np\n1\n2048\n\nt\nb\na\nw\n" | $(FDISK) -C1000 -S63 -H16 $(BUILDDIR)/hd.img
	$(LOSETUP) -o1048576 $(LOOPDEV) $(BUILDDIR)/hd.img
	$(MKFS) -F32 -n "HARUHIOS" -s1 -h2048 -r512 $(LOOPDEV)
	$(DD) if=$(BUILDDIR)/vbr.img of=$(LOOPDEV) bs=1 count=3 seek=0 conv=notrunc
	$(DD) if=$(BUILDDIR)/vbr.img of=$(LOOPDEV) bs=1 count=422 seek=90 skip=90 conv=notrunc
	$(MKDIR) -p $(abs_srctree)/mnt
	$(MOUNT) -tvfat $(LOOPDEV) $(abs_srctree)/mnt
	$(CP) $(BUILDDIR)/KERNEL.SYS $(abs_srctree)/mnt
	$(CP) $(BUILDDIR)/BOOT.SYS $(abs_srctree)/mnt
	-sync

PHONY += clean
clean:
	$(RM) -rf build

.PHONY: $(PHONY)
