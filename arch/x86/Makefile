
SRCS := $(wildcard boot/*.s)

arch:
	$(AS) $(SRCS) -o $@.o

OBJS += arch.o
link: $(OBJS)
	$(LD) -Tlinker.ld -static $^

