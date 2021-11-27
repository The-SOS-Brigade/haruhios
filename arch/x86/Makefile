SRCS_S	:= $(shell find . -type f -name '*.S')
SRCS_C	:= $(boot/*.c) $(shell find kernel -type f -name '*.c')

OBJS	+= $(SRCS_S:%.S=%.o) $(SRCS_C:%.c=%.o)

LDFLAGS	:= -static
CFLAGS	+= -masm=att
INCLUDE	+= -Iinclude

__all: $(OBJS)
	$(LD) -Tlinker.ld $^ $(LDFLAGS)

%.o: %.S
	$(GCC) -E $< -o $(patsubst %.S, %.i, $<) $(CFLAGS) $(INCLUDE)
	$(AS) $(patsubst %.S, %.i, $<) -o $@ $(ASFLAGS)

%.o: %.c
	$(GCC) $< -c -o $@ $(CFLAGS) $(INCLUDE)

