#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "mlkem_params.h"

#ifdef MLKEM_90S

#include "aes256ctr.h"
#include "sha2.h"

#if (MLKEM_SSBYTES != 32)
#error "90s variant of mlkem can only generate keys of length 256 bits"
#endif

#define hash_h(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) sha512(OUT, IN, INBYTES)
#define xof_absorb(STATE, IN, X, Y) aes256xof_absorb(STATE, IN, X, Y)
#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) aes256xof_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define prf(OUT, OUTBYTES, KEY, NONCE) aes256_prf(OUT, OUTBYTES, KEY, NONCE)
#define kdf(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)

#define XOF_BLOCKBYTES 64

typedef aes256xof_ctx xof_state;

#else

#include "fips202.h"

typedef struct {
  uint64_t s[25];
} keccak_state;

void mlkem_shake128_absorb(keccak_state *s, const unsigned char *input, unsigned char x, unsigned char y);
void mlkem_shake128_squeezeblocks(unsigned char *output, unsigned long long nblocks, keccak_state *s);
void shake256_prf(unsigned char *output, unsigned long long outlen, const unsigned char *key, const unsigned char nonce);
void shake256_rkprf(unsigned char *out, const unsigned char *key, const unsigned char *input);

#define hash_h(OUT, IN, INBYTES) sha3_256(OUT, IN, INBYTES)
#define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)
#define xof_absorb(STATE, IN, X, Y) mlkem_shake128_absorb(STATE, IN, X, Y)
#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) mlkem_shake128_squeezeblocks(OUT, OUTBLOCKS, STATE)
#define prf(OUT, OUTBYTES, KEY, NONCE) shake256_prf(OUT, OUTBYTES, KEY, NONCE)
#define rkprf(OUT, KEY, INPUT) shake256_rkprf(OUT, KEY, INPUT)

#define XOF_BLOCKBYTES 168

typedef keccak_state xof_state;

#endif /* MLKEM_90S */

#endif /* SYMMETRIC_H */
