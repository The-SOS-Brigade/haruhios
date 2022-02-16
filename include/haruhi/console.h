#ifndef _HARUHI_CONSOLE_H
#define _HARUHI_CONSOLE_H

extern void console_init(void);
extern void console_clear(void);
extern void asprintk(const char *str);
void printk(char *str, ...);

#endif

