/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include "string.h"

unsigned char random_bytes[32];

static void randombytes(unsigned char *buf, unsigned long long num)
{
	memcpy(buf, random_bytes, num);
	memset(random_bytes, 0, num);
}
