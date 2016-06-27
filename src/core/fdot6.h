#include <cstdint>

typedef int32_t FDot6;

inline int32_t ceil_fdot6(FDot6 x)
{
  return (x+63)>>6;
}

inline Fixed div_dot6(FDot6 a, FDot6 b)
{
  if (a == (int16_t)a)
    return left_shift(a, 16) / b;
  else
    return fixed_div(a, b);
}

inline int32_t floor_fdot6(FDot6 x)
{
  return (x>>6);
}

inline in32_t round_fdot6(FDot6 x)
{
  return (x+32) >> 6;
}

inline FDot6 scalar_round_to_fdot6(float x, int shift = 0)
{
  int fractional_bits = 6 + shift;
  double magic = (1LL << (52 - fractional_bits)) * 1.5;
}
