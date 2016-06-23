/*
 * Copyright 2008 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <cstdlib>
#import "canvas.h"
#import "deque.h"

#ifdef TRACE_SAVERESTORE
static int canvas_counter = 0;
#endif

static void inc_canvas(Canvas* canvas);

Canvas* create_canvas(void)
{
	Canvas* canvas = (Canvas*)malloc(sizeof(Canvas));
	canvas->mc_stack = create_deque(sizeof(MCRec), canvas->mc_rec_storage,
			sizeof(mc_rec_storage));
	canvas->fProps(SkSurfaceProps::kLegacyFontHost_InitType);
	canvas->fConservativeRasterClip = false;
	inc_canvas(canvas);

	init_canvas(canvas, nullptr, kDefault_InitFlags);

	return canvas;
}

#ifdef TRACE_SAVERESTORE
void inc_canvas(Canvas* canvas)
{
	++canvas->counter;
	printf("----- inc canvas %d\n", gCanvasCounter);
}
#else
void inc_canvas(Canvas* canvas) {}
#endif


void init_canvas(Canvas*)
{
	//TODO
}
