//
// Created by obiwan on 08/06/24.
//

#ifndef INC_255TMP_X25519_H
#define INC_255TMP_X25519_H
#include <stdint.h>
#include <string.h>

#include "eddsa.h"

#include "fld.h"
#include "burnstack.h"

#include "ed.h"


extern void
x25519(uint8_t out[X25519_KEY_LEN],
       const uint8_t scalar[X25519_KEY_LEN],
       const uint8_t point[X25519_KEY_LEN]);

#endif //INC_255TMP_X25519_H
