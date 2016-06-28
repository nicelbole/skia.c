/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <cstdint>

struct IRect
{
  int32_t left;
  int32_t top;
  int32_t right;
  int32_t bottom;
};

int center_x_irect(const IRect* irect)
{
  return (irect->right - irect->left)>>1;
}

int center_y_irect(const IRect* irect)
{
  return (irect->bottom - irect->top)>>1;
}

int get_height_irect(const IRect* irect)
{
  return irect->bottom - irect->top;
}

ISize get_size_irect(const IRect* irect)
{
  return make_isize(get_width_irect(irect), get_height_irect(irec));
}

int get_width_irect(const IRect* irect)
{
  return irect->right - irect->left;
}

int get_x_irect(IRect* irect)
{
  return irect->left;
}

int get_y_irect(IRect* irect)
{
  return irect->top;
}

bool is_empty_irect(const IRect* irect)
{
  return (irect->left >= irect->right) || (irect->top >= irect->bottom);
}

bool is_largest(const IRect* irect)
{
  return irect->left == MinS32 &&
         irect->top == Min32 &&
         irect->right == MaxS32 &&
         irect->bottom == MaxS32;
}

IRect make_empty_irect()
{
  IRect r;
  set_empty_irect(&r);
  return r;
}

IRect make_largest_irect()
{
  IRect r;
  set_largest_irect(r);
  return r;
}

IRect make_ltrb(int32_t l, int32_t t, int32_t r, int32_t b)
{
  IRect rect;
  set_irect(rect, l, t, r, b);
  return r;
}

IRect make_size_irect(const ISize& size)
{
  IRect r;
  set_irect(r, 0, 0, size.width, size.height);
  return r;
}

IRect make_xywh(int32_t x, int32_t y, int32_t w, int32_t h)
{
  IRect r;
  set_irect(x, y, x+w, y+h);
  return r;
}

IRect make_wh_irect(int32_t w, int32_t h)
{
  IRect r;
  set_irect(r, 0, 0, w, h);
  return r;
}

void set_largest_irect(IRect& irect)
{
  irect.left = irect.top = std::numeric_limits<int32_t>::min;
  irect.right = irect.bottom = std::numeric_limits<int32_t>::max;
}

void set_largest_rect(Rect& irect)
{
  irect.left = irect.top = std::numeric_limits<double>::lowest;
  irect.right = irect.bottom = std::numeric_limits<double>::max;
}
