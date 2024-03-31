/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#include "string.h"

void *memset(void *buf, int val, size_t len)
{
	char *c = buf;
	while (len--)
		*c++ = val;
	return buf;
}

void *memcpy(void *dst, const void *src, size_t len)
{
	char *d = dst;
	const char *s = src;
	while (len--)
		*d++ = *s++;
	return dst;
}

void *memmove(void *dst, const void *src, size_t len)
{
	char *d = dst;
	const char *s = src;
	if (dst > src && dst < src + len) {
		d += len - 1;
		s += len - 1;
		while (len--)
			*d-- = *s--;
	} else {
		while (len--)
			*d++ = *s++;
	}
	return dst;
}
