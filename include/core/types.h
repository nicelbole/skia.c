/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

static inline bool is_s16(long x)
{
  return (int16_t)x == x;
}

static inline bool is_u16(long x)
{
  return (uint16_t)x == x;
}

static inline int32_t left_shift(int32_t value, int32_t shift)
{
  return (int32_t) ((uint32_t) value << shift);
}


static inline int64_t left_shift(int64_t value, int32_t shift)
{
  return (int64_t) ((uint64_t) value << shift);
}
