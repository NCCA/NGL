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
#ifndef MULTIBUFFERVAO_H_
#define MULTIBUFFERVAO_H_

#include "AbstractVAO.h"
#include <vector>
namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class MultiBufferVAO "include/MultiBufferVAO.h"
/// @brief Simple non index vao using multiple buffers
/// see https://github.com/NCCA/VertexArrayObject/tree/master/MultiBufferVAOFactory
/// for examples of use
/// @author Jonathan Macey
/// @version 1.0
/// @date 6/4/16
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT MultiBufferVAO : public AbstractVAO
{
  public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief creator method for the factory
    /// @param _mode the mode to draw with.
    /// @returns a new AbstractVAO * object
    //----------------------------------------------------------------------------------------------------------------------
    static AbstractVAO *create(GLenum _mode=GL_TRIANGLES) { return new MultiBufferVAO(_mode); }
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the VAO using glDrawArrays
    //----------------------------------------------------------------------------------------------------------------------
    virtual void draw() const;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor don't do anything as the remove clears things
    //----------------------------------------------------------------------------------------------------------------------
    virtual ~MultiBufferVAO()=default;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief remove the VAO and buffers created
    //----------------------------------------------------------------------------------------------------------------------
    virtual void removeVAO();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief, this method sets the data for the VAO if data has already been set it will remove the existing data
    /// and then re-set with the new data.
    //----------------------------------------------------------------------------------------------------------------------
    void setData(size_t _size,const GLfloat &_data,GLenum _mode=GL_STATIC_DRAW) ;

  protected :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor calles parent ctor to allocate vao;
    //----------------------------------------------------------------------------------------------------------------------
    MultiBufferVAO(GLenum _mode)  : AbstractVAO(_mode)
    {

    }

  private :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the id of the buffers for the VAO
    //----------------------------------------------------------------------------------------------------------------------
    std::vector <GLuint> m_vboIDs;


};


} // end namespace

#endif
