#include <haruhi/string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *ptr = (char *)dest;

	for (i = 0; i < n; ++i)
		ptr[i] = ((char *)src)[i];

	return ptr;
}

void *memset(void *dest, int c, size_t n)
{
	size_t i;
	char *ptr = (char *)dest;

	for (i = 0; i < n; ++i)
		ptr[n] = (char)c;

	return ptr;
}


int strcmp(const char *str0, const char *str1)
{
	size_t i;
	size_t len = strlen(str0);
	int tmp = 0;

	for (i = 0; i < len; ++i) {
		tmp = str0[i] - str1[i];
		if (tmp != 0)
			break;
	}

	return tmp;
}

size_t strlen(const char *str)
{
	size_t len = 0;
	for (; str[len] != 0; ++len);
	return len;
}

