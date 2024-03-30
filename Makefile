
# WebAssembly crypto module for digital signing based on Ed25519 and BLAKE2B
# Copyright 2024 Ahmet Inan <xdsopl@gmail.com>

CC = clang
CFLAGS = -ffreestanding -fvisibility=hidden --target=wasm32
LDFLAGS = -nostdlib -Wl,--export-dynamic,--no-entry

CFLAGS += -std=c89 -W -Wall -O2 -Iquirks
BLAKE2 = -Iblake2_ref
CRYPTO = -Ied25519_ref -DCRYPTO_NAMESPACE\(name\)=crypto_\#\#name

assets/crypto.wasm: temp/string.o temp/blake2b-ref.o temp/fe25519.o temp/sc25519.o temp/ge25519.o temp/sign.o temp/keypair.o temp/open.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

temp/blake2b-ref.o: blake2_ref/blake2b-ref.c
	$(CC) $(CFLAGS) $(BLAKE2) -c -o $@ $<

temp/fe25519.o: ed25519_ref/fe25519.c
	$(CC) $(CFLAGS) $(CRYPTO) -c -o $@ $<

temp/sc25519.o: ed25519_ref/sc25519.c
	$(CC) $(CFLAGS) $(CRYPTO) -c -o $@ $<

temp/ge25519.o: ed25519_ref/ge25519.c
	$(CC) $(CFLAGS) $(CRYPTO) -c -o $@ $<

temp/sign.o: ed25519_ref/sign.c
	$(CC) $(CFLAGS) $(BLAKE2) $(CRYPTO) -c -o $@ $<

temp/keypair.o: ed25519_ref/keypair.c
	$(CC) $(CFLAGS) $(BLAKE2) $(CRYPTO) -c -o $@ $<

temp/open.o: ed25519_ref/open.c
	$(CC) $(CFLAGS) $(BLAKE2) $(CRYPTO) -c -o $@ $<

temp/string.o: quirks/string.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f temp/*.o

