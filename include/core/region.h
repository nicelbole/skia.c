/*
 * Copyright 2005 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

struct Region
{
  typedef int32_t RunType;

  IRect bounds;
  RunHead* run_head;
};

Region* create_region();
Region* create_region(const Region&);
bool get_boundary_path_region(const Region*, Path* path);
