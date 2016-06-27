struct Edge
{
  enum Type {
    Line, Quad, Cubic
  };

  Edge* next;
  Edge* prev;
}
