/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <cstdint>
#include <table_mask_filter.h>

static void make_gamma_table(uint8_t[256], Scalar);

static SkMaskFilter* create_gamma_mask_filter(SkScalar gamma)
{
  uint8_t table[256];
  make_gamma_table(table, gamma);
  return create_table_mask_filter(table);
}

TableMaskFilter* create_table_mask_filter()
{
  TableMaskFilter* filter = (TableMaskFilter*)malloc(sizeof(TableMaskFilter));
  for (int i = 0; i < 256; i++)
    filter->table[i] = i;
  return filter;
}

TableMaskFilter* create_table_mask_filter(TableMaskFilter* filter, const uint8_t table[256])
{
  TableMaskFilter* filter = (TableMaskFilter*)malloc(sizeof(TableMaskFilter));
  memcpy(filter->table, table, sizeof(filter->table));
  return filter;
}

void delete_table_mask_filter(TableMaskFilter* filter)
{
  free(filter);
}

/* Costruisce la tavola del gamma: table[x] = (x/255.)^gamma */
void make_gamma_table(uint8_t table[256], Scalar gamma)
{
  const float dx = 1 / 255.0f;
  const float g = scalar_to_float(gamma);

  float x = 0;
  for (int i = 0; i < 256; i++)
  {
    // float ee = powf(x, g) * 255;
    table[i] = TPin(float_round_2_int(powf(x, g) * 255), 0, 255);
    x += dx;
  }
}
