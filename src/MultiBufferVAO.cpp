  #include "MultiBufferVAO.h"
#include <iostream>
#include <NGLassert.h>

namespace ngl
{
  MultiBufferVAO::~MultiBufferVAO()
  {
    removeVAO();
  }

  void MultiBufferVAO::draw() const
  {
    if(!m_allocated)
    {
      NGLMessage::addWarning("trying to draw an unallocated VOA");
    }
    if(!m_bound)
    {
      NGLMessage::addWarning("trying to draw an unbound VOA");
    }
    glDrawArrays(m_mode, 0, static_cast<GLsizei>(m_indicesCount));
  }

  void MultiBufferVAO::removeVAO() 
  {
    if(m_bound)
    {
      unbind();
    }
    if(m_allocated)
    {
      for(auto b : m_vboIDs)
      {
        glDeleteBuffers(1,&b);
      }
      glDeleteVertexArrays(1,&m_id);
      m_allocated=false;
    }
  }
  void MultiBufferVAO::setData(const VertexData &_data)
  {
    if(!m_bound)
    {
      NGLMessage::addWarning("trying to set VOA data when unbound");
    }

    GLuint vboID;
    glGenBuffers(1, &vboID);
    m_vboIDs.push_back(vboID);
    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_data.m_size), &_data.m_data, _data.m_mode);
    m_allocated=true;

  }

  void MultiBufferVAO::setData(size_t _index, const VertexData &_data )
  {
    if(!m_bound)
    {
      NGLMessage::addWarning("trying to set VOA data when unbound");
    }
    if(_index >= m_vboIDs.size())
    {
      NGLMessage::addError("Trying to set Buffer data at wrong Index");
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[_index]);
    glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_data.m_size), &_data.m_data, _data.m_mode);
    m_allocated=true;
  }



#ifdef PYTHONBUILD

  void MultiBufferVAO::setData(size_t _size, const std::vector<float>  &_data)
  {
    if(m_bound == false)
    {
      NGLMessage::addWarning("trying to set VOA data when unbound");
    }

    GLuint vboID;
    glGenBuffers(1, &vboID);
    m_vboIDs.push_back(vboID);
    // now we will bind an array buffer to the first one and load the data for the verts
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_size), &_data[0], GL_STATIC_DRAW);
    m_allocated=true;

  }

  void MultiBufferVAO::setData(size_t _index,size_t _size, const std::vector<float>  &_data)
  {
    if(m_bound == false)
    {
      NGLMessage::addWarning("trying to set VOA data when unbound");
    }

    if(_index >m_vboIDs.size())
    {
      NGLMessage::addError("Trying to set Buffer data at wrong Index");
    }


    glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[_index]);
    glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_size), &_data[0], GL_STATIC_DRAW);
    m_allocated=true;

  }

  void MultiBufferVAO::setData(size_t _size, const std::vector<Vec3>  &_data)
  {
      if(m_bound == false)
      {
          NGLMessage::addWarning("trying to set VOA data when unbound");
      }

      GLuint vboID;
      glGenBuffers(1, &vboID);
      m_vboIDs.push_back(vboID);
      // now we will bind an array buffer to the first one and load the data for the verts
      glBindBuffer(GL_ARRAY_BUFFER, vboID);
      glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_size), &_data[0].m_x, GL_STATIC_DRAW);
      m_allocated=true;

  }

  void MultiBufferVAO::setData(size_t _size, const std::vector<Vec4>  &_data)
  {
      if(m_bound == false)
      {
          NGLMessage::addWarning("trying to set VOA data when unbound");
      }

      GLuint vboID;
      glGenBuffers(1, &vboID);
      m_vboIDs.push_back(vboID);
      // now we will bind an array buffer to the first one and load the data for the verts
      glBindBuffer(GL_ARRAY_BUFFER, vboID);
      glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_size), &_data[0].m_x, GL_STATIC_DRAW);
      m_allocated=true;

  }


  void MultiBufferVAO::setData(size_t _index,size_t _size, const std::vector<Vec3>  &_data)
  {
      if(m_bound == false)
      {
          NGLMessage::addWarning("trying to set VOA data when unbound");
      }
      if(_index >m_vboIDs.size())
      {
        NGLMessage::addError("Trying to set Buffer data at wrong Index");
      }

      // now we will bind an array buffer to the first one and load the data for the verts
      glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[_index]);
      glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_size), &_data[0].m_x, GL_STATIC_DRAW);
      m_allocated=true;

  }


  void MultiBufferVAO::setData(size_t _index,size_t _size, const std::vector<Vec4>  &_data)
  {
      if(m_bound == false)
      {
          NGLMessage::addWarning("trying to set VOA data when unbound");
      }
      if(_index >m_vboIDs.size())
      {
        NGLMessage::addError("Trying to set Buffer data at wrong Index");
      }

      // now we will bind an array buffer to the first one and load the data for the verts
      glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[_index]);
      glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(_size), &_data[0].m_x, GL_STATIC_DRAW);
      m_allocated=true;

  }




#endif
  GLuint MultiBufferVAO::getBufferID(unsigned int _id ) const
  {
    NGL_ASSERT(_id<m_vboIDs.size())
    return m_vboIDs[_id];
  }

  Real *MultiBufferVAO::mapBuffer(unsigned int _index, GLenum _accessMode)
  {
    Real *ptr=nullptr;
    if(_index<m_vboIDs.size())
    {
      bind();
      glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[_index]);
      ptr = static_cast<Real *>(glMapBuffer(GL_ARRAY_BUFFER, _accessMode));
    }
    return ptr;
  }
}
