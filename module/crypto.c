/*
WebAssembly crypto module for digital signing based on Ed25519 and BLAKE2B

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

#include <string.h>
#include "blake2.h"
#include "ge25519.h"

__attribute__((visibility("default")))
unsigned char digest[64];
__attribute__((visibility("default")))
unsigned char private_key[32];
__attribute__((visibility("default")))
unsigned char fingerprint[32];
__attribute__((visibility("default")))
unsigned char signature[1<<24];
__attribute__((visibility("default")))
unsigned char *message = signature + 64;

static int hash(unsigned char *out, const unsigned char *in, int len)
{
	return blake2b(out, BLAKE2B_OUTBYTES, in, len, NULL, 0);
}

static int verify(const unsigned char *x, const unsigned char *y)
{
	int len = 32, dif = 0;
	while (len--)
		dif |= *x++ ^ *y++;
	return !!dif;
}

__attribute__((visibility("default")))
int digest_message(int mlen)
{
	return hash(digest, signature+64, mlen);
}

__attribute__((visibility("default")))
int create_signature(int mlen)
{
	unsigned char az[64];
	unsigned char nonce[64];
	unsigned char hram[64];
	sc25519 sck, scs, scsk;
	ge25519 ger;
	hash(az, private_key, 32);
	az[0] &= 248;
	az[31] &= 127;
	az[31] |= 64;
	memcpy(signature+32, az+32, 32);
	hash(nonce, signature+32, mlen+32);
	sc25519_from64bytes(&sck, nonce);
	ge25519_scalarmult_base(&ger, &sck);
	ge25519_pack(signature, &ger);
	memcpy(signature+32, fingerprint, 32);
	hash(hram, signature, mlen+64);
	sc25519_from64bytes(&scs, hram);
	sc25519_from32bytes(&scsk, az);
	sc25519_mul(&scs, &scs, &scsk);
	sc25519_add(&scs, &scs, &sck);
	sc25519_to32bytes(signature+32, &scs);
	return 0;
}

__attribute__((visibility("default")))
int create_fingerprint()
{
	unsigned char az[64];
	sc25519 scsk;
	ge25519 gepk;
	hash(az, private_key, 32);
	az[0] &= 248;
	az[31] &= 127;
	az[31] |= 64;
	sc25519_from32bytes(&scsk, az);
	ge25519_scalarmult_base(&gepk, &scsk);
	ge25519_pack(fingerprint, &gepk);
	return 0;
}

__attribute__((visibility("default")))
int verify_signature(int mlen)
{
	unsigned char hram[64], rcheck[32], scopy[32];
	ge25519 get1, get2;
	sc25519 schram, scs;
	if (signature[63] & 224)
		return 1;
	if (ge25519_unpackneg_vartime(&get1, fingerprint))
		return 1;
	sc25519_from32bytes(&scs, signature+32);
	memcpy(scopy, signature+32, 32);
	memcpy(signature+32, fingerprint, 32);
	hash(hram, signature, mlen+64);
	sc25519_from64bytes(&schram, hram);
	ge25519_double_scalarmult_vartime(&get2, &get1, &schram, &ge25519_base, &scs);
	ge25519_pack(rcheck, &get2);
	memcpy(signature+32, scopy, 32);
	return verify(signature, rcheck);
}
