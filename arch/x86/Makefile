
SRCS_S	:= $(wildcard boot/*.s)
SRCS_C	:= $(wildcard boot/*.c) $(wildcard kernel/*.c)
OBJS	+= $(SRCS_S:%.s=%.o) $(SRCS_C:%.c=%.o)

ASFLAGS	:=
LDFLAGS	:= -static
CFLAGS	+= -masm=att
INCLUDE	+= -Iinclude

__all: $(OBJS)
	$(LD) -Tlinker.ld $^ $(LDFLAGS)

%.o: %.s
	$(AS) $< -o $@ $(ASFLAGS)

%.o: %.c
	$(GCC) $< -c -o $@ $(CFLAGS) $(INCLUDE)

