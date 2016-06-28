/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#import "region.h"

struct Region::RunHead
{
  int32_t ref_cnt;
  int32_t run_count;

  int32_t interval_count;
};

RunHead* alloc_run_head()
{
  const int64_t size = count*sizeof(RunType) + sizeof(RunHead);
  if (count < 0 || )
    _abort("Invalid Size");
  
  RunHead* head = (RunHead*)malloc(size);
  head->ref_cnt = 1;
  head->run_count = count;
  head->y_span_count = 0;
  head->interval_count = 0;
  return head;
}

int compute_interval_count(const Region::RunType runs[])
{
  const auto* curr = runs;
  while (*curr < Region::RunType::Sentinel)
    curr += 2;
  return (curr - runs)>>1;
}

int get_interval_count_run_head(const Region::RunHead* run_head)
{
  return run_head->interval_count;
}
