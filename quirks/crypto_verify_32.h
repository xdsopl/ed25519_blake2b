/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

static int crypto_verify_32(const unsigned char *x, const unsigned char *y)
{
	int len = 32, dif = 0;
	while (len--)
		dif |= *x++ ^ *y++;
	return dif;
}
