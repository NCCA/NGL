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
#ifndef SIMPLEVAO_H_
#define SIMPLEVAO_H_

#include "AbstractVAO.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class SimpleVAO "include/SimpleVAO.h"
/// @brief Simple non index vao using one buffer
/// @author Jonathan Macey
/// @version 1.0
/// @date 6/4/16
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT SimpleVAO : public AbstractVAO
{
  public :

    static AbstractVAO *create(GLenum _mode=GL_TRIANGLES) { return new SimpleVAO(_mode); }

    virtual void draw() const;
    virtual ~SimpleVAO()=default;
    virtual void removeVAO();
    void setData(size_t _size,const GLfloat &_data,GLenum _mode=GL_STATIC_DRAW);

  protected :
    SimpleVAO(GLenum _mode)  : AbstractVAO(_mode)
    {

    }

  private :
    GLuint m_buffer=0;

};


} // end namespace

#endif
