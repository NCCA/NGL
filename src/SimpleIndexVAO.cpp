#include "SimpleIndexVAO.h"
#include <iostream>
namespace ngl
{
  void SimpleIndexVAO::draw() const
  {
    if(m_allocated == false)
    {
      std::cerr<<"Warning trying to draw an unallocated VOA\n";
    }
    if(m_bound == false)
    {
      std::cerr<<"Warning trying to draw an unbound VOA\n";
    }
    glDrawElements(m_mode,static_cast<GLsizei>(m_indicesCount),m_indexType,static_cast<GLvoid *>(nullptr));
  }

  void SimpleIndexVAO::removeVAO()
  {
    if(m_bound == true)
    {
      unbind();
    }
    if( m_allocated ==true)
    {
        glDeleteBuffers(1,&m_buffer);
    }
    glDeleteVertexArrays(1,&m_id);
    m_allocated=false;
    }


  //void SimpleIndexVAO::setData(size_t _size, const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData, GLenum _indexType, GLenum _mode  )
  void SimpleIndexVAO::setData(const AbstractVAO::VertexData &_data)
  {
    const VertexData &data = static_cast<const VertexData &>(_data);
    if(m_bound == false)
    {
    std::cerr<<"trying to set VOA data when unbound\n";
    }
    GLuint vboID;
    glGenBuffers(1, &vboID);

    GLuint iboID;
    glGenBuffers(1, &iboID);

    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.m_size), &data.m_data, data.m_mode);
    // we need to determine the size of the data type before we set it
    // in default to a ushort
    int size=sizeof(GLushort);
    switch(data.m_indexType)
    {
      case GL_UNSIGNED_INT   : size=sizeof(GLuint);   break;
      case GL_UNSIGNED_SHORT : size=sizeof(GLushort); break;
      case GL_UNSIGNED_BYTE  : size=sizeof(GLubyte);  break;
      default : std::cerr<<"wrong data type send for index value\n"; break;
    }
    // now for the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.m_indexSize * static_cast<GLsizeiptr>(size), const_cast<GLvoid *>(data.m_indexData),data.m_mode);

    m_allocated=true;
    m_indexType=data.m_indexType;
  }

}
