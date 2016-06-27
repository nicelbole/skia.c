/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

struct Bitmap
{
  PixelRef* pixel_ref;
};

Bitmap* create_bitmap();
Bitmap* create_bitmap(const Bitmap&);
Bitmap* create_bitmap(Bitmap&&);
void delete_bitmap();
bool set_info_bitmap(const Bitmap&, size_t = 0);

size_t get_row_bytes_bitmap(Bitmap* bitmap)
{
  return bitmap->row_bytes;
}
