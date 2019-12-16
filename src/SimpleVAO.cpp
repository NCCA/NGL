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

#ifdef PYTHONBUILD

    void SimpleVAO::setData(size_t _size, const std::vector<float> &_data)
    {
        if(m_bound == false)
        {
            msg->addWarning("trying to set VOA data when unbound");
        }
        if( m_allocated ==true)
        {
            glDeleteBuffers(1,&m_buffer);
        }
        glGenBuffers(1, &m_buffer);
        // now we will bind an array buffer to the first one and load the data for the verts
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>( _size), &_data[0],GL_STATIC_DRAW);
        m_allocated=true;
    }


  void SimpleVAO::setData(size_t _size, const std::vector<Vec3> &_data)
  {
    if(m_bound == false)
    {
      msg->addWarning("trying to set VOA data when unbound");
    }
    if( m_allocated ==true)
    {
        glDeleteBuffers(1,&m_buffer);
    }
    glGenBuffers(1, &m_buffer);
    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>( _size), &_data[0].m_x,GL_STATIC_DRAW);
    m_allocated=true;
  }



#endif

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
