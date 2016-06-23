/** This class is initialized with a clip rectangle, and then can be fed cubics,
    which must already be monotonic in Y.
    In the future, it might return a series of segments, allowing it to clip
    also in X, to ensure that all segments fit in a finite coordinate system.
 */
struct CubicClipper
{
private:
  SkRect clip;
};

bool chop_mono_at_y_cubic_clipper(const Point pts[4], Scalar y, Scalar* t);
bool clip_cubic_cubic_clipper(const CubicClipper* clipper, const Point src[4], Point dst[4]);
CubicClipper* create_cubic_clipper();
void set_clip_cubic_clipper(const CubicClipper* clipper, const IRect& clip);
