#include <cstdint>

struct ISize
{
  int32_t width;
  int32_t height;
};

void clamp_neg_to_zero_isize(ISize* isize)
{
  if (isize->width < 0)
    isize->width = 0;
  if (isize->height < 0)
    isize->height = 0;
}

bool equals_isize(const ISize* isize, int32_t w, int32_t h)
{
  return isize->width == w && isize->height == h;
}

int32_t get_height(const ISize* isize)
{
  return isize->height;
}

int32_t get_width(const ISize* isize)
{
  return isize->width;
}

bool is_empty_isize(const ISize* isize)
{
  return isize->width <= 0 || isize->height <= 0;
}

bool is_zero_isize(const ISize* isize)
{
  return isize->width == 0 && isize->height == 0;
}

ISize make_isize(int32_t w, int32_t h)
{
  ISize s;
  s.width = w;
  s.height = h;
  return s;
}

void set_empty_isize(ISize* isize)
{
  isize->width = isize->height = 0;
}

void set_isize(ISize* isize, int32_t w, int32_t h)
{
  isize->width = w;
  isize->height = h;
}
