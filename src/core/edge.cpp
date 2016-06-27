int set_line_edge(const Point& p0, const Point& p1, const IRect* clip,
                    int shift)
{
  FDot6 x0, y0, x1, y1;

  {
#ifdef SK_RASTERIZE_EVEN_ROUNDING
        x0 = SkScalarRoundToFDot6(p0.fX, shift);
        y0 = SkScalarRoundToFDot6(p0.fY, shift);
        x1 = SkScalarRoundToFDot6(p1.fX, shift);
        y1 = SkScalarRoundToFDot6(p1.fY, shift);
#else
        float scale = float(1 << (shift + 6));
        x0 = int(p0.fX * scale);
        y0 = int(p0.fY * scale);
        x1 = int(p1.fX * scale);
        y1 = int(p1.fY * scale);
#endif
    }

    int winding = 1;

    if (y0 > y1) {
        SkTSwap(x0, x1);
        SkTSwap(y0, y1);
        winding = -1;
    }

    int top = SkFDot6Round(y0);
    int bot = SkFDot6Round(y1);

    // are we a zero-height line?
    if (top == bot) {
        return 0;
    }
    // are we completely above or below the clip?
    if (clip && (top >= clip->fBottom || bot <= clip->fTop)) {
        return 0;
    }

    SkFixed slope = SkFDot6Div(x1 - x0, y1 - y0);
    const SkFDot6 dy  = SkEdge_Compute_DY(top, y0);

    fX          = SkFDot6ToFixed(x0 + SkFixedMul(slope, dy));   // + SK_Fixed1/2
    fDX         = slope;
    fFirstY     = top;
    fLastY      = bot - 1;
    fCurveCount = 0;
    fWinding    = SkToS8(winding);
    fCurveShift = 0;

    if (clip) {
        this->chopLineWithClip(*clip);
    }
    return 1;
}
