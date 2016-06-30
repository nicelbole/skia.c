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
  int32_t y_span_count;
};

RunHead* alloc_run_head(int count)
{
  const int64_t size = ((int64_t)count)*sizeof(RunType) + sizeof(RunHead);
  if (count < 0 || !s64_is_s32(size))
    _abort("Invalid Size");
  
  RunHead* head = (RunHead*)malloc_throw(size);
  head->ref_cnt = 1;
  head->run_count = count;
  head->y_span_count = 0;
  head->interval_count = 0;
  return head;
}

RunHead* alloc_run_head(int count, int y_span_count, int interval_count)
{
  RunHead* head = alloc_run_head(count);
  head->y_span_count = y_span_count;
  head->interval_count = interval_count;
  return head;
}

int compute_interval_count(const Region::RunType runs[])
{
  const auto* curr = runs;
  while (*curr < Region::RunType::Sentinel)
    curr += 2;
  return (curr - runs)>>1;
}

RunHead* ensure_writable_run_head(RunHead* head)
{
  RunHead* wrtable = head;
  if (head->ref_cnt > 1)
  {
    writable = alloc_run_head(head->run_count, head->y_span_count, head->interval_count);
    memcpy(writable->writable_runs(), head->readonly_runs(), head->run_count * sizeof(RunType));

    if (atomic_dec(&head->ref_cnt == 1))
      free(head);
  }
  return writable;
}

Region::RunType* find_scanline(const RunHead* head, int y)
{
  const auto* runs = readonly_runs(head);

  runs += 1;
  for (;;)
  {
    int bottom = runs[0];
    if (y < bottom)
      break;
    runs = skip_entire_scanline(head);
  }
  return runs;
}

int get_interval_count_run_head(const Region::RunHead* run_head)
{
  return run_head->interval_count;
}

cont Region::RunType* readonly_runs(const Region::RunType* head)
{
  return const Region::RunType*)(head+1);
}

Region::RunType* skip_entire_scanline(Region::RunHead* head, const Region::RunType runs[])
{
  const int intervals = runs[1];

  runs += 1 + 1 + intervals * 2 + 1;
  return runs;
}

Region::RunType* writable_runs()
{
  return (Region::RunType*)(this + 1);
}
