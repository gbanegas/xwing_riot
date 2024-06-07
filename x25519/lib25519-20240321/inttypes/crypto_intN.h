#ifndef crypto_intN_h
#define crypto_intN_h

#include <inttypes.h>
#define crypto_intN intN_t

__attribute__((unused))
static crypto_intN crypto_intN_negative_mask(crypto_intN crypto_intN_x)
{
  return crypto_intN_x >> (N-1);
}

__attribute__((unused))
static crypto_intN crypto_intN_nonzero_mask(crypto_intN crypto_intN_x)
{
  return crypto_intN_negative_mask(crypto_intN_x) | crypto_intN_negative_mask(-crypto_intN_x);
}

__attribute__((unused))
static crypto_intN crypto_intN_zero_mask(crypto_intN crypto_intN_x)
{
  return ~crypto_intN_nonzero_mask(crypto_intN_x);
}

__attribute__((unused))
static crypto_intN crypto_intN_positive_mask(crypto_intN crypto_intN_x)
{
  crypto_intN crypto_intN_z = -crypto_intN_x;
  crypto_intN_z ^= crypto_intN_x & crypto_intN_z;
  return crypto_intN_negative_mask(crypto_intN_z);
}

__attribute__((unused))
static crypto_intN crypto_intN_unequal_mask(crypto_intN crypto_intN_x,crypto_intN crypto_intN_y)
{
  crypto_intN crypto_intN_xy = crypto_intN_x ^ crypto_intN_y;
  return crypto_intN_nonzero_mask(crypto_intN_xy);
}

__attribute__((unused))
static crypto_intN crypto_intN_equal_mask(crypto_intN crypto_intN_x,crypto_intN crypto_intN_y)
{
  return ~crypto_intN_unequal_mask(crypto_intN_x,crypto_intN_y);
}

__attribute__((unused))
static crypto_intN crypto_intN_smaller_mask(crypto_intN crypto_intN_x,crypto_intN crypto_intN_y)
{
  crypto_intN crypto_intN_xy = crypto_intN_x ^ crypto_intN_y;
  crypto_intN crypto_intN_z = crypto_intN_x - crypto_intN_y;
  crypto_intN_z ^= crypto_intN_xy & (crypto_intN_z ^ crypto_intN_x);
  return crypto_intN_negative_mask(crypto_intN_z);
}

__attribute__((unused))
static crypto_intN crypto_intN_min(crypto_intN crypto_intN_x,crypto_intN crypto_intN_y)
{
  crypto_intN crypto_intN_xy = crypto_intN_y ^ crypto_intN_x;
  crypto_intN crypto_intN_z = crypto_intN_y - crypto_intN_x;
  crypto_intN_z ^= crypto_intN_xy & (crypto_intN_z ^ crypto_intN_y);
  crypto_intN_z = crypto_intN_negative_mask(crypto_intN_z);
  crypto_intN_z &= crypto_intN_xy;
  return crypto_intN_x ^ crypto_intN_z;
}

__attribute__((unused))
static crypto_intN crypto_intN_max(crypto_intN crypto_intN_x,crypto_intN crypto_intN_y)
{
  crypto_intN crypto_intN_xy = crypto_intN_y ^ crypto_intN_x;
  crypto_intN crypto_intN_z = crypto_intN_y - crypto_intN_x;
  crypto_intN_z ^= crypto_intN_xy & (crypto_intN_z ^ crypto_intN_y);
  crypto_intN_z = crypto_intN_negative_mask(crypto_intN_z);
  crypto_intN_z &= crypto_intN_xy;
  return crypto_intN_y ^ crypto_intN_z;
}

__attribute__((unused))
static void crypto_intN_minmax(crypto_intN *crypto_intN_a,crypto_intN *crypto_intN_b)
{
  crypto_intN crypto_intN_x = *crypto_intN_a;
  crypto_intN crypto_intN_y = *crypto_intN_b;
  crypto_intN crypto_intN_xy = crypto_intN_y ^ crypto_intN_x;
  crypto_intN crypto_intN_z = crypto_intN_y - crypto_intN_x;
  crypto_intN_z ^= crypto_intN_xy & (crypto_intN_z ^ crypto_intN_y);
  crypto_intN_z = crypto_intN_negative_mask(crypto_intN_z);
  crypto_intN_z &= crypto_intN_xy;
  *crypto_intN_a = crypto_intN_x ^ crypto_intN_z;
  *crypto_intN_b = crypto_intN_y ^ crypto_intN_z;
}

#endif
