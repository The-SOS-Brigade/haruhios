#include <haruhi/memory/kheap.h>
#include <haruhi/console.h>
#include <haruhi/string.h>
#include <haruhi/types.h>

#define PRINTK_FMT_PREFIX "%"

void printk(char *str, ...)
{
	va_list args;
	va_start(args, str);
	size_t len = strlen(str);
	size_t fmt_count = strcnt(str, PRINTK_FMT_PREFIX);
	void *buf = kzalloc(len+1);

	if (!buf) {
		asprintk("printk(): kheap alloc req failed\n");
		return;
	}

	str = memcpy(buf, str, len+1);
	char *ptr = str;
	char itoa_buffer[20];

	for (size_t i = 0; i < fmt_count; ++i) {
		ptr = strstr(ptr, PRINTK_FMT_PREFIX);
		switch (ptr[1]) {
		case '%':
			strrpl(str, PRINTK_FMT_PREFIX"%", "%");
			--fmt_count;
			break;
		case 'c':
			va_arg(args, int);
			break;
		case 'd':
		{
			signed int tmp = va_arg(args, signed int);
			strrpl(str, PRINTK_FMT_PREFIX"d", itoa(tmp, itoa_buffer, 10));
			break;
		}
		case 'u':
			va_arg(args, unsigned int);
			break;
		case 'p':
			va_arg(args, void *);
			break;
		case 's':
		{
			char *tmp = va_arg(args, char *);
			strrpl(str, PRINTK_FMT_PREFIX"s", tmp);
			break;
		}
		case 'x':
			va_arg(args, int);
			break;
		default:
			break;
		}
	}

	va_end(args);
	asprintk(str);
	kfree(buf);
}

