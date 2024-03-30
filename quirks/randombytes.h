/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

static void randombytes(unsigned char *buf, unsigned long long num)
{
	while (num--)
		*buf++ = num;
}
