#include "svg_canvas.h"
#include "svg_device.h"

Canvas* create_svg_canvas(const Rect& bounds, XMLWriter* writer)
{
  ISize size = size_ round_out_rect(bounds);
  //TODO
  
  return create_canvas(device);
}
