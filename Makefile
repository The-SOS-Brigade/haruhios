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

OBJS := arch.o $(SRCS:=.o)

PHONY := __all
__all: arch.o

export AS GCC CFLAGS LD

PHONY += arch
arch:
	echo $(ARCH)
	$(MAKE) -C arch/$(SRCARCH)

arch.o:
	@echo >&2 "***"; \
	 echo >&2 "*** Make arch before building haruhios"; \
	 echo >&2 "***"
	 

PHONY += clean
clean:
	find . -name '*.o' -delete

.PHONY: $(PHONY)

