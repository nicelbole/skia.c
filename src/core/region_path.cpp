bool get_boundary_path_region(const Region* region, Path* path)
{
  if (is_empty_region(region))
    return false;

  const IRect& bounds = region->bounds;

  if (is_rect_region(region))
  {
    Rect r;
    set_rect(r, bounds);
    add_rect_path(r);
    return true;
  }

  Region::Iterator iter = ;//TODO
  
}
