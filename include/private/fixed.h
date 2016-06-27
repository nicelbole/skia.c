// The divide may exceed 32 bits. Clamp to a signed 32 bit result.
inline SkFixedDiv(numer, denom)
{
    SkToS32(SkTPin<int64_t>((SkLeftShift((int64_t)numer, 16) / denom), SK_MinS32, SK_MaxS32))
}
