struct Point
{
  Scalar x, y;
};

inline Point make_point(Scalar x, Scalar y)
{
  Point pt;
  pt.set(x, y);
  return pt;
}
