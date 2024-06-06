#ifndef KEM_H
#define KEM_H

#include <stdint.h>

void crypto_kem_keypair(unsigned char *pk,
                    unsigned char *sk,
                    const unsigned char *randomness);

void crypto_kem_enc(unsigned char *c,
                unsigned char *m,
                const unsigned char *pk,
                const unsigned char *coins);

void crypto_kem_dec(unsigned char *m,
                const unsigned char *c,
                const unsigned char *sk);

#endif
