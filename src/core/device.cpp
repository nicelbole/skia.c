/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#import "device.h"

BaseDevice* create_base_device(const SurfaceProps& sprops)
{
  BaseDevice* device = malloc(sizeof(BaseDevice));

  device->surface_props(sprops);
  set_zero_ipoint(device->origin);
  device->meta_data = nullptr;
  
  return device;
}

void delete_base_device(BaseDevice* device)
{
  free(device->meta_data);
}

MetaData& get_meta_data_base_device(BaseDevice* device)
{
  if (device->meta_data == nullptr)
    device->meta_data = create_meta_data();
  return device->meta_data;
}

ImageInfo get_image_info(const BaseDevice* device)
{
  return make_unknown_image_info();
}
