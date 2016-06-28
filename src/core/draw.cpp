void draw_rrect_draw(const Draw* draw, const RRect& rrect, const Paint& paint) const
{
  if (is_empty_raster_clip(draw->rc))
    return;

  // TODO: Investigate optimizing these options. They are in the same
  // order as SkDraw::drawPath, which handles each case. It may be
  // that there is no way to optimize for these using the SkRRect path.
  Scalar coverage;
  if (SkDrawTreatAsHairline(paint, *fMatrix, &coverage))
    goto DRAW_PATH;

  if (paint.getPathEffect() || paint.getStyle() != SkPaint::kFill_Style) {
            goto DRAW_PATH;
        }

        if (paint.getRasterizer()) {
            goto DRAW_PATH;
        }
    }

    if (paint.getMaskFilter()) {
        // Transform the rrect into device space.
        SkRRect devRRect;
        if (rrect.transform(*fMatrix, &devRRect)) {
            SkAutoBlitterChoose blitter(fDst, *fMatrix, paint);
            if (paint.getMaskFilter()->filterRRect(devRRect, *fMatrix, *fRC, blitter.get())) {
                return; // filterRRect() called the blitter, so we're done
            }
        }
    }

DRAW_PATH:
    // Now fall back to the default case of using a path.
    SkPath path;
    path.addRRect(rrect);
    this->drawPath(path, paint, nullptr, true);
}
