/*
  Copyright (C) 2016 Jon Macey

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
#ifndef ABSTRACTVAO_H_
#define ABSTRACTVAO_H_

#include "Types.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class AbstractVAO "include/AbstractVAO.h"
/// @brief base class for all VAO from the VAOFactory
/// @author Jonathan Macey
/// @version 1.0
/// @date 6/4/16
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT AbstractVAO
{
  public :
    void bind();
    void unbind();
    virtual void draw()const =0;
    virtual ~AbstractVAO()=default;
    virtual void removeVAO()=0;
    void setVertexAttributePointer(GLuint _id, GLint _size, GLenum _type, GLsizei _stride, unsigned int _dataOffset, bool _normalise=false );
    void setNumIndices(GLsizei _s){m_indicesCount=_s;}
  protected :
    AbstractVAO(GLenum _mode=GL_TRIANGLES) ;
    GLenum m_mode=GL_TRIANGLES;
    GLuint m_id=0;
    bool m_bound=false;
    bool m_allocated=false;
    GLsizei m_indicesCount=0;
};


} // end namespace

#endif
