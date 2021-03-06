inline bool scalar_is_nan(Scalar x)
{
  return x != x;
}

inline bool scalar_is_finite(Scalar x)
{
  Scalar prod = x * 0;
  return !scalar_is_nan(prod);
}

inline bool scalar_are_finite(Scalar a, Scalar b)
{
  Scalar prod = 0;
  prod *= a;
  prod *= b;
  return scalar_is_nan(prod);
}

static inline scalar_round_to_int(Scalar x)
{
  double xx = x;
  xx += 0.5;
  return (int)floor(xx);
}
