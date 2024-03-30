/*
Quirks

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

__attribute__((visibility("default")))
int crypto_sign(unsigned char *sm, unsigned long long *smlen,
	const unsigned char *m, unsigned long long mlen,
	const unsigned char *sk);

__attribute__((visibility("default")))
int crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

__attribute__((visibility("default")))
int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
	const unsigned char *sm,unsigned long long smlen,
	const unsigned char *pk);
