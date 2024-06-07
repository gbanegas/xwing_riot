#ifndef crypto_uintN_h
#define crypto_uintN_h

#include <inttypes.h>
#define crypto_uintN uintN_t
#define crypto_uintN_signed intN_t

__attribute__((unused))
static crypto_uintN_signed crypto_uintN_signed_negative_mask(crypto_uintN_signed crypto_uintN_signed_x)
{
  return crypto_uintN_signed_x >> (N-1);
}

__attribute__((unused))
static crypto_uintN crypto_uintN_nonzero_mask(crypto_uintN crypto_uintN_x)
{
  return crypto_uintN_signed_negative_mask(crypto_uintN_x) | crypto_uintN_signed_negative_mask(-crypto_uintN_x);
}

__attribute__((unused))
static crypto_uintN crypto_uintN_zero_mask(crypto_uintN crypto_uintN_x)
{
  return ~crypto_uintN_nonzero_mask(crypto_uintN_x);
}

__attribute__((unused))
static crypto_uintN crypto_uintN_unequal_mask(crypto_uintN crypto_uintN_x,crypto_uintN crypto_uintN_y)
{
  crypto_uintN crypto_uintN_xy = crypto_uintN_x ^ crypto_uintN_y;
  return crypto_uintN_nonzero_mask(crypto_uintN_xy);
}

__attribute__((unused))
static crypto_uintN crypto_uintN_equal_mask(crypto_uintN crypto_uintN_x,crypto_uintN crypto_uintN_y)
{
  return ~crypto_uintN_unequal_mask(crypto_uintN_x,crypto_uintN_y);
}

__attribute__((unused))
static crypto_uintN crypto_uintN_smaller_mask(crypto_uintN crypto_uintN_x,crypto_uintN crypto_uintN_y)
{
  crypto_uintN crypto_uintN_xy = crypto_uintN_x ^ crypto_uintN_y;
  crypto_uintN crypto_uintN_z = crypto_uintN_x - crypto_uintN_y;
  crypto_uintN_z ^= crypto_uintN_xy & (crypto_uintN_z ^ crypto_uintN_x ^ (((crypto_uintN) 1) << (N-1)));
  return crypto_uintN_signed_negative_mask(crypto_uintN_z);
}

__attribute__((unused))
static crypto_uintN crypto_uintN_min(crypto_uintN crypto_uintN_x,crypto_uintN crypto_uintN_y)
{
  crypto_uintN crypto_uintN_xy = crypto_uintN_y ^ crypto_uintN_x;
  crypto_uintN crypto_uintN_z = crypto_uintN_y - crypto_uintN_x;
  crypto_uintN_z ^= crypto_uintN_xy & (crypto_uintN_z ^ crypto_uintN_y ^ (((crypto_uintN) 1) << (N-1)));
  crypto_uintN_z = crypto_uintN_signed_negative_mask(crypto_uintN_z);
  crypto_uintN_z &= crypto_uintN_xy;
  return crypto_uintN_x ^ crypto_uintN_z;
}

__attribute__((unused))
static crypto_uintN crypto_uintN_max(crypto_uintN crypto_uintN_x,crypto_uintN crypto_uintN_y)
{
  crypto_uintN crypto_uintN_xy = crypto_uintN_y ^ crypto_uintN_x;
  crypto_uintN crypto_uintN_z = crypto_uintN_y - crypto_uintN_x;
  crypto_uintN_z ^= crypto_uintN_xy & (crypto_uintN_z ^ crypto_uintN_y ^ (((crypto_uintN) 1) << (N-1)));
  crypto_uintN_z = crypto_uintN_signed_negative_mask(crypto_uintN_z);
  crypto_uintN_z &= crypto_uintN_xy;
  return crypto_uintN_y ^ crypto_uintN_z;
}

__attribute__((unused))
static void crypto_uintN_minmax(crypto_uintN *crypto_uintN_a,crypto_uintN *crypto_uintN_b)
{
  crypto_uintN crypto_uintN_x = *crypto_uintN_a;
  crypto_uintN crypto_uintN_y = *crypto_uintN_b;
  crypto_uintN crypto_uintN_xy = crypto_uintN_y ^ crypto_uintN_x;
  crypto_uintN crypto_uintN_z = crypto_uintN_y - crypto_uintN_x;
  crypto_uintN_z ^= crypto_uintN_xy & (crypto_uintN_z ^ crypto_uintN_y ^ (((crypto_uintN) 1) << (N-1)));
  crypto_uintN_z = crypto_uintN_signed_negative_mask(crypto_uintN_z);
  crypto_uintN_z &= crypto_uintN_xy;
  *crypto_uintN_a = crypto_uintN_x ^ crypto_uintN_z;
  *crypto_uintN_b = crypto_uintN_y ^ crypto_uintN_z;
}

#endif
