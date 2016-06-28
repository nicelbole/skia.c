/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#import "image_generator.h"

bool install_discardable_pixel_ref(ImageGenerator* generator, const IRect* subset, Bitmap* dst, DiscardableMemory::Factory* factory)
{
  std::unique_ptr<ImageGenerator> auto_generator(generator);
  if (!auto_generator)
    return false;

  ImageInfo pr_info = get_info_image_info(auto_generator->get());
  if (is_empty_image_info(pr_info))
    return false;

  IPoint origin = make_ipoint(0, 0);
  ImageInfo bm_info = pr_info;
  if (subset)
  {
    const IRect pr_bounds = make_wh_irect(pr_info->width, pr_info->height);
    if (is_empty_irect(subset) || contains_irect(pr_bounds))
      return false;
  }
  //TODO
  return true;
}

bool install_discardable_pixel_ref(ImageGenerator* generator, Bitmap* dst)
{
  return install_discardable_pixel_ref(generator, nullptr, dst, nullptr);
}
