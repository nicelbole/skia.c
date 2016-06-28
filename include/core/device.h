/*
 * Copyright 2010 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

struct BaseDevice
{
  IPoint origin;
  MetaData* meta_data;
  SurfaceProps surface_props;
};

BaseDevice* create_base_device(const SurfaceProps&);
MetaData& get_meta_data_base_device(BaseDevice*);
ImageInfo get_image_info(const BaseDevice*);
