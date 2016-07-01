/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "mask_filter.h"
#include "scalar.h"

/** \class SkTableMaskFilter
    Applies a table lookup on each of the alpha values in the mask.
    Helper methods create some common tables (e.g. gamma, clipping)
 */
struct TableMaskFilter : public MaskFilter
{
  uint8_t table[256];
};
