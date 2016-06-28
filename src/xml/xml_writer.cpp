#include "XMLWriter.h"

void start_element_xml_writer(XMLWriter* writer, const char name[])
{
  start_element_len(writer, name, strlen(name));
}

void start_element_xml_writer(XMLWriter* writer, const char elem[], size_t length)
{
  on_start_element_len_xml_writer(writer, elem, length);
}

void on_start_element_len_xml_stream_writer(XMLWriter* writer, const char name[]. size_t length)
{
  int level = writer->elems;//TODO
}
