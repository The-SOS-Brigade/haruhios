#include <haruhi/memory/kheap.h>
#include <haruhi/string.h>
#include <haruhi/types.h>
#include <haruhi/math.h>

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
		ptr[i] = (char)c;

	return ptr;
}

int strcmp(char *str0, const char *str1)
{
	return strncmp(str0, str1, strlen(str0));
}

char *strcpy(char *dest, const char *src)
{
	size_t len = strlen(src);

	for (size_t i = 0; i < len; ++i) {
		dest[i] = src[i];
	}

	dest[len] = '\0';

	return dest;
}

size_t strlen(const char *str)
{
	size_t len = 0;
	for (; str[len] != 0; ++len);
	return len;
}

char *strstr(const char *str, const char *substr)
{
	size_t substr_len = strlen(substr);

	while (*str) {
		if (!strncmp(str, substr, substr_len))
			return (char *)str;
		++str;
	}

	return NULL;
}

size_t strcnt(const char *str, const char *substr)
{
	size_t count = 0;

	while ((str = strstr(str, substr)) != NULL) {
		++str;
		++count;
	}

	return count;
}

char *strrpl(char *str, const char *substr, const char *newsubstr)
{
	size_t newsublen = strlen(newsubstr);
	size_t sublen = strlen(substr);
	char *offstr = strstr(str, substr);

	if (!offstr)
		return str;

	size_t offlen = strlen(offstr) - sublen + 1;
	char *ptr = kzalloc(offlen);

	if (!ptr)
		return str;

	memcpy(ptr, offstr+sublen, offlen);
	memcpy(offstr+newsublen, ptr, offlen);
	memcpy(offstr, newsubstr, newsublen);

	kfree(ptr);

	return str;
}

int strncmp(const char *str0, const char *str1, size_t n)
{
	int tmp = 0;
	for (size_t i = 0; i < n; ++i) {
		tmp = str0[i] - str1[i];
		if (tmp != 0)
			break;
	}
	return tmp;
}

char *itoa(int value, char *str, char radix)
{
	if (radix < 2 || radix > 36) {
		*str = '\0';
		return str;
	}

	char *ptr = str, *ptr1 = str, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= radix;
		*ptr++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[abs(tmp_value - value * radix)];

	} while (value);

	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';

	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}

	return str;
}

char *utoa(unsigned int value, char *str, char radix)
{
	if (radix < 2 || radix > 36) {
		*str = '\0';
		return str;
	}

	char *ptr = str, *ptr1 = str, tmp_char;
	int tmp_value;

	do {
		tmp_value = value % radix;
		value /= radix;
		*ptr++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[abs(tmp_value)];

	} while (value);

	*ptr-- = '\0';

	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}

	return str;
}

