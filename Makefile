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
			-Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

this_makefile := $(lastword $(MAKEFILE_LIST))
abs_srctree := $(realpath $(dir $(this_makefile)))

SRCS := $(wildcard $(abs_srctree)/kernel/*.c)
OBJS := $(SRCS:%.c=%.o)

PHONY := __all
__all: build

export AS GCC LD OBJS CFLAGS

PHONY += build
build:
	$(MAKE) -C arch/$(SRCARCH)

PHONY += clean
clean:
	find . -name '*.o' -delete

.PHONY: $(PHONY)

