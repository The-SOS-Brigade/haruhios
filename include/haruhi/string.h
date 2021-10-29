#ifndef _HARUHI_STRING_H
#define _HARUHI_STRING_H

#include <haruhi/types.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
int strcmp(const char *str0, const char *str1);
size_t strlen(const char *str);

#endif

