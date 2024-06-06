#ifndef KEM_HR
#define KEM_HR

#include <stdint.h>
#include <string.h>
#include <lib25519.h>

#include "params.h"
#include "mlkem/symmetric.h"
#include "randombytes.h"
#include "mlkem/kem.h"


#define CRYPTO_SECRETKEYBYTES  xwing_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  xwing_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES xwing_CIPHERTEXTBYTES
#define CRYPTO_BYTES           xwing_SSBYTES
#define CRYPTO_ALGNAME         "xwing"

int crypto_xkem_keypair_derand(unsigned char *pk, unsigned char *sk, const unsigned char *coins);

int crypto_xkem_keypair(unsigned char *pk, unsigned char *sk);

int crypto_xkem_enc_derand(unsigned char *ct, unsigned char *ss, const unsigned char *pk, const unsigned char *coins);

int crypto_xkem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

int crypto_xkem_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk);

#endif
