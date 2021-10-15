
SRCS := $(wildcard boot/*.s)
OBJS += $(SRCS:%.s=%.o)
ASFLAGS :=
LDFLAGS := -static

__all: $(OBJS)
	$(LD) -Tlinker.ld $^ $(LDFLAGS)

%.o: %.s
	$(AS) $< -o $@ $(ASFLAGS)

%.o: %.c
	$(GCC) $< -c -o $@ $(CFLAGS)

