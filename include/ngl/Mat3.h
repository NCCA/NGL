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
#ifndef MAT3_H_
#define MAT3_H_

/// @file Mat3.h
/// @brief a simple 3x3  TX matrix

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include <array>
#include <ostream>
#ifdef USEGLM
#include <glm/mat3x3.hpp>
#endif

namespace ngl
{
class Quaternion;
class Mat4;
class Vec3;


/// @class Mat3 "include/Mat3.h"
/// @brief Mat3 basic 3x3 matrix for certain glsl ops
/// @author Jonathan Macey
/// @version 1.0
/// @date 27/10/11


class NGL_DLLEXPORT Mat3
{
  // added after clang++ build
    public:
  
  /// @brief ctor will always create an identity matrix
  
  Mat3()=default;
  
  /// @brief ctor passing in value
  
  Mat3(Real _00, Real _01, Real _02, Real _10, Real _11, Real _12, Real _20, Real _21, Real _22) noexcept;
  
  /// @brief copy ctor from mat4 will copy left up and fwd vectors
  
  Mat3(const Mat4 &_m) noexcept;

  
  /// @brief copy ctor with Real useful for Matrix m=1; for identity or Matrix m=3.5 for uniform scale
  
  Mat3(const Real _m) noexcept;
#ifdef USEGLM
  Mat3(const glm::mat3 &_m);
  glm::mat3 toGLM() const;
#endif

  
  /// @brief clear the matrix to all 0
  
  const Mat3 &null() noexcept;

  
  /// @brief  make the matrix m the identity matrix \n
  /// 1 0 0 0 <BR>
  /// 0 1 0 0 <BR>
  /// 0 0 1 0 <BR>
  /// 0 0 0 1 <BR>
  
  const Mat3 &identity() noexcept;
  
  /// @brief operator for matrix multiplication
  /// @param[in] _m the matrix to multiply the current one by
  /// @returns this*_m
  
  Mat3 operator*(const Mat3 &_m) const noexcept;
  
  /// @brief operator to mult this matrix by value _m
  /// @param[in] _m the matrix to multiplt
  /// @returns a new matrix this*_m
  
  const Mat3 &operator*=(const Mat3 &_m) noexcept;
  
  /// @brief operator to add two matrices together
  /// @param[in] _m the matrix to add
  /// @returns this+_m
  
  Mat3 operator+(const Mat3 &_m) const noexcept;
  
  /// @brief += operator
  /// @param[in] _m the matrix to add
  /// @returns this+m
  
  const Mat3 &operator+=(const Mat3 &_m) noexcept;
  
  /// @brief operator to mult matrix by a scalar
  /// @param[in] _i the scalar to multiply by
  /// @returns this*_i
  
  Mat3 operator*(Real _i) const noexcept;
  
  /// @brief *= operator with a scalar value
  /// @param[in] _i the scalar to multiply by
  /// @returns the matrix*i
  
  const Mat3 &operator*=(Real _i) noexcept;
  
  /// @brief multiply this by a Vec3
  /// @param[in] _v the vector to multiply
  /// @returns Vector M*V
  
  Vec3 operator*(const Vec3 &_v) const noexcept;
  
  ///  @brief method to transpose the matrix
  
  const Mat3 &transpose() noexcept;

  
  /// @brief return a new matrix as a rotation X
  /// note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees
  
  static Mat3 rotateX(Real _deg) noexcept;
  
  /// @brief returns a new matrix as a rotation in Y
  /// @param[in] _deg the value to be rotated by in degrees
  
  static Mat3 rotateY(Real _deg) noexcept;

  
  /// @brief set this matrix to a rotation matrix in the Z axis for value _deg
  /// note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees
  
  static Mat3 rotateZ(Real _deg) noexcept;
  
  /// @brief set the matrix scale values
  /// @param[in] _x the scale value in the _x
  /// @param[in] _y the scale value in the _y
  /// @param[in] _z the scale value in the _z
  
  static Mat3 scale(Real _x, Real _y, Real _z) noexcept;

  
  /// @brief get the determinant of the matrix
  /// @returns the determinat
  
  Real determinant() const noexcept;

  
  /// @brief set the matrix to be the inverse
  
  Mat3 inverse() noexcept;

  
  /// @brief axis / angle rotation using the Euler method
  /// @param[in] _angle the angle in degree to rotate
  /// @param[in] _x part of the axis should be normalised before call
  /// @param[in] _y part of the axis should be normalised before call
  /// @param[in] _z part of the axis  should be normalised before call
  
  void euler(Real _angle, Real _x, Real _y, Real _z) noexcept;
  
  /// @brief accesor to the openGL matrix
  /// @returns a pointer to m_openGL[0]
  
  Real *openGL() noexcept
  {
    return &m_openGL[0];
  }
  
  /// @brief get the left vector of the matrix (-ve 1st Row)
  /// @returns the up vector
  
  Vec3 getLeftVector() const noexcept;
  
  /// @brief get the right vector of the matrix (  1nd Row)
  /// @returns the up vector
  
  Vec3 getRightVector() const noexcept;
  
  /// @brief get the up vector of the matrix (2nd Row)
  /// @returns the up vector
  
  Vec3 getUpVector() const noexcept;
  
  /// @brief get the down vector of the matrix ( -ve 2nd Row)
  /// @returns the up vector
  
  Vec3 getDownVector() const noexcept;
  
  /// @brief get the forward vector of the matrix (-ve 3rd Row)
  /// @returns the up vector
  
  Vec3 getForwardVector() const noexcept;
  
  /// @brief get the back vector of the matrix ( 3nd Row)
  /// @returns the up vector
  
  Vec3 getBackVector() const noexcept;

    public:
  
  // allow access to some of the other classes
  friend class Transformation;
  friend class Quaternion;
  friend class Camera;
  

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma pack(push, 1)

  union
  {
    /// @brief Mat3 element m_m as a 4x4 array mapped by union to m_nn elements and m_openGL
    Real m_m[3][3];
    /// @brief  The matrix in m_openGL 16 Real array format usefull for OpenGL fv formats
    /// mapped to m_m[][] elements and m_xx elements
    std::array< Real, 9 > m_openGL = {{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}};
    struct
    {      
      /// @brief  individual matrix element maps to m_m[0][0] or m_openGL[0]
      Real m_00;
      /// @brief  individual matrix element maps to m_m[0][1] or m_openGL[1]
      Real m_01;
      /// @brief  individual matrix element maps to m_m[0][2] or m_openGL[2]
      Real m_02;     
      /// @brief  individual matrix element maps to m_m[1][0] or m_openGL[3]
      Real m_10;
      /// @brief  individual matrix element maps to m_m[1][1] or m_openGL[4]
      Real m_11;
      /// @brief  individual matrix element maps to m_m[1][2] or m_openGL[5]      
      Real m_12;
      /// @brief  individual matrix element maps to m_m[2][0] or m_openGL[6]
      Real m_20;
      /// @brief  individual matrix element maps to m_m[2][1] or m_openGL[7]
      Real m_21;
      /// @brief  individual matrix element maps to m_m[2][2] or m_openGL[8]      
      Real m_22;
    };
#pragma pack(pop)
  };
#pragma GCC diagnostic pop

}; // end of class
// free function for matrix comparison use in unit tests etc
inline bool operator==(const ngl::Mat3 &_m1, const ngl::Mat3 &_m2)
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

