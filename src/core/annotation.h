/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**
 *  Annotate the canvas by associating the specified URL with the
 *  specified rectangle (in local coordinates, just like drawRect).
 *
 *  If the backend of this canvas does not support annotations, this call is
 *  safely ignored.
 *
 *  The caller is responsible for managing its ownership of the SkData.
 */
void annotate_rect_with_url(Canvas*, const Rect&, Data*);
