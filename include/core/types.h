static inline int32_t left_shift(int32_t value, int32_t shift)
{
  return (int32_t) ((uint32_t) value << shift);
}


static inline int64_t left_shift(int64_t value, int32_t shift)
{
  return (int64_t) ((uint64_t) value << shift);
}
