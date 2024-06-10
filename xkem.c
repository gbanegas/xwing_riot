
#include "xkem.h"
#include "params.h"
#include <stdio.h>

void print_hex(unsigned char *e, size_t l) {
    printf("kem: ");
    for (int i = 0; i < l; i++) {
        printf("%x,", e[i]);
    }
    printf("\n");
}

/*************************************************
 * Name:        crypto_xkem_keypair_derand
 *
 * Description: Generates public and private key for the CCA-secure
 *              X-Wing key encapsulation mechanism
 *
 * Arguments:   - unsigned char *pk:               pointer to output public key (of length XWING_PUBLICKEYBYTES bytes)
 *              - unsigned char *sk:               pointer to output private key (of length XWING_SECRETKEYBYTES bytes)
 *              - const unsigned char *randomness: pointer to input random coins used as seed (of length 3*XWING_SYMBYTES bytes)
 *                                                 to deterministically generate all randomness
 **************************************************/
int crypto_xkem_keypair_derand(unsigned char *pk,
                               unsigned char *sk,
                               const unsigned char *randomness) {
   // print_hex(pk, XWING_PUBLICKEYBYTES);
    crypto_kem_keypair(pk, sk, randomness);
   // print_hex(pk, XWING_PUBLICKEYBYTES);
    pk += MLKEM_PUBLICKEYBYTES;
    sk += MLKEM_SECRETKEYBYTES;
    randomness += 2 * XWING_SYMBYTES;
    x25519_base(pk, randomness);
   // lib25519_nG_montgomery25519(pk, randomness);
    //pk -= MLKEM_PUBLICKEYBYTES;
    //print_hex(pk, XWING_PUBLICKEYBYTES);
    //pk += MLKEM_PUBLICKEYBYTES;
    memcpy(sk, randomness, DH_BYTES);
    memcpy(sk + DH_BYTES, pk, DH_BYTES);
    return 0;
}

/*************************************************
 * Name:        crypto_xkem_keypair
 *
 * Description: Generates public and private key for the CCA-secure
 *              X-Wing key encapsulation mechanism
 *
 * Arguments:   - unsigned char *pk:               pointer to output public key (of length XWING_PUBLICKEYBYTES bytes)
 *              - unsigned char *sk:               pointer to output private key (of length XWING_SECRETKEYBYTES bytes)
 **************************************************/
int crypto_xkem_keypair(unsigned char *pk,
                        unsigned char *sk) {
    unsigned char buf[3 * DH_BYTES];
    randombytes(buf, 3 * DH_BYTES);
    return crypto_xkem_keypair_derand(pk, sk, buf);
}

/*************************************************
 * Name:        crypto_xkem_enc_derand
 *
 * Description: Generates cipher text and shared
 *              secret for given public key
 *
 * Arguments:   - unsigned char *ct:          pointer to output ciphertext (of length XWING_CIPHERTEXTBYTES bytes)
 *              - unsigned char *ss:          pointer to output decrypted message (of length XWING_SSBYTES bytes)
 *              - const unsigned char *pk:    pointer to input public key (of length XWING_PUBLICKEYBYTES bytes)
 *              - const unsigned char *coins: pointer to input random coins used as seed (of length 2*XWING_SYMBYTES bytes)
 *                                            to deterministically generate all randomness
 **************************************************/
int crypto_xkem_enc_derand(unsigned char *ct,
                           unsigned char *ss,
                           const unsigned char *pk,
                           const unsigned char *coins) {
    unsigned char buffer[XWING_PRFINPUT];
    unsigned char *bufferPointer = buffer;

    memcpy(buffer, XWING_LABEL, 6);
    bufferPointer += 6;

    crypto_kem_enc(ct, bufferPointer, pk, coins);

    pk += MLKEM_PUBLICKEYBYTES;
    ct += MLKEM_CIPHERTEXTBYTES;
    coins += DH_BYTES;
    bufferPointer += MLKEM_SSBYTES;

   // lib25519_nG_montgomery25519(ct, coins);
    x25519_base(ct, coins);
    DH(bufferPointer, coins, pk);
    //lib25519_dh(bufferPointer, pk, coins);
    bufferPointer += DH_BYTES;

    memcpy(bufferPointer, ct, DH_BYTES);
    memcpy(bufferPointer + DH_BYTES, pk, DH_BYTES);

    sha3_256(ss, buffer, XWING_PRFINPUT);
    return 0;
}

/*************************************************
 * Name:        crypto_xkem_enc
 *
 * Description: Generates cipher text and shared
 *              secret for given public key
 *
 * Arguments:   - unsigned char *ct:          pointer to output ciphertext (of length XWING_CIPHERTEXTBYTES bytes)
 *              - unsigned char *ss:          pointer to output decrypted message (of length XWING_SSBYTES bytes)
 **************************************************/
int crypto_xkem_enc(unsigned char *ct,
                    unsigned char *ss,
                    const unsigned char *pk) {
    unsigned char buf[2 * DH_BYTES];
    randombytes(buf, 2 * DH_BYTES);

    return crypto_xkem_enc_derand(ct, ss, pk, buf);
}

/*************************************************
 * Name:        crypto_xkem_dec
 *
 * Description: Generates shared secret for given
 *              cipher text and private key
 *
 * Arguments:   - unsigned char *ss:        pointer to output decrypted message (of length XWING_SSBYTES bytes)
 *              - const unsigned char *ct:  pointer to input ciphertext (of length XWING_CIPHERTEXTKEYBYTES bytes)
 *              - const unsigned char *sk:  pointer to input secret key (of length XWING_SECRETKEYBYTES bytes)
 **************************************************/
int crypto_xkem_dec(uint8_t *ss,
                    const uint8_t *ct,
                    const uint8_t *sk) {
    unsigned char buffer[XWING_PRFINPUT];
    unsigned char *bufferPointer = buffer;

    memcpy(bufferPointer, XWING_LABEL, 6);
    bufferPointer += 6;

    crypto_kem_dec(bufferPointer, ct, sk);

    sk += MLKEM_SECRETKEYBYTES;
    ct += MLKEM_CIPHERTEXTBYTES;
    bufferPointer += MLKEM_SSBYTES;

    DH(bufferPointer, sk, ct);
   // lib25519_dh(bufferPointer, ct, sk);
    sk += DH_BYTES;
    bufferPointer += DH_BYTES;

    memcpy(bufferPointer, ct, DH_BYTES);
    memcpy(bufferPointer + DH_BYTES, sk, DH_BYTES);

    sha3_256(ss, buffer, XWING_PRFINPUT);
    return 0;
}
