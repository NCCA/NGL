#include "AbstractVAO.h"
namespace ngl
{
AbstractVAO::AbstractVAO(GLenum _mode) : m_mode{_mode}
{
  // first we create a vertex array Object
  glGenVertexArrays(1, &m_id);
}

GLenum AbstractVAO::getMode() const
{
  return m_mode;
}

void AbstractVAO::setMode(const GLenum &_mode)
{
  m_mode = _mode;
}

//----------------------------------------------------------------------------------------------------------------------
void AbstractVAO::bind()
{
  glBindVertexArray(m_id);
  m_bound = true;
}
//----------    ------------------------------------------------------------------------------------------------------------
void AbstractVAO::unbind()
{
  glBindVertexArray(0);
  m_bound = false;
}

void AbstractVAO::setVertexAttributePointer(GLuint _id, GLint _size, GLenum _type, GLsizei _stride, unsigned int _dataOffset, bool _normalise) const noexcept
{
  if(!m_bound)
  {
    NGLMessage::addWarning("Warning trying to set attribute on Unbound VOA");
  }
  // set and enable the generic vertex attribute
  glVertexAttribPointer(_id, _size, _type, _normalise, _stride, static_cast< Real * >(nullptr) + _dataOffset); 
  glEnableVertexAttribArray(_id);
}

void AbstractVAO::unmapBuffer() const
{
  glUnmapBuffer(GL_ARRAY_BUFFER); // unmap it after use
}

} // namespace ngl
