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
#ifndef BBOX_H_
#define BBOX_H_
/// @file BBox.h
/// @brief a simple bounding box class
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec3.h"
#include "Vec4.h"
#include "AbstractVAO.h"
#include <memory>
#include <array>


namespace ngl
{


///  @class BBox  "include/BBox.h"
///  @brief Simple Bounding box class used in various parts of ngl and other example programs
///  @author Jonathan Macey
///  @version 4.1
///  @date Last Revision updated to use Vec3 to fit with new shader attribute pipeline


class NGL_DLLEXPORT BBox
{
public :

  
  /// @brief Bounding Box ctor using a Center and the 3 dimensions of the BBox
  ///  @param[in]  _center the center of the BBox.
  ///  @param[in]  _width the width of the BBox (== X coord).
  ///  @param[in]  _height the height of the BBox (== Y coord).
  ///  @param[in]  _depth the Depth of the BBox (== Z coord).
  
  BBox(const Vec3 &_center, Real _width,Real _height, Real _depth,bool _noGL=false) noexcept;

  
  /// @brief ctor using +/- x,y,z dimensions
  /// @param[in]  _minX the x position of the min x extent
  /// @param[in]  _maxX the x position of the max x extent
  /// @param[in]  _minY the y position of the min y extent
  /// @param[in]  _maxY the y position of the max y extent
  /// @param[in]  _minZ the z position of the min z extent
  /// @param[in]  _maxZ the z position of the max z extent
  
  BBox(Real _minX,Real _maxX,Real _minY,Real _maxY,Real _minZ,Real _maxZ,bool _noGL=false) noexcept;
  
  /// @brief Default constructor will create a BBox centered at point 0,0,0
  /// With Unit length width and height (== 1)
  
  BBox()=default;
  BBox(bool _noGL) : m_noGL{_noGL}{}

  /// @brief copy ctor
  /// @param[in] _b the bbox to copy
  
  BBox(const BBox &_b) noexcept;
  BBox& operator=(const BBox &_other);
  
  /// @brief Draw Method draws the BBox using OpenGL
  
  void draw() const noexcept;
  
  /// @brief reset the draw mode for the BBox
  /// @param[in] _mode the mode to draw
  
  void setDrawMode(GLenum _mode)noexcept;
  /// @brief dtor no dynamic memory so empty
  ~BBox()noexcept;   
   /// @brief the min x value of the bbox
   Real minX()const noexcept { return m_minX;}   
   /// @brief the max x value of the bbox
   Real maxX()const noexcept{ return m_maxX;}
   /// @brief the min y value of the bbox
   Real minY()const noexcept{ return m_minY;}
   /// @brief the max y value of the bbox
   Real maxY()const noexcept{ return m_maxY;}   
   /// @brief the min z value of the bbox
   Real minZ()const noexcept{ return m_minZ;}
   /// @brief the max z value of the bbox
   Real maxZ()const noexcept{ return m_maxZ;}
   /// @brief This is the center of the BBox stored for caluculations in other classes s
   Vec3 center()const noexcept{ return m_center; }
   /// @brief accessor for the width of the BBox
   /// @returns the width of the BBox
   Real width()const noexcept{ return m_width; }
   /// @brief set the width
   /// @param[in] _w the width to set will re-calculate bbox and VAO
   /// @param[in] _recalc flag to indicate if we need to recalc the vao defauts to true
   void width(Real _w, bool _recalc=true) noexcept;
   /// @brief Height of the BBox
   Real height()const noexcept{return m_height;}
   
   /// @brief set the height
   /// @param[in] _h the height to set will re-calculate bbox and VAO
   /// @param[in] _recalc flag to indicate if we need to recalc the vao defauts to true
   void height(Real _h, bool _recalc=true) noexcept;
   /// @brief Depth of the BBox
   Real depth()const noexcept{return m_depth;}
   /// @brief set the depth
   /// @param[in] _d the depth to set will re-calculate bbox and VAO
   /// @param[in] _recalc flag to indicate if we need to recalc the vao defauts to true
   void depth(Real _d, bool _recalc=true) noexcept;
   /// @brief the array of normals for the  BBox
   std::array<Vec3,6>  getNormalArray()noexcept{return m_norm;}   
   /// @brief the array of verts for the  BBox
  std::array<Vec3,8>  getVertexArray()noexcept{return m_vert;}
   /// @brief set the center of the BBox and re-calculate the extents
   /// @param _center the new center of the BBox
   void setCenter(const Vec3 &_center, bool _recalc=true) noexcept;
   /// @brief recalculate the bbox values once things have been changed
   /// this will also re-do the VAO
   void recalculate() noexcept;
   void setExtents(Real _minX,Real _maxX,Real _minY,Real _maxY,Real _minZ,Real _maxZ) noexcept;

protected :

  
  /// @brief method used to set the vao
  
  void setVAO();
  
  /// @brief Contains the   8 vertices for the BBox aranged from v[0] = Left-top-Max Z
  ///and then rotating clock wise for the top of the BBox
  ///The Bottom Square is a mirror of the 1st verts with the Y value changed
  ///See constructor code for caluculations
  
  std::array<Vec3,8> m_vert;
  /// @brief the min x value of the bbox
  Real m_minX=-1.0f;
  /// @brief the max x value of the bbox
  Real m_maxX=1.0f;
  /// @brief the min y value of the bbox
  Real m_minY=-1.0f;
  /// @brief the max y value of the bbox
  Real m_maxY=1.0f;
  /// @brief the min z value of the bbox
  Real m_minZ=-1.0f;
  /// @brief the max z value of the bbox
  Real m_maxZ=1.0f; 
  /// @brief This is the center of the BBox stored for caluculations in other classes s
  Vec3 m_center={0.0f,0.0f,0.0f};
  /// @brief used to store the 6 Normal faces for the BBox used for calculating BBox  collisions if needed
  std::array<Vec3,6> m_norm;
  /// @brief Width of the BBox
  Real m_width=2.0f;
  /// @brief Height of the BBox
  Real m_height=2.0f;
  /// @brief Depth of the BBox
  Real m_depth=2.0f;
  /// @brief a pointer to the VAO buffer used for drawing the bbox
  std::unique_ptr< AbstractVAO >m_vao;
  /// @brief sets the draw mode for the BBox Faces,  set to GL_LINE for
  ///  line faces and GL_FILL for filled
  GLuint m_drawMode=GL_LINE;
  /// @brief flag to indicate this is a data BBox not a drawing one
  bool m_noGL=false;

}; // end class
} // end namespace

#endif


