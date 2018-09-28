#include "SimpleVAO.h"
#include <iostream>
namespace ngl
{
  SimpleVAO::~SimpleVAO()
  {
    removeVAO();
  }

  void SimpleVAO::draw() const
  {
    if(m_allocated == false)
    {
      msg->addWarning("Trying to draw an unallocated VOA");
    }
    if(m_bound == false)
    {
      msg->addWarning("Warning trying to draw an unbound VOA");
    }
    glDrawArrays(m_mode, 0, static_cast<GLsizei>(m_indicesCount));
  }

  void SimpleVAO::removeVAO()
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

  void SimpleVAO::setData(const VertexData &_data)
  {
    if(m_bound == false)
    {
      msg->addWarning("trying to set VOA data when unbound");
    }
    if( m_allocated ==true)
    {
        glDeleteBuffers(1,&m_buffer);
    }
    std::cout<<"setting data "<<_data.m_size<<'\n';
    std::unique_ptr<float [] > d=std::make_unique<float []>(_data.m_size);
    std::memcpy(d.get(),&_data.m_data,_data.m_size);
    for(size_t i=0; i<_data.m_size; ++i)
      std::cout<<i<<" Data "<<d[i]<<'\n';
    glGenBuffers(1, &m_buffer);
    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>( _data.m_size), &_data.m_data, _data.m_mode);
    m_allocated=true;
  }

  Real * SimpleVAO::mapBuffer(unsigned int _index, GLenum _accessMode)
  {
    Real *ptr=nullptr;
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    ptr = static_cast<Real *>(glMapBuffer(GL_ARRAY_BUFFER, _accessMode));
    // modern GL allows this but not on mac!
    //ptr = static_cast<Real *>(glMapNamedBuffer(m_id, _accessMode));

    return ptr;
  }

}
