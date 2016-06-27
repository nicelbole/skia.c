/*
 * Copyright 2009 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#import "cubic_clipper.h"
#include "SkGeometry.h"

CubicClipper create_cubic_clipper()
{
  CubicClipper clipper = (CubicClipper*)malloc(sizeof(CubicClipper));
  set_empty_rect(clipper->clip);
  return clipper;
}

void set_clip_cubic_clipper(CubicClipper* clipper, const IRect& clip)
{
  set_rect(clipper->clip, clipper->clip);
}



bool chop_mono_at_y(const Point pts[4], Scalar y, Scalar* t)
{
  SkScalar ycrv[4];
  ycrv[0] = pts[0].fY - y;
  ycrv[1] = pts[1].fY - y;
  ycrv[2] = pts[2].fY - y;
  ycrv[3] = pts[3].fY - y;

#ifdef NEWTON_RAPHSON    // Quadratic convergence, typically <= 3 iterations.
    // Initial guess.
    // TODO(turk): Check for zero denominator? Shouldn't happen unless the curve
    // is not only monotonic but degenerate.
    SkScalar t1 = ycrv[0] / (ycrv[0] - ycrv[3]);

    // Newton's iterations.
    const SkScalar tol = SK_Scalar1 / 16384;  // This leaves 2 fixed noise bits.
    SkScalar t0;
    const int maxiters = 5;
    int iters = 0;
    bool converged;
    do {
        t0 = t1;
        SkScalar y01   = SkScalarInterp(ycrv[0], ycrv[1], t0);
        SkScalar y12   = SkScalarInterp(ycrv[1], ycrv[2], t0);
        SkScalar y23   = SkScalarInterp(ycrv[2], ycrv[3], t0);
        SkScalar y012  = SkScalarInterp(y01,  y12,  t0);
        SkScalar y123  = SkScalarInterp(y12,  y23,  t0);
        SkScalar y0123 = SkScalarInterp(y012, y123, t0);
        SkScalar yder  = (y123 - y012) * 3;
        // TODO(turk): check for yder==0: horizontal.
        t1 -= y0123 / yder;
        converged = SkScalarAbs(t1 - t0) <= tol;  // NaN-safe
        ++iters;
    } while (!converged && (iters < maxiters));
    *t = t1;                  // Return the result.

    // The result might be valid, even if outside of the range [0, 1], but
    // we never evaluate a Bezier outside this interval, so we return false.
    if (t1 < 0 || t1 > SK_Scalar1)
        return false;         // This shouldn't happen, but check anyway.
    return converged;

#else  // BISECTION    // Linear convergence, typically 16 iterations.

    // Check that the endpoints straddle zero.
    SkScalar tNeg, tPos;    // Negative and positive function parameters.
    if (ycrv[0] < 0) {
        if (ycrv[3] < 0)
            return false;
        tNeg = 0;
        tPos = SK_Scalar1;
    } else if (ycrv[0] > 0) {
        if (ycrv[3] > 0)
            return false;
        tNeg = SK_Scalar1;
        tPos = 0;
    } else {
        *t = 0;
        return true;
    }

    const SkScalar tol = SK_Scalar1 / 65536;  // 1 for fixed, 1e-5 for float.
    int iters = 0;
    do {
        SkScalar tMid = (tPos + tNeg) / 2;
        SkScalar y01   = SkScalarInterp(ycrv[0], ycrv[1], tMid);
        SkScalar y12   = SkScalarInterp(ycrv[1], ycrv[2], tMid);
        SkScalar y23   = SkScalarInterp(ycrv[2], ycrv[3], tMid);
        SkScalar y012  = SkScalarInterp(y01,     y12,     tMid);
        SkScalar y123  = SkScalarInterp(y12,     y23,     tMid);
        SkScalar y0123 = SkScalarInterp(y012,    y123,    tMid);
        if (y0123 == 0) {
            *t = tMid;
            return true;
        }
        if (y0123 < 0)  tNeg = tMid;
        else            tPos = tMid;
        ++iters;
    } while (!(SkScalarAbs(tPos - tNeg) <= tol));   // Nan-safe

    *t = (tNeg + tPos) / 2;
    return true;
#endif  // BISECTION
}


bool clip_cubic_cubic_clipper(CubicClipper* clipper, const Point stc_pts[4], Point dst[4])
{
  bool reverse;

  // we need the data to be monotonically descending in Y
  if (src_pts[0].fY > src_pts[3].fY)
  {
    dst[0] = src_pts[3];
    dst[1] = src_pts[2];
    dst[2] = src_pts[1];
    dst[3] = src_pts[0];
    reverse = true;
  }
  else
  {
    memcpy(dst, src_pts, 4 * sizeof(Point));
    reverse = false;
  }

  // are we completely above or below
  const Scalar ctop = clipper->clip.top;
  const Scalar cbot = clipper->clip.bottom;
  if (dst[3].fY <= ctop || dst[0].fY >= cbot)
    return false;

  Scalar t;
  Point tmp[7]; // for SkChopCubicAt

  // are we partially above
  if (dst[0].fY < ctop && chop_mono_at_y_cubic_clipper(dst, ctop, &t))
  {
    SkChopCubicAt(dst, tmp, t);
    dst[0] = tmp[3];
    dst[1] = tmp[4];
    dst[2] = tmp[5];
  }

  // are we partially below
  if (dst[3].fY > cbot && ChopMonoAtY(dst, cbot, &t))
  {
    SkChopCubicAt(dst, tmp, t);
    dst[1] = tmp[1];
    dst[2] = tmp[2];
    dst[3] = tmp[3];
  }

  if (reverse)
  {
    SkTSwap<SkPoint>(dst[0], dst[3]);
    SkTSwap<SkPoint>(dst[1], dst[2]);
  }

  return true;
}