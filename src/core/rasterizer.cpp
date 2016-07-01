bool rasterize_rasterizer(const Rasterizer* rasterizer, const Path& fill_path, const Matrix& matrix,
  const IRect* clip_bounds, MaskFilter* filter, Mask* mask, Mask::CreateMode mode)
{
  IRect storage;

  if (clip_bounds && filter && mode != Mask::CreateMode::JustRenderImage)
  {
    IPoint margin;
    Mask src_m, dst_m;

    src_m.format = Mask::Format::A8;
    set_irect(src_m.bounds, 0, 0, 1, 1);
    if (!filter_mask_mask_filter(filter, &dst_m, src_m, matrix, &margin))
      return false;
    storage = make_outset_irect(clip_bounds, margin.x, margin.y);
    clip_bounds = &storage;
  }

    return on_rasterize_rasterizer(rasterizer, fill_path, matrix, clip_bounds, mask, mode);
}
