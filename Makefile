ARCH ?= i686
SRCARCH := ARCH

ifeq ($(ARCH),x86_64)
	SRCARCH := x86
	AS	:= $(ARCH)-elf-as
	GCC	:= $(ARCH)-elf-gcc
	LD	:= $(ARCH)-elf-ld
else ifeq ($(ARCH),i686)
	SRCARCH := x86
	AS	:= $(ARCH)-elf-as
	GCC	:= $(ARCH)-elf-gcc
	LD	:= $(ARCH)-elf-ld
else
	ERR	:= $(error Invalid arch)
endif

CFLAGS := -g -ffreestanding -falign-jumps -falign-functions -falign-labels \
			-falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions \
			-Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp \
			-Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0	\
			-std=gnu11

this_makefile := $(lastword $(MAKEFILE_LIST))
abs_srctree := $(realpath $(dir $(this_makefile)))

SRCS		:= $(shell find $(abs_srctree)/kernel -type f -name '*.c')
KERNEL_OBJS	:= $(SRCS:%.c=%.o)
INCLUDE		:= -I$(abs_srctree)/include
BUILDDIR	:= build

MKDIR		:= mkdir
FIND		:= find

PHONY := __all
__all: build

export AS ARCH GCC LD KERNEL_OBJS CFLAGS INCLUDE BUILDDIR

PHONY += build
build:
	$(MKDIR) -p arch/$(SRCARCH)/$(BUILDDIR)
	$(MAKE) -C arch/$(SRCARCH)

export abs_srctree

PHONY += install_loop
install_loop:
ifneq ($(shell id -u), 0)
	@echo "Run with root privileges"
	@exit 1
endif
	$(MAKE) -C arch/$(SRCARCH) $@

PHONY += clean
clean:
	$(MAKE) -C arch/$(SRCARCH) $@
	$(FIND) . -name '*.o' -delete
	$(FIND) . -name '*.i' -delete

.PHONY: $(PHONY)

