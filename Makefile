ARCH		?= x86
TOOLCHAIN	?= i686-elf-
SRCARCH		:= $(ARCH)

ifeq ($(ARCH),x86_64)
	SRCARCH := x86
	AS	:= $(TOOLCHAIN)as
	GCC	:= $(TOOLCHAIN)gcc
	LD	:= $(TOOCHAIN)ld
else ifeq ($(ARCH),x86)
	AS	:= $(TOOLCHAIN)as
	GCC	:= $(TOOLCHAIN)gcc
	LD	:= $(TOOLCHAIN)ld
else
	ERR	:= $(error Invalid arch)
endif

CFLAGS := -g -ffreestanding -falign-jumps -falign-functions -falign-labels \
			-falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions \
			-Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp \
			-Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0	\
			-std=gnu11 -fstack-protector-strong

this_makefile := $(lastword $(MAKEFILE_LIST))
abs_srctree := $(realpath $(dir $(this_makefile)))

SRCS		:= $(shell find $(abs_srctree)/kernel -type f -name '*.c')
KERNEL_OBJS	:= $(SRCS:%.c=%.o)
INCLUDE		:= -I$(abs_srctree)/include -include "haruhi/config.h"
BUILDDIR	:= build

MKDIR		:= mkdir
FIND		:= find
DOXYGEN		?= doxygen

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

PHONY += htmldocs
htmldocs:
	$(DOXYGEN) docs/Doxyfile
	$(MAKE) -C docs html

PHONY += clean
clean:
	$(MAKE) -C arch/$(SRCARCH) $@
	$(RM) -rf docs/_build
	$(FIND) . -name '*.o' -delete
	$(FIND) . -name '*.i' -delete

.PHONY: $(PHONY)

