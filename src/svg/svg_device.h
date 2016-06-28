struct BaseDevice{
};

struct SVGDevice {
};

BaseDevice create_svg_device(const ISize&, XMLWrite*);
void draw_paint_svg_device(const Draw&, const Paint&);
ImageInfo image_info(SVGDevice*);
