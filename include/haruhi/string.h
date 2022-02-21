#ifndef _HARUHI_STRING_H
#define _HARUHI_STRING_H

#include <haruhi/types.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
int strcmp(const char *str0, const char *str1);
size_t strlen(const char *str);
char *strstr(const char *str, const char *substr);
size_t strcnt(const char *str, const char *substr);
char *strrpl(char *str, const char *substr, const char *newsubstr);
int strncmp(const char *str0, const char *str1, size_t n);
char *itoa(int n, char *str, char radix);

#endif

