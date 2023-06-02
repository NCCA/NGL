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
#ifndef MAT2_H_
#define MAT2_H_

/// @file Mat2.h
/// @brief a simple 2x2  TX matrix

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec2.h"
#include <array>
#include <ostream>
#ifdef USEGLM
#include <glm/mat2x2.hpp>
#endif

namespace ngl
{


/// @class Mat2 "include/Mat2.h"
/// @brief Mat2 basic 3x3 matrix for certain glsl ops
/// @author Jonathan Macey
/// @version 1.0
/// @date 27/10/11


class NGL_DLLEXPORT Mat2
{
    public:
  
  /// @brief ctor will always create an identity matrix
  
  Mat2() noexcept;
  
  /// @brief ctor passing in value
  
  Mat2(Real _00, Real _01, Real _10, Real _11) noexcept;
  
  /// @brief copy ctor with Real useful for Matrix m=1; for identity or Matrix m=3.5 for uniform scale
  
  Mat2(const Real _m) noexcept;
#ifdef USEGLM
  Mat2(const glm::mat2 &_m);
  glm::mat2 toGLM() const;
#endif

  
  /// @brief clear the matrix to all 0
  
  const Mat2 &null() noexcept;

  
  /// @brief  make the matrix m the identity matrix \n
  /// 1 0 0 0 <BR>
  /// 0 1 0 0 <BR>
  /// 0 0 1 0 <BR>
  /// 0 0 0 1 <BR>
  
  const Mat2 &identity() noexcept;
  
  /// @brief operator for matrix multiplication
  /// @param[in] _m the matrix to multiply the current one by
  /// @returns this*_m
  
  Mat2 operator*(const Mat2 &_m) const noexcept;
  
  /// @brief operator to mult this matrix by value _m
  /// @param[in] _m the matrix to multiplt
  /// @returns a new matrix this*_m
  
  const Mat2 &operator*=(const Mat2 &_m) noexcept;
  
  /// @brief operator to add two matrices together
  /// @param[in] _m the matrix to add
  /// @returns this+_m
  
  Mat2 operator+(const Mat2 &_m) const noexcept;
  
  /// @brief += operator
  /// @param[in] _m the matrix to add
  /// @returns this+m
  
  const Mat2 &operator+=(const Mat2 &_m) noexcept;
  
  /// @brief operator to mult matrix by a scalar
  /// @param[in] _i the scalar to multiply by
  /// @returns this*_i
  
  Mat2 operator*(Real _i) const noexcept;
  
  /// @brief *= operator with a scalar value
  /// @param[in] _i the scalar to multiply by
  /// @returns the matrix*i
  
  const Mat2 &operator*=(Real _i) noexcept;
  
  /// @brief multiply this by a Vec3
  /// @param[in] _v the vector to multiply
  /// @returns Vector M*V
  
  Vec2 operator*(const Vec2 &_v) const noexcept;
  
  ///  @brief method to transpose the matrix
  
  const Mat2 &transpose() noexcept;

  
  /// @brief return this matrix as a 2D rotation matrix by _deg
  /// @param[in] _deg the value to be rotated by in degrees
  
  static Mat2 rotate(Real _deg) noexcept;
  
  /// @brief set the matrix scale values
  /// @param[in] _x the scale value in the _x
  /// @param[in] _y the scale value in the _y
  /// @param[in] _z the scale value in the _z
  
  static Mat2 scale(Real _x, Real _y) noexcept;

  
  /// @brief accesor to the openGL matrix
  /// @returns a pointer to m_openGL[0]
  
  Real *openGL() noexcept
  {
    return &m_openGL[0];
  }

    public:
  

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma pack(push, 1)
  union
  {
    
    /// @brief Mat2 element m_m as a 2x2 array mapped by union to m_nn elements and m_openGL
    
    Real m_m[2][2];
    
    /// @brief  The matrix in m_openGL 4 Real array format usefull for OpenGL fv formats
    /// mapped to m_m[][] elements and m_xx elements
    
    // Real m_openGL[9];
    std::array< Real, 4 > m_openGL = {{1.0f, 0.0f, 0.0f, 1.0f}};
    struct
    {
      /// @brief  individual matrix element maps to m_m[0][0] or m_openGL[0]
      Real m_00;
      /// @brief  individual matrix element maps to m_m[0][1] or m_openGL[1]      
      Real m_01;
      /// @brief  individual matrix element maps to m_m[1][0] or m_openGL[2]
      Real m_10;
      /// @brief  individual matrix element maps to m_m[1][1] or m_openGL[3]
      Real m_11;
    };
#pragma pack(pop)
  };
#pragma GCC diagnostic pop

}; // end of class
// free function for matrix comparison use in unit tests etc
inline bool operator==(const ngl::Mat2 &_m1, const ngl::Mat2 &_m2)
{
  for(size_t i = 0; i < _m1.m_openGL.size(); ++i)
  {
    if(!(FCompare(_m1.m_openGL[i], _m2.m_openGL[i])))
    {
      return false;
    }
  }
  return true;
}

} // namespace ngl

#endif

