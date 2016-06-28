void draw_paint_svg_device(SVGDevice* device, const Draw& draw, Paint& paint)
{
  AutoElement rect = ;//TODO
  add_rect_attributes();
}

struct AutoElement {
  XMLWriter writer;
  ResourceBucket = resource_bucket;
};

AutoElement* create_auto_element(const char name[], XMLWriter* writer)
{
  AutoElement* aelem = malloc(sizeof(AutoElement));
  aelem->writer = writer;
  aelem->resource_bucket = nullptr;
  start_element_xml_writer(writer, name);
}
