#include <cstdint>

struct RRect {
  enum Corner {
    UpperLeft,
    UpperRight,
    LowerRight,
    LowerLeft
  };
  
  enum Type {
    Empty,

    NinePatch,
    Complex
  };
  
private:
  Rect rect;
  Vector radii[4];
  int32_t type;
};

bool all_corners_circular(const RRect*);

Scalar get_height_rrect(const RRect* rrect)
{
  return get_height_rrect(rrect);
}

Scalar get_width_rrect(const RRect* rrect)
{
  return get_width_rect(rrect);
}

inline bool is_circle_rrect(const RRect* rect)
{
  return get_type_rrect(rrect) == RRect::Type::Circle;
}

inline bool is_complex_rrect(const RRect* rrect)
{
  return get_type_rrect(rrect) == RRect::Type::Complex;
}

inline bool is_nine_patch(const RRect* rrect)
{
  return get_type_rrect(rrect) == RRect::Type::NinePatch;
}

void set_empty_rrect(RRect* rrect)
{
  set_empty_rect(rrect->rect);
  memset(rrect->radii, 0, sizeof(rrect->radii));
  rrect->type = RRect::Type::Empty;
}

void set_rect_radii_rrect(const Rect&, const Vector[4]);
void set_nine_patch_rrect(const Rect&, Scalar, Scalar, Scalar, Scalar);
