static inline Nx2s interp(const Nx2s&, const Nx2s&, const Nx2s&);

void chop_cubic_at(const Point src[4], Point dst[7], Scalar t)
{
  Nx2s p0 = from_point(src[0]);
  Nx2s p1 = from_point(src[1]);
  Nx2s p2 = from_point(src[2]);
  Nx2s p3 = from_point(src[3]);
  Nx2s tt(t);

  Nx2s ab = interp(p0, p1, tt);
  Nx2s bc = interp(p1, p2, tt);
  Nx2s cd = interp(p2, p3, tt);
  Nx2s abc = interp(ab, bc, tt);
  Nx2s bcd = interp(bc, cd, tt);
  Nx2s abcd = interp(abc, bcd, tt);

  dst[0] = src[0];
  dst[1] = to_point(ab);
  dst[2] = to_point(abc);
  dst[3] = to_point(abcd);
  dst[4] = to_point(bcd);
  dst[5] = to_point(cd);
  dst[6] = src[3];
}

static inline Nx2s interp(const Nx2s& v0, const Nx2s& v1, const Nx2s& t)
{
  return {v0.x + (v1.x-v0.x)*t, v0.y + (v1.y-v0.y)*t};
}
