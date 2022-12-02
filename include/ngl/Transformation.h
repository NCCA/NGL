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
#ifndef TRANSFORM_H_
#define TRANSFORM_H_

/// @file Transformation.h
/// @brief a simple transformation object containing rot / tx / scale and final matrix

// Library includes
#include "Mat4.h"
#include "NGLassert.h"
#include "Transformation.h"
#include "Vec4.h"

namespace ngl
{

/// @enum decide which matrix is the current active matrix

enum  class ActiveMatrix : char{NORMAL,TRANSPOSE,INVERSE};

/// @class Transformation "include/ngl/Transformation.h"
/// @brief Transformation describes a transformation (translate, scale, rotation)
/// modifed by j macey and included into NGL
/// @author Vincent Bonnet
/// @version 1.5
/// @date 14/03/10 Last Revision 14/03/10

class NGL_DLLEXPORT Transformation
{
  friend class Vec4;
public:

  
  /// @brief Constructor
  
  Transformation() noexcept;
  
  /// @brief Copy Constructor
  Transformation(const Transformation &_t) =default;
  Transformation & operator =(const Transformation &_t) =default;

  /// @brief method to set the scale value in the transform
  /// @param[in] _scale the scale value to set for the transform
  
  void setScale( const Vec3& _scale ) noexcept;
  void setScale( const Vec4& _scale ) noexcept;

  
  /// @brief method to set the scale value in the transform
  /// @param[in] _x x scale value
  /// @param[in] _y y scale value
  /// @param[in] _z z scale value
  
  void setScale(  Real _x,  Real _y,  Real _z  ) noexcept;
  
  /// @brief method to add to the existing the scale value in the transform
  /// @param[in] _scale the scale value to set for the transform
  
  void addScale( const Vec3& _scale ) noexcept;
  void addScale( const Vec4& _scale ) noexcept;
  
  /// @brief method to add to the existing the scale value in the transform
  /// @param[in] _x x scale value
  /// @param[in] _y y scale value
  /// @param[in] _z z scale value
  
  void addScale(  Real _x,  Real _y, Real _z ) noexcept;
  
  /// @brief method to set the position
  /// @param[in] _position position
  
  void setPosition( const Vec4& _position ) noexcept;
  
  /// @brief method to set the position
  /// @param[in] _position position
  
  void setPosition( const Vec3& _position ) noexcept;
  
  /// @brief method to set the position value in the transform
  /// @param[in] _x x position value
  /// @param[in] _y y position value
  /// @param[in] _z z position value
  
  void setPosition( Real _x, Real _y, Real _z  ) noexcept;
  
  /// @brief method add to the existing set the position
  /// @param[in] _position position
  
  void addPosition( const Vec4& _position  ) noexcept;
  
  /// @brief method add to the existing set the position
  /// @param[in] _position position
  
  void addPosition( const Vec3& _position ) noexcept;
  
  /// @brief method to add to the existing position value in the transform
  /// @param[in] _x x position value
  /// @param[in] _y y position value
  /// @param[in] _z z position value
  
  void addPosition( Real _x, Real _y,  Real _z  ) noexcept;
  
  /// @breif method to set the matrix directly
  /// @param[in] _m the matrix to set the m_transform to
  /// need to also re-compute the others
  
  void setMatrix( const Mat4 &_m ) noexcept;
  
  /// @brief method to set the rotation
  /// @param[in] _rotation rotation
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  
  void setRotation( const Vec3& _rotation ) noexcept;
  void setRotation( const Vec4& _rotation ) noexcept;
  
  /// @brief method to set the rotation value in the transform
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  /// @param[in] _x x rotation value
  /// @param[in] _y y rotation value
  /// @param[in] _z z rotation value
  
  void setRotation( Real _x, Real _y, Real _z ) noexcept;
  
  /// @brief method to add to the existing  rotation
  /// @param[in] _rotation rotation
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  
  void addRotation( const Vec3& _rotation   ) noexcept;
  void addRotation( const Vec4& _rotation   ) noexcept;
  
  /// @brief method to add to the existing rotation value in the transform
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  /// @param[in] _x x rotation value
  /// @param[in] _y y rotation value
  /// @param[in] _z z rotation value
  
  void addRotation( Real _x, Real _y, Real _z  ) noexcept;
  
  /// @brief a method to set all the transforms to the identity
  
  void reset() noexcept;
  
  /// @brief function to get the scale
  /// @returns the scale
  
  Vec3 getScale()  const  noexcept    { return m_scale;  }
  
  /// @brief function to get the position
  /// @returns the position
  
  Vec3 getPosition() const  noexcept  { return m_position;  }
  
  /// @brief function to get the rotation
  /// @returns the rotation
  
  Vec3 getRotation() const  noexcept  { return m_rotation;  }
  
  /// @brief function to get the matrix. It computes the matrix if it's dirty
  /// @returns the matrix
  
  Mat4 getMatrix() noexcept{ computeMatrices();  return m_matrix;  }
  
  /// @brief function to get the transpose matrix. It computes the transpose matrix if it's dirty
  /// @returns the transpose matrix
  
  Mat4 getTransposeMatrix() noexcept{  computeMatrices(); return m_transposeMatrix; }
  
  /// @brief function to get the inverse matrix. It computes the inverse matrix if it's dirty
  /// @returns the inverse matrix
  
  Mat4 getInverseMatrix() noexcept {  computeMatrices(); return m_inverseMatrix; }
  
  /// @brief *= operator
  /// @param _m the transformation to combine
  
  void operator*=( const Transformation &_m  ) noexcept;
  
  ///  @brief operator for Transform multiplication will do a matrix
  /// multiplication on each of the matrices
  /// @note this is not const as we need to check that the members are
  /// calculated before we do the multiplication. This is deliberate
  /// @param[in] _m the Transform to multiply the current one by
  /// @returns all the transform matrix members * my _m members
  
  Transformation operator*( const Transformation &_m  ) noexcept;

protected :

  
  /// @brief position
  
  Vec3 m_position={0.0f,0.0f,0.0f};
  
  /// @brief  scale
  
  Vec3 m_scale={1.0f,1.0f,1.0f};
  
  /// @brief  rotation
  
  Vec3 m_rotation={0.0f,0.0f,0.0f};
  
  /// @brief  boolean defines if the matrix is dirty or not
  
  bool m_isMatrixComputed=false;
  
  /// @brief  matrix transformation
  
  Mat4 m_matrix;
  
  /// @brief  transpose matrix transformation
  
  Mat4 m_transposeMatrix;
  
  /// @brief  inverse matrix transformation
  
  Mat4 m_inverseMatrix;
  
  /// @brief method to compute the matrix, transpose and inverse matrix. set the m_bIsMatrixComputed variable to true.
  
  void computeMatrices() noexcept;

};

} // end ngl namespace
#endif

