/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

constexpr const char* AnnotationKeys_URL = "SkAnnotationKey_URL";

void annotate_rect_with_url(Canvas* canvas, const Rect& rect, Data* value)
{
  if (nullptr == value)
    return;
  draw_annotation_canvas(canvas, rect, AnnotationKeys_URL
			 , value);
}
