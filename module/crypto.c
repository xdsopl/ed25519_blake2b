/*
WebAssembly crypto module for digital signing based on Ed25519 and BLAKE2B

Copyright 2024 Ahmet Inan <xdsopl@gmail.com>
*/

__attribute__((visibility("default")))
unsigned char public_key[32];
__attribute__((visibility("default")))
unsigned char private_key[64];
__attribute__((visibility("default")))
unsigned char message[1024-64];
__attribute__((visibility("default")))
unsigned char signature[1024];

int crypto_sign(unsigned char *sm, unsigned long long *smlen,
	const unsigned char *m, unsigned long long mlen,
	const unsigned char *sk);

int crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
	const unsigned char *sm, unsigned long long smlen,
	const unsigned char *pk);

__attribute__((visibility("default")))
int sign_message(int mlen)
{
	unsigned long long smlen;
	return crypto_sign(signature, &smlen, message, mlen, private_key);
}

__attribute__((visibility("default")))
int create_keypair()
{
	return crypto_sign_keypair(public_key, private_key);
}

__attribute__((visibility("default")))
int open_signature(int smlen)
{
	unsigned long long mlen;
	return crypto_sign_open(message, &mlen, signature, smlen, public_key);
}
