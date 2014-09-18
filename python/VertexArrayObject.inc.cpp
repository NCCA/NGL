namespace ngl
{

void (VertexArrayObject::*drawN)() const = &VertexArrayObject::draw;
void (VertexArrayObject::*drawE)(GLenum ) const = &VertexArrayObject::draw;


} // end namespace
