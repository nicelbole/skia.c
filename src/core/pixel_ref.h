struct PixelRef
{
  const ImageInfo info;
};

PixelRef* create_pixel_ref(ImageInfo&);
void delete_pixel_ref();

ImageInfo& get_info_pixel_ref(PixelRef* pixel_ref)
{
  return pixel_ref->info;
}
