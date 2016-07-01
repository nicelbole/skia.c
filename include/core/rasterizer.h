/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#import "flattenable.h"
#include "mask.h"

struct MaskFilter;
struct Matrix;
struct Path;
struct IRect;

struct Rasterizer
{
  /* Turn the path into a mask, respecting the specified local->device matrix.
   */
  bool rasterize(const Path& path, const Matrix& matrix,
                   const IRect* clipBounds, MaskFilter* filter,
                   Mask* mask, Mask::CreateMode mode) const;

  SK_DEFINE_FLATTENABLE_TYPE(SkRasterizer)

  virtual bool on_rasterize(const Path& path, const Matrix& matrix,
    const IRect* clipBounds, Mask* mask, Mask::CreateMode mode) const;
};

Rasterizer* create_rasterizer();
