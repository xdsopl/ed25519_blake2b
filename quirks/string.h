/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include <stddef.h>

void *memset(void *buf, int val, size_t len);
void *memcpy(void *dst, const void *src, size_t len);
void *memmove(void *dst, const void *src, size_t len);

