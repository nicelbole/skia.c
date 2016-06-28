void draw_rrect_bitmap_device(BitmapDevice* device, const Draw& draw, RRect& rect, Paint& paint)
{
#ifdef SK_IGNORE_BLURRED_RRECT_OPT
  Path path;
  add_rrect_path(path, rrect);
  draw_path_device(device, draw, path, paint, nullptr, true);
#else
  draw_rrect_draw(draw, rrect, paint);
#endif
}

static bool valid_for_bitmap_device(const ImageInfo& info,
				    AlphaType* newAlphaType)
{
  if (get_width_image_info(info) < 0 || get_height_image_info(info) < 0)
    return false;

  if (kUnknown_SkColorType == info.colorType())
  {
    if (newAlphaType)
      *newAlphaType = kUnknown_SkAlphaType;
    return true;
  }

  switch (info.alphaType())
  {
  case kPremul_SkAlphaType:
  case kOpaque_SkAlphaType:
    break;
  default:
    return false;
  }

  AlphaType canonicalAlphaType = info.alphaType();

  switch (info.colorType())
  {
  case kAlpha_8_SkColorType:
    break;
  case kRGB_565_SkColorType:
    canonicalAlphaType = kOpaque_SkAlphaType;
    break;
  case kN32_SkColorType:
    break;
  case kRGBA_F16_SkColorType:
    break;
  default:
    return false;
  }

  if (newAlphaType)
    *newAlphaType = canonicalAlphaType;
  return true;
}
