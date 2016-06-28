/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

enum AlphaType {
  Unknown,
  Opaque,
  Premultiplied,
  Unpremultiplied,
  Last = Unpremultiplied
};

static inline bool is_opaque_alpha_type(AlphaType at)
{
  return at == AlphaType::Opaque;
}

static inline bool is_valid(unsigned value)
{
  return value <= AlphaType::Last;
}

enum ColorType {
  Unknown,
  Alpha8,
  RGB565,
  ARGB4444,
  RGBA8888,
  BGRA8888,
  Index8,
  Gray8,
  RGBAF16,
  Last = RGBAF16,
  N32 = RGBA8888
};

enum ColorProfileType {
  Linear,
  SRGB,
  Last = SRGB
};

struct ImageInfo
{
  int width;
  int height;
  ColorType color_type;
  AlphaType alpha_type;
  ColorProfileType profile_type;
};

ImageInfo* create_image_info()
{
  ImageInfo* iinfo = malloc(sizeof(ImageInfo));

  iinfo->width = 0;
  iinfo->height = 0;
  iinfo->color_type = ColorType::Unknown;
  iinfo->alpha_type = AlphaType::Unknown;
  iinfo->profile-type = ColorProfileType::Linear;
  
  return iinfo;
}

ImageInfo* make_image_info(int width, int height, ColorType ct, AlphaType at, ColorProfileType pt = ColorProfileType::Linear)
{
  return create_image_info(width, height, ct, at, pt);
}
