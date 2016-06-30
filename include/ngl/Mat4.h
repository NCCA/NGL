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
#ifndef MAT4_H_
#define MAT4_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Matrix.h
/// @brief a simple 4x4 Homogenous Affine TX matrix
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include <ostream>
#include <array>

namespace ngl
{
class Vec4;
class Vec3;
class Quaternion;



//----------------------------------------------------------------------------------------------------------------------
/// @class Mat4 "include/Mat4.h"
/// @brief Matrix Class to do simple matrix operations included
///  operator overloaded functions for maths and matrix * vector type maths.
/// @note for clarity here is the martix offsets m_openGL[n] and the m_00 / [][] versions
/// I tend to draw this out a lot so thought I would put it here
/// to save me doing it again
///  [y][x] i       [y][x] i       [y][x] i        [y][x]  i
/// [ (0,0) 0 m_00 | (0,1) 4 m_10 | (0,2) 8  m_20 | (0,3) 12 m_30]
/// [ (1,0) 1 m_01 | (1,1) 5 m_11 | (1,2) 9  m_21 | (1,3) 13 m_31]
/// [ (2,0) 2 m_02 | (2,1) 6 m_12 | (2,2) 10 m_22 | (2,3) 14 m_32]
/// [ (3,0) 3 m_03 | (3,1) 7 m_13 | (3,2) 11 m_23 | (3,3) 15 m_33]
/// you will note that the m_ values are transposed so be wary
/// @author Jonathan Macey
/// @version 3.0
/// @date Last Revision 28/09/09 Updated to NCCA Coding standard
/// @example AffineTransforms/Affine.cpp
/// @example AffineTransforms/Global.h
/// @example AffineTransforms/Global.cpp
//----------------------------------------------------------------------------------------------------------------------


class NGL_DLLEXPORT Mat4
{
  // added after clang++ build
  friend class Vec4;
public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor will always create an identity matrix
  //----------------------------------------------------------------------------------------------------------------------
  Mat4() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using 4x4 array, really useful when mixing with Imath as we can do
  /// Imath::Matrix44 <float> iMatrix;
  /// Mat4 nMatrix(iMatrix.x)
  /// @param[in] _m[4][4] the input array for the matrix
  //----------------------------------------------------------------------------------------------------------------------
  Mat4(Real _m[4][4]) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor using individual elements
  /// @param [in] _00 0th element (etc you get the deal)
  //----------------------------------------------------------------------------------------------------------------------
  Mat4(Real _00,Real _01,Real _02,Real _03,
       Real _10,Real _11,Real _12,Real _13,
       Real _20,Real _21,Real _22,Real _23,
       Real _30,Real _31,Real _32,Real _33) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor with reference object
  //----------------------------------------------------------------------------------------------------------------------
  Mat4(const Mat4& _m) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor with Real useful for Mat4 m=1; for identity or Matrix m=3.5 for uniform scale
  //----------------------------------------------------------------------------------------------------------------------
  Mat4(Real _m) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator
  //----------------------------------------------------------------------------------------------------------------------
  Mat4& operator =(const Mat4& _m) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the value at m_m[_x][_y] to _equals
  /// @param[in]  _x the x index into the array
  /// @param[in]  _y the y index into the array
  /// @param[in]  _equals the value to set to
  //----------------------------------------------------------------------------------------------------------------------
  void setAtXY(GLint _x, GLint _y, Real _equals) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clear the matrix to all 0
  //----------------------------------------------------------------------------------------------------------------------
  const Mat4& null() noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  make the matrix m the identity matrix \n
  /// 1 0 0 0 <BR>
  /// 0 1 0 0 <BR>
  /// 0 0 1 0 <BR>
  /// 0 0 0 1 <BR>
  //----------------------------------------------------------------------------------------------------------------------
  const Mat4& identity() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator for matrix multiplication
  /// @param[in] _m the matrix to multiply the current one by
  /// @returns this*_m
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 operator*(const Mat4 &_m) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator to mult this matrix by value _m
  /// @param[in] _m the matrix to multiplt
  /// @returns a new matrix this*_m
  //----------------------------------------------------------------------------------------------------------------------
  const Mat4& operator*=(const Mat4 &_m) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator to add two matrices together
  /// @param[in] _m the matrix to add
  /// @returns this+_m
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 operator+(const Mat4 &_m) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator
  /// @param[in] _m the matrix to add
  /// @returns this+m
  //----------------------------------------------------------------------------------------------------------------------
  const Mat4& operator+=(const Mat4 &_m) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator to mult matrix by a scalar
  /// @param[in] _i the scalar to multiply by
  /// @returns this*_i
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 operator*(const Real _i) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief *= operator with a scalar value
  /// @param[in] _i the scalar to multiply by
  /// @returns the matrix*i
  //----------------------------------------------------------------------------------------------------------------------
  const Mat4& operator*=(const Real _i) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief method to transpose the matrix
  //----------------------------------------------------------------------------------------------------------------------
  const Mat4& transpose() noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set this matrix to a rotation matrix in the X axis for value _deg
  /// note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void rotateX(const Real _deg) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set this matrix to a rotation matrix in the Y axis for value _deg
  /// note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees
  //----------------------------------------------------------------------------------------------------------------------
  void rotateY(const Real _deg) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set this matrix to a rotation matrix in the Z axis for value _deg
  /// note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees
  //----------------------------------------------------------------------------------------------------------------------
   void rotateZ(const Real _deg) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the matrix scale values
  /// @param[in] _x the scale value in the _x
  /// @param[in] _y the scale value in the _y
  /// @param[in] _z the scale value in the _z
  //----------------------------------------------------------------------------------------------------------------------
  void scale(const Real _x,const Real _y,const Real _z) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the matrix as a translation matrix
  /// @param[in] _x the _x translation value
  /// @param[in] _y the _y translation value
  /// @param[in] _z the _z translation value
  //----------------------------------------------------------------------------------------------------------------------
  void translate(const Real _x, const Real _y, const Real _z) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the determinant of the matrix
  /// @returns the determinat
  //----------------------------------------------------------------------------------------------------------------------
  Real determinant() const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get a sub 3x3 matrix used in determinant and Inverse calculations
  /// @param[in] _i index value
  /// @param[in] _j index value
  /// @param[in] o_mat the 3x3 matrix
  //----------------------------------------------------------------------------------------------------------------------
  void subMatrix3x3(const int _i,const int _j,Real o_mat[]) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the data as a 3x3 matrix
  /// @param [out] _d the data from the sub matrix
  //----------------------------------------------------------------------------------------------------------------------
  void as3x3Array(Real _d[9]) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the inverse of the matrix
  /// @returns a new matrix the inverse of the current matrix (warning no error checking )
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 inverse() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief convert this matrix to a Quaternion
  /// @returns the matrix as a Quaternion
  //----------------------------------------------------------------------------------------------------------------------
  Quaternion asQuaternion() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this by a Vec4
  /// @param[in] _v the vector to multiply
  /// @returns Vector M*V
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator * (const Vec4 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief axis / angle rotation using the Euler method
  /// @param[in] _angle the angle in degree to rotate
  /// @param[in] _x part of the axis should be normalised before call
  /// @param[in] _y part of the axis should be normalised before call
  /// @param[in] _z part of the axis  should be normalised before call
  //----------------------------------------------------------------------------------------------------------------------
  void euler(const Real _angle, const Real _x, const Real _y, const Real _z) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the openGL matrix
  /// @returns a pointer to m_openGL[0]
  //----------------------------------------------------------------------------------------------------------------------
  Real * openGL() noexcept{return &m_openGL[0];}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns a matrix adjacent to the matrix passed in
  /// @returns the adjacent matrix
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 Adjacent(const Mat4 &_mat) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the  ajacent matrix to this
  /// @returns the adjacent matrix
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 Adjacent() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the left vector of the matrix (-ve 1st Row)
  /// @returns the up vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getLeftVector() const  noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the right vector of the matrix (  1nd Row)
  /// @returns the up vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getRightVector() const  noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the up vector of the matrix (2nd Row)
  /// @returns the up vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getUpVector() const  noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the down vector of the matrix ( -ve 2nd Row)
  /// @returns the up vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getDownVector() const  noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the forward vector of the matrix (-ve 3rd Row)
  /// @returns the up vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getForwardVector() const  noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get the back vector of the matrix ( 3nd Row)
  /// @returns the up vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 getBackVector() const  noexcept;

public :
 //----------------------------------------------------------------------------------------------------------------------
 // allow access to some of the other classes
 friend class Transformation;
 friend class Quaternion;
 friend class Camera;
 //----------------------------------------------------------------------------------------------------------------------
#pragma pack(push,1)

  union
  {
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief matrix element m_m as a 4x4 array mapped by union to m_nn elements and m_openGL
    //----------------------------------------------------------------------------------------------------------------------
    Real m_m[4][4];
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief  The matrix in m_openGL 16 Real array format usefull for OpenGL fv formats
    /// mapped to m_m[][] elements and m_xx elements
    //----------------------------------------------------------------------------------------------------------------------
    Real m_openGL[16];


    struct
    {
        struct
        {
          Real m_00; //!< individual matrix element maps to m_m[0][0] or m_openGL[0]
          Real m_01; //!< individual matrix element maps to m_m[0][1] or m_openGL[1]
          Real m_02; //!< individual matrix element maps to m_m[0][2] or m_openGL[2]
          Real m_03; //!< individual matrix element maps to m_m[0][3] or m_openGL[3]
          Real m_10; //!< individual matrix element maps to m_m[1][0] or m_openGL[4]
          Real m_11; //!< individual matrix element maps to m_m[1][1] or m_openGL[5]
          Real m_12; //!< individual matrix element maps to m_m[1][2] or m_openGL[6]
          Real m_13; //!< individual matrix element maps to m_m[1][3] or m_openGL[7]
          Real m_20; //!< individual matrix element maps to m_m[2][0] or m_openGL[8]
          Real m_21; //!< individual matrix element maps to m_m[2][1] or m_openGL[9]
          Real m_22; //!< individual matrix element maps to m_m[2][2] or m_openGL[10]
          Real m_23; //!< individual matrix element maps to m_m[2][3] or m_openGL[11]
          Real m_30; //!< individual matrix element maps to m_m[3][0] or m_openGL[12]
          Real m_31; //!< individual matrix element maps to m_m[3][1] or m_openGL[13]
          Real m_32; //!< individual matrix element maps to m_m[3][2] or m_openGL[14]
          Real m_33; //!< individual matrix element maps to m_m[3][3] or m_openGL[15]
        };
    };
   };
#pragma pack(pop)
  }; // end of class

// free function for matrix comparison use in unit tests etc
inline bool operator==(const ngl::Mat4 &_m1 , const ngl::Mat4 &_m2)
{
  for(int i=0; i<16; ++i)
  {
    if(!( FCompare(_m1.m_openGL[i] , _m2.m_openGL[i] )))
    {
      return false;
    }
  }
  return true;
}

// free function for matrix comparison use in unit tests etc
inline bool operator!=(const ngl::Mat4 &_m1 , const ngl::Mat4 &_m2)
{
  for(int i=0; i<16; ++i)
  {
    if(( FCompare(_m1.m_openGL[i] , _m2.m_openGL[i] )))
    {
      return false;
    }
  }
  return true;
}


}// end of namespace

#endif
//----------------------------------------------------------------------------------------------------------------------

