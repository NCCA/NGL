/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "VertexArrayObject.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
/// @file VertexArrayObject.cpp
/// @brief implementation files for VertexArrayObject class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
VertexArrayObject::VertexArrayObject(GLenum _mode)
{
  m_allocated=false;
  // first we create a vertex array Object
  glGenVertexArrays(1, &m_id);
  m_bound=false;
  m_drawMode=_mode;
  m_indicesCount=0;
  m_indexed=false;
  m_indexType = GL_UNSIGNED_BYTE;
}

//----------------------------------------------------------------------------------------------------------------------
void VertexArrayObject::bind()
{
  glBindVertexArray(m_id);
  m_bound=true;
}
//----------------------------------------------------------------------------------------------------------------------
void VertexArrayObject::unbind()
{
  glBindVertexArray(0);
  m_bound=false;
}
//----------------------------------------------------------------------------------------------------------------------
void VertexArrayObject::removeVOA()
{
  if(m_bound == true)
  {
    unbind();
  }
  if( m_allocated ==true)
  {
    size_t size=m_vboIDs.size();
    for(size_t i=0; i<size; ++i)
    {
      glDeleteBuffers(1,&m_vboIDs[i]);
    }
    glDeleteVertexArrays(1,&m_id);
    m_allocated=false;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void VertexArrayObject::setData(unsigned int _size,const GLfloat &_data,GLenum _mode)
{
  if(m_bound == false)
  {
    std::cerr<<"trying to set VOA data when unbound\n";
  }
  GLuint vboID;
  glGenBuffers(1, &vboID);
  m_vboIDs.push_back(vboID);
  // now we will bind an array buffer to the first one and load the data for the verts
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, _size, &_data, _mode);
  m_allocated=true;

}


void VertexArrayObject::setIndexedData(unsigned int _size,const GLfloat &_data, unsigned int _indexSize, const GLvoid *_indexData,GLenum _indexType,GLenum _mode  )
{

  if(m_bound == false)
  {
  std::cerr<<"trying to set VOA data when unbound\n";
  }
  GLuint vboID;
  glGenBuffers(1, &vboID);
  m_vboIDs.push_back(vboID);

  GLuint iboID;
  glGenBuffers(1, &iboID);
  m_iboID = iboID;

  //glEnableVertexAttribArray(0);
  // now we will bind an array buffer to the first one and load the data for the verts
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, _size, &_data, _mode);
  // we need to determine the size of the data type before we set it
  // in default to a ushort
  int size=sizeof(GLushort);
  switch(_indexType)
  {
    case GL_UNSIGNED_INT   : size=sizeof(GLuint);   break;
    case GL_UNSIGNED_SHORT : size=sizeof(GLushort); break;
    case GL_UNSIGNED_BYTE  : size=sizeof(GLubyte);  break;
    default : std::cerr<<"wrong data type send for index value\n"; break;
  }
  // now for the indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexSize * size, _indexData, _mode);

  m_allocated=true;
  m_indexed=true;
  m_indexType=_indexType;
}


void VertexArrayObject::setRawIndexedData(unsigned int _size, const GLvoid *_data, unsigned int _indexSize,const GLvoid *_indexData, GLenum _indexType,GLenum _mode)
{

  if(m_bound == false)
  {
  std::cerr<<"trying to set VOA data when unbound\n";
  }
  GLuint vboID;
  glGenBuffers(1, &vboID);
  m_vboIDs.push_back(vboID);

  GLuint iboID;
  glGenBuffers(1, &iboID);
  m_iboID = iboID;

  //glEnableVertexAttribArray(0);
  // now we will bind an array buffer to the first one and load the data for the verts
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, _size, _data, _mode);
  // we need to determine the size of the data type before we set it
  // in default to a ushort
  int size=sizeof(GLushort);
  switch(_indexType)
  {
    case GL_UNSIGNED_INT   : size=sizeof(GLuint);   break;
    case GL_UNSIGNED_SHORT : size=sizeof(GLushort); break;
    case GL_UNSIGNED_BYTE  : size=sizeof(GLubyte);  break;
    default : std::cerr<<"wrong data type sent for index value\n"; break;
  }
  // now for the indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexSize*size , _indexData, _mode);

  m_allocated=true;
  m_indexed=true;
  m_indexType=_indexType;
}




void VertexArrayObject::updateIndexedData( unsigned int _size, const GLfloat &_data,GLenum _mode )
{

  if(m_bound == false)
  {
    std::cerr<<"trying to set VOA data when unbound\n";
  }

  if(m_allocated && m_indexed)
  {
    glBindBuffer(GL_ARRAY_BUFFER, getVBOid(0));
    glBufferData(GL_ARRAY_BUFFER, _size, &_data, _mode);
  }
}


void VertexArrayObject::updateIndexedData(GLuint vboidx, unsigned int _size,const GLfloat &_data,GLenum _mode)
{
    if(m_bound == false)
    {
      std::cerr<<"trying to set VOA data when unbound\n";
    }

    if(m_allocated && m_indexed)
    {
      glBindBuffer(GL_ARRAY_BUFFER, getVBOid(vboidx));
      glBufferData(GL_ARRAY_BUFFER, _size, &_data, _mode);
    }
}



void VertexArrayObject::updateData( unsigned int _size, const GLfloat &_data,GLenum _mode )
{

  if(m_bound == false)
  {
    std::cerr<<"trying to set VOA data when unbound\n";
  }

  if(m_allocated )
  {
    glBindBuffer(GL_ARRAY_BUFFER, getVBOid(0));
    glBufferData(GL_ARRAY_BUFFER, _size, &_data, _mode);
  }
}


void VertexArrayObject::updateData(GLuint vboidx, unsigned int _size,const GLfloat &_data,GLenum _mode)
{
    if(m_bound == false)
    {
      std::cerr<<"trying to set VOA data when unbound\n";
    }

    if(m_allocated )
    {
      glBindBuffer(GL_ARRAY_BUFFER, getVBOid(vboidx));
      glBufferData(GL_ARRAY_BUFFER, _size, &_data, _mode);
    }
}



GLuint VertexArrayObject::getVBOid(unsigned int _index)
{
  GLuint id=0;
  /// _index >=0 && picked up by g++4.3 so removed from below
  if(_index<m_vboIDs.size())
  {
    id=m_vboIDs[_index];
  }
  return id;
}

//----------------------------------------------------------------------------------------------------------------------
void VertexArrayObject::setVertexAttributePointer(GLuint _id, GLint _size, GLenum _type, GLsizei _stride, unsigned int _dataOffset, bool _normalise )
{
  if(m_bound !=true)
  {
    std::cerr<<"Warning trying to set attribute on Unbound VOA\n";
  }

  glVertexAttribPointer(_id,_size,_type,_normalise,_stride,((Real *)NULL + (_dataOffset)));
  glEnableVertexAttribArray(_id);
}


void VertexArrayObject::setVertexAttributeIPointer( GLuint _id,  GLint _size, GLenum _type, GLsizei _stride, unsigned int _dataOffset )
{
  if(m_bound !=true)
  {
    std::cerr<<"Warning trying to set attribute on Unbound VOA\n";
  }

  glVertexAttribIPointer(_id,_size,_type,_stride,((Real *)NULL + (_dataOffset)));
  glEnableVertexAttribArray(_id);
}



//----------------------------------------------------------------------------------------------------------------------
void VertexArrayObject::draw() const
{
  if(m_allocated == false)
  {
    std::cerr<<"Warning trying to draw an unallocated VOA\n";
  }
  if(m_bound == false)
  {
    std::cerr<<"Warning trying to draw an unbound VOA\n";
  }

  if(m_indexed == false)
  {
    glDrawArrays(m_drawMode, 0, m_indicesCount);	// draw first object
  }
  else
  {
    glDrawElements(m_drawMode,m_indicesCount,m_indexType,(GLvoid*)((char*)NULL));
  }
}


void VertexArrayObject::draw(unsigned int _startIndex, unsigned int _numVerts, GLenum _mode  ) const
{
  if(m_allocated == false)
  {
    std::cerr<<"Warning trying to draw an unallocated VOA\n";
  }
  if(m_bound == false)
  {
    std::cerr<<"Warning trying to draw an unbound VOA\n";
  }
  glDrawArrays(_mode, _startIndex, _numVerts);	// draw first object
}

void VertexArrayObject::draw(GLenum _mode) const
{
  if(m_allocated == false)
  {
    std::cerr<<"Warning trying to draw an unallocated VOA\n";
  }
  if(m_bound == false)
  {
    std::cerr<<"Warning trying to draw an unbound VOA\n";
  }

  if(m_indexed == false)
  {
    glDrawArrays(_mode, 0, m_indicesCount);	// draw first object
  }
  else
  {
    glDrawElements(_mode,m_indicesCount,m_indexType,(GLvoid*)((char*)NULL));
  }
}

void VertexArrayObject::drawInstanced(unsigned int _n) const
{
  if(m_allocated == false)
  {
    std::cerr<<"Warning trying to draw an unallocated VOA\n";
  }
  if(m_bound == false)
  {
    std::cerr<<"Warning trying to draw an unbound VOA\n";
  }

  if(m_indexed == false)
  {
    glDrawArraysInstanced(m_drawMode, 0, m_indicesCount,_n);	// draw first object
  }
  else
  {

    glDrawElementsInstanced(m_drawMode,m_indicesCount,m_indexType,(GLvoid*)((char*)NULL),_n);
  }
}

//----------------------------------------------------------------------------------------------------------------------
Real *VertexArrayObject::getDataPointer(unsigned int _vbo, GLenum _accessMode)
{
  Real *ptr=0;
//  code was this but g++ 4.2 gives warning about it always being true
// removed the first test as change to uint so should be ok
//  if(_vbo >=0 && _vbo<m_vboIDs.size())
//
  if(_vbo<m_vboIDs.size())
  {
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[_vbo]);
    ptr = (Real*)glMapBuffer(GL_ARRAY_BUFFER, _accessMode);
  }
  return ptr;
}

void VertexArrayObject::freeDataPointer()
{
  glUnmapBuffer(GL_ARRAY_BUFFER); // unmap it after use
}

int VertexArrayObject::getSize() const
{
  if(m_bound == false)
  {
    std::cerr<<"Warning trying to access an unbound VOA\n";
  }

  int size;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  return size;
}

} // end namspace ngl



