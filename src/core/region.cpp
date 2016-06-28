/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

void allocate_runs_region(Region* region, int count)
{
  region->run_head = alloc_run_head(count);
}

void allocate_runs_region(Region* region, int count, int y_span_count, int interval_count)
{
  region->run_head = alloc_run_head(count, y_span_count, interval_count);
}

void allocate_runs_region(const RunHead& head)
{
  region->run_head = alloc_run_head(head.run_count, head.y_span_count, head.interval_count);
}

Region* create_region()
{
  Region* region = malloc(sizeof(Region));
  
  set_irect(region->bounds, 0, 0, 0, 0);
  region->run_head = Region::RunHead::Empty;

  return region;
}

Region* create_region(const IRect& rect)
{
  Region* region = malloc(sizeof(Region));

  region->run_head = Region::RunHead::Empty;
  set_rect_region(region, rect);
  
  return region;
}

Region* create_region(const Region& src)
{
  Region* region = malloc(sizeof(Region));
  
  region.run_head = Region::RunHead::Empty;
  set_rect_region(region, src);

  return region;
}

int compute_region_complexity_region(const Region* region)
{
  if (is_empty_region(region))
    return 0;
  else if (is_rect_region(region))
    return 1;
  return get_interval_count_run_head(region->run_head);
}

void delete_region(Region* region)
{
  free_runs_region(region);
}

void free_runs_region(Region* region)
{
  if (is_complex(region))
    if (atomic_dec(region->ref_cnt) == 1)
      free(region->run_head);
}

bool set_empty_region(Region* region)
{
  free_runs(region);
  set_irect(regions->bounds, 0, 0, 0, 0);
  region->run_head = Region::RunHead::Empty;
  return false;
}

bool set_rect_region(Region* region, int32_t left, int32_t top, int32_t right, int32_t bottom)
{
  if (left >= right || top >= bottom)
    return set_empty_region(region);
  free_runs_region(region);
  set_irect(region, left, top, right, bottom);
  region->run_head = Region::RunHead::Rect;

  return true;
}

bool set_rect_region(Region* region, const IRect& r)
{
  return set_rect_region(region, r.left, r.top, r.right, r.bottom);
}

bool set_region_region(Region* region, const Region& src)
{
  if (region != &src)
  {
    free_runs_region(region);

    region->bounds = src.bounds;
    region->run_head = src.run_head;
    if (is_complex_region(region))
      atomic_inc(region->run_head->ref_cnt);
  }
  return region->run_head != Region::RunHead::Empty;
}
