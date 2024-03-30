/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include "blake2.h"

static int crypto_hash_sha512(unsigned char *out, const unsigned char *in, unsigned long long inlen)
{
	return blake2b(out, BLAKE2B_OUTBYTES, in, inlen, NULL, 0);
}
