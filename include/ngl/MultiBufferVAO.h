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
    static std::unique_ptr<AbstractVAO> create(GLenum _mode=GL_TRIANGLES) { return std::unique_ptr<AbstractVAO>(new MultiBufferVAO(_mode)); }
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw the VAO using glDrawArrays
    //----------------------------------------------------------------------------------------------------------------------
    virtual void draw() const override final;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor don't do anything as the remove clears things
    //----------------------------------------------------------------------------------------------------------------------
    virtual ~MultiBufferVAO();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief remove the VAO and buffers created
    //----------------------------------------------------------------------------------------------------------------------
    virtual void removeVAO() override final;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief, this method sets the data for the VAO if data has already been set it will remove the existing data
    /// and then re-set with the new data.
    //----------------------------------------------------------------------------------------------------------------------
    virtual void setData(const VertexData &_data) override final;
    void setData(size_t _index, const VertexData &_data );
    #ifdef PYTHONBUILD
        void setData(size_t _size, const std::vector<float>  &_data);
        void setData(size_t _size, const std::vector<Vec3>  &_data);
        void setData(size_t _size, const std::vector<Vec4>  &_data);
        void setData(size_t _index,size_t _size, const std::vector<float>  &_data);
        void setData(size_t _index,size_t _size, const std::vector<Vec3>  &_data);
        void setData(size_t _index,size_t _size, const std::vector<Vec4>  &_data);
    #endif

    //`----------------------------------------------------------------------------------------------------------------------
    /// @brief return the id of the buffer, if there is only 1 buffer just return this
    /// if we have the more than one buffer the sub class manages the id's
    /// @param _buffer index (default to 0 for single buffer VAO's)
    //----------------------------------------------------------------------------------------------------------------------
    virtual GLuint getBufferID(unsigned int _id) const override final;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief grab a raw pointer to the data
    /// @param _index the index to the buffer (0) default for simple
    /// @param _mode the access more
    //----------------------------------------------------------------------------------------------------------------------
    Real * mapBuffer(unsigned int _index=0, GLenum _accessMode=GL_READ_WRITE) override final;

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
