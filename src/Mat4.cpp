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
#include "Mat4.h"
#include "NGLassert.h"
#include "Quaternion.h"
#include "Util.h"
#include "Vec3.h"
#include <algorithm>
#include <cstring> // for memset
#include <iostream>
#ifdef USEGLM
#include <glm/gtc/type_ptr.hpp>
#endif


/// @file Mat4.cpp
/// @brief implementation files for Matrix class


namespace ngl
{


Mat4::Mat4() noexcept
{
  memset(&m_m, 0, sizeof(m_m));
  m_00 = 1.0f;
  m_11 = 1.0f;
  m_22 = 1.0f;
  m_33 = 1.0f;
}

Mat4::Mat4(Real _m[4][4]) noexcept
{
  for(int y = 0; y < 4; ++y)
  {
    for(int x = 0; x < 4; ++x)
    {
      m_m[y][x] = _m[y][x];
    }
  }
}

Mat4::Mat4(Real _00, Real _01, Real _02, Real _03, Real _10, Real _11, Real _12, Real _13, Real _20, Real _21, Real _22, Real _23, Real _30, Real _31, Real _32, Real _33) noexcept
{
  m_00 = _00;
  m_01 = _01;
  m_02 = _02;
  m_03 = _03;
  m_10 = _10;
  m_11 = _11;
  m_12 = _12;
  m_13 = _13;
  m_20 = _20;
  m_21 = _21;
  m_22 = _22;
  m_23 = _23;
  m_30 = _30;
  m_31 = _31;
  m_32 = _32;
  m_33 = _33;
}

Mat4::Mat4(const Mat4 &_m) noexcept
{
  m_openGL = _m.m_openGL;
}

#ifdef USEGLM
Mat4::Mat4(const glm::mat4 &_m)
{
  memcpy(&m_m[0][0], glm::value_ptr(_m), 16*sizeof(GLfloat));
}

glm::mat4 Mat4::toGLM() const
{
  glm::mat4 result;
  memcpy(glm::value_ptr(result), &m_m[0][0], 16*sizeof(GLfloat));

  return result;
}

#endif


Mat4 &Mat4::operator=(const Mat4 &_m) noexcept
{
  m_openGL = _m.m_openGL;
  return *this;
}

Mat4::Mat4(Real _m) noexcept
{
  memset(m_m, 0, sizeof(m_m));
  m_00 = _m;
  m_11 = _m;
  m_22 = _m;
  m_33 = 1.0f;
}

const Mat4 &Mat4::null() noexcept
{
  memset(&m_m, 0, sizeof(m_m));
  return *this;
}

const Mat4 &Mat4::identity() noexcept
{
  memset(m_m, 0, sizeof(m_m));
  m_00 = 1.0f;
  m_11 = 1.0f;
  m_22 = 1.0f;
  m_33 = 1.0f;
  return *this;
}


const Mat4 &Mat4::operator*=(const Mat4 &_m) noexcept
{
  Mat4 temp(*this);
  //  row 0
  m_00 = temp.m_00 * _m.m_00;
  m_01 = temp.m_01 * _m.m_00;
  m_02 = temp.m_02 * _m.m_00;
  m_03 = temp.m_03 * _m.m_00;

  m_00 += temp.m_10 * _m.m_01;
  m_01 += temp.m_11 * _m.m_01;
  m_02 += temp.m_12 * _m.m_01;
  m_03 += temp.m_13 * _m.m_01;

  m_00 += temp.m_20 * _m.m_02;
  m_01 += temp.m_21 * _m.m_02;
  m_02 += temp.m_22 * _m.m_02;
  m_03 += temp.m_23 * _m.m_02;

  m_00 += temp.m_30 * _m.m_03;
  m_01 += temp.m_31 * _m.m_03;
  m_02 += temp.m_32 * _m.m_03;
  m_03 += temp.m_33 * _m.m_03;

  //  row 1
  m_10 = temp.m_00 * _m.m_10;
  m_11 = temp.m_01 * _m.m_10;
  m_12 = temp.m_02 * _m.m_10;
  m_13 = temp.m_03 * _m.m_10;

  m_10 += temp.m_10 * _m.m_11;
  m_11 += temp.m_11 * _m.m_11;
  m_12 += temp.m_12 * _m.m_11;
  m_13 += temp.m_13 * _m.m_11;

  m_10 += temp.m_20 * _m.m_12;
  m_11 += temp.m_21 * _m.m_12;
  m_12 += temp.m_22 * _m.m_12;
  m_13 += temp.m_23 * _m.m_12;

  m_10 += temp.m_30 * _m.m_13;
  m_11 += temp.m_31 * _m.m_13;
  m_12 += temp.m_32 * _m.m_13;
  m_13 += temp.m_33 * _m.m_13;

  //  row 2
  m_20 = temp.m_00 * _m.m_20;
  m_21 = temp.m_01 * _m.m_20;
  m_22 = temp.m_02 * _m.m_20;
  m_23 = temp.m_03 * _m.m_20;

  m_20 += temp.m_10 * _m.m_21;
  m_21 += temp.m_11 * _m.m_21;
  m_22 += temp.m_12 * _m.m_21;
  m_23 += temp.m_13 * _m.m_21;

  m_20 += temp.m_20 * _m.m_22;
  m_21 += temp.m_21 * _m.m_22;
  m_22 += temp.m_22 * _m.m_22;
  m_23 += temp.m_23 * _m.m_22;

  m_20 += temp.m_30 * _m.m_23;
  m_21 += temp.m_31 * _m.m_23;
  m_22 += temp.m_32 * _m.m_23;
  m_23 += temp.m_33 * _m.m_23;

  //  row 3
  m_30 = temp.m_00 * _m.m_30;
  m_31 = temp.m_01 * _m.m_30;
  m_32 = temp.m_02 * _m.m_30;
  m_33 = temp.m_03 * _m.m_30;

  m_30 += temp.m_10 * _m.m_31;
  m_31 += temp.m_11 * _m.m_31;
  m_32 += temp.m_12 * _m.m_31;
  m_33 += temp.m_13 * _m.m_31;

  m_30 += temp.m_20 * _m.m_32;
  m_31 += temp.m_21 * _m.m_32;
  m_32 += temp.m_22 * _m.m_32;
  m_33 += temp.m_23 * _m.m_32;

  m_30 += temp.m_30 * _m.m_33;
  m_31 += temp.m_31 * _m.m_33;
  m_32 += temp.m_32 * _m.m_33;
  m_33 += temp.m_33 * _m.m_33;

  return *this;
}


Mat4 Mat4::operator+(const Mat4 &_m) const noexcept
{
  Mat4 ret;

  auto iterA = std::cbegin(m_openGL);
  auto iterB = std::cbegin(_m.m_openGL);
  auto iterR = std::begin(ret.m_openGL);
  auto end = std::cend(m_openGL);
  for(; iterA != end; ++iterA, ++iterB, ++iterR)
  {
    *iterR = *iterA + *iterB;
  }
  return ret;

  /* this is one way of doing things with STL however speed is Average time: 15.457 us as
   apposed to Average time: 6.847 us using the above version
  Mat4 ret;
  std::transform(std::begin(m_openGL), std::end(m_openGL),
                 std::begin(_m.m_openGL), std::begin(ret.m_openGL),
                 std::plus<Real>());

  return ret;
  */
}

const Mat4 &Mat4::operator+=(const Mat4 &_m) noexcept
{
  auto iterA = std::begin(m_openGL);
  auto iterB = std::cbegin(_m.m_openGL);
  auto end = std::cend(m_openGL);
  for(; iterA != end; ++iterA, ++iterB)
  {
    *iterA += *iterB;
  }
  return *this;
}

Mat4 Mat4::operator*(const Real _i) const noexcept
{
  Mat4 ret;
  auto iterA = std::cbegin(m_openGL);
  auto iterB = std::begin(ret.m_openGL);
  auto end = std::cend(m_openGL);
  for(; iterA != end; ++iterA, ++iterB)
  {
    *iterB = *(iterA)*_i;
  }
  return ret;
}


const Mat4 &Mat4::operator*=(const Real _i) noexcept
{
  for(int y = 0; y < 4; y++)
  {
    for(int x = 0; x < 4; x++)
    {
      m_m[y][x] *= _i;
    }
  }
  return *this;
}


Vec4 Mat4::operator*(const Vec4 &_v) const noexcept
{
  return Vec4(
    _v.m_x * m_00 + _v.m_y * m_10 + _v.m_z * m_20 + _v.m_w * m_30,
    _v.m_x * m_01 + _v.m_y * m_11 + _v.m_z * m_21 + _v.m_w * m_31,
    _v.m_x * m_02 + _v.m_y * m_12 + _v.m_z * m_22 + _v.m_w * m_32,
    _v.m_x * m_03 + _v.m_y * m_13 + _v.m_z * m_23 + _v.m_w * m_33);
}


const Mat4 &Mat4::transpose() noexcept
{
  Mat4 tmp(*this);

  for(int row = 0; row < 4; row++)
  {
    for(int col = 0; col < 4; col++)
    {
      m_m[row][col] = tmp.m_m[col][row];
    }
  }
  return *this;
}


Mat4 Mat4::rotateX(const Real _deg) noexcept
{
  Mat4 m;
  Real beta = radians(_deg);
  Real sr = sinf(beta);
  Real cr = cosf(beta);
  m.m_11 = cr;
  m.m_12 = sr;
  m.m_21 = -sr;
  m.m_22 = cr;
  return m;
}


Mat4 Mat4::rotateY(const Real _deg) noexcept
{
  Mat4 m;
  Real beta = radians(_deg);
  Real sr = sinf(beta);
  Real cr = cosf(beta);
  m.m_00 = cr;
  m.m_02 = -sr;
  m.m_20 = sr;
  m.m_22 = cr;
  return m;
}


Mat4 Mat4::rotateZ(const Real _deg) noexcept
{
  Mat4 m;
  Real beta = radians(_deg);
  Real sr = sinf(beta);
  Real cr = cosf(beta);
  m.m_00 = cr;
  m.m_01 = sr;
  m.m_10 = -sr;
  m.m_11 = cr;
  return m;
}


Mat4 Mat4::translate(const Real _x, const Real _y, const Real _z) noexcept
{
  Mat4 m;
  m.m_30 = _x;
  m.m_31 = _y;
  m.m_32 = _z;
  return m;
}


Mat4 Mat4::scale(const Real _x, const Real _y, const Real _z) noexcept
{
  Mat4 m;
  m.m_00 = _x;
  m.m_11 = _y;
  m.m_22 = _z;
  return m;
}


Real Mat4::determinant() const noexcept
{
  // Our matrices are 4.4 only, so we can just write the full formula instead of a complex algorithm.
  return (
    m_m[0][0] * m_m[1][1] * m_m[2][2] * m_m[3][3] - m_m[0][0] * m_m[1][1] * m_m[2][3] * m_m[3][2] +
    m_m[0][0] * m_m[1][2] * m_m[2][3] * m_m[3][1] - m_m[0][0] * m_m[1][2] * m_m[2][1] * m_m[3][3] +
    m_m[0][0] * m_m[1][3] * m_m[2][1] * m_m[3][2] - m_m[0][0] * m_m[1][3] * m_m[2][2] * m_m[3][1] -
    m_m[1][0] * m_m[2][1] * m_m[3][2] * m_m[0][3] + m_m[1][0] * m_m[2][1] * m_m[0][2] * m_m[3][3] -
    m_m[1][0] * m_m[3][1] * m_m[0][2] * m_m[2][3] + m_m[1][0] * m_m[3][1] * m_m[2][2] * m_m[0][3] -
    m_m[1][0] * m_m[0][1] * m_m[2][2] * m_m[3][3] + m_m[1][0] * m_m[0][1] * m_m[3][2] * m_m[2][3] +
    m_m[2][0] * m_m[3][1] * m_m[0][2] * m_m[1][3] - m_m[2][0] * m_m[3][1] * m_m[1][2] * m_m[0][3] +
    m_m[2][0] * m_m[0][1] * m_m[1][2] * m_m[3][3] - m_m[2][0] * m_m[0][1] * m_m[3][2] * m_m[1][3] +
    m_m[2][0] * m_m[1][1] * m_m[3][2] * m_m[0][3] - m_m[2][0] * m_m[1][1] * m_m[0][2] * m_m[3][3] -
    m_m[3][0] * m_m[0][1] * m_m[1][2] * m_m[2][3] + m_m[3][0] * m_m[0][1] * m_m[2][2] * m_m[1][3] -
    m_m[3][0] * m_m[1][1] * m_m[2][2] * m_m[0][3] + m_m[3][0] * m_m[1][1] * m_m[0][2] * m_m[2][3] -
    m_m[3][0] * m_m[2][1] * m_m[0][2] * m_m[1][3] + m_m[3][0] * m_m[2][1] * m_m[1][2] * m_m[0][3]);
}


Mat4 Mat4::euler(const Real _angle, const Real _x, const Real _y, const Real _z) noexcept
{
  // Axis and Angle matrix rotation see
  // http://en.wikipedia.org/wiki/Rotation_matrix for more details
  Real beta = radians(-_angle);
  Real cosTheta = cosf((beta));
  Real sinTheta = sinf((beta));
  Real OneMinusCosTheta = 1.0f - cosTheta;
  ngl::Vec3 norm(_x, _y, _z);
  norm.normalize();
  Real x = norm.m_x;
  Real y = norm.m_y;
  Real z = norm.m_z;
  Mat4 m;
  m.m_m[0][0] = OneMinusCosTheta * (x * x) + cosTheta;
  m.m_m[0][1] = OneMinusCosTheta * (x * y) - (z * sinTheta);
  m.m_m[0][2] = OneMinusCosTheta * (x * z) + (y * sinTheta);
  m.m_m[1][0] = OneMinusCosTheta * (x * y) + (z * sinTheta);
  m.m_m[1][1] = OneMinusCosTheta * (y * y) + cosTheta;
  m.m_m[1][2] = OneMinusCosTheta * (y * z) - (x * sinTheta);
  m.m_m[2][0] = OneMinusCosTheta * (x * z) - (y * sinTheta);
  m.m_m[2][1] = OneMinusCosTheta * (y * z) + (x * sinTheta);
  m.m_m[2][2] = OneMinusCosTheta * (z * z) + cosTheta;
  return m;
}



Quaternion Mat4::asQuaternion() const noexcept
{
  // calculate trace of the matrix
  Real T = m_openGL[0] + m_openGL[5] + m_openGL[10] + 1;

  // if trace is greater than 0, calculate an instant calculation
  if(T > 0)
  {
    Real S = static_cast< Real >(0.5f / sqrtf(T));
    return Quaternion(
      static_cast< Real >((m_openGL[6] - m_openGL[9]) * S), static_cast< Real >((m_openGL[8] - m_openGL[2]) * S),
      static_cast< Real >((m_openGL[1] - m_openGL[4]) * S), static_cast< Real >(0.25f / S));
  }
  Real BigF = m_openGL[0];
  unsigned char check = 0;
  if(m_openGL[5] > BigF)
  {
    check = 1;
    BigF = m_openGL[5];
  }
  if(m_openGL[10] > BigF)
  {
    check = 2;
    // BigF  = m_openGL[10];
  }
  switch(check)
  {
    case 0:
    {
      Real S = static_cast< Real >(sqrtf(1.0f + m_openGL[0] - m_openGL[5] - m_openGL[10]) * 2.0f);

      return Quaternion(
        0.5f / S, (m_openGL[1] + m_openGL[4]) / S, (m_openGL[2] + m_openGL[8]) / S, (m_openGL[6] + m_openGL[9]) / S);
    }
    case 1:
    {
      Real S = static_cast< Real >(sqrtf(1.0f + m_openGL[5] - m_openGL[0] - m_openGL[10]) * 2.0f);

      return Quaternion(
        (m_openGL[1] + m_openGL[4]) / S, 0.5f / S, (m_openGL[6] + m_openGL[9]) / S, (m_openGL[2] + m_openGL[8]) / S);
    }
    case 2:
    {
      Real S = static_cast< Real >(sqrtf(1.0f + m_openGL[10] - m_openGL[0] - m_openGL[5]) * 2.0f);

      return Quaternion(
        (m_openGL[2] + m_openGL[8]) / S, (m_openGL[6] + m_openGL[9]) / S, 0.5f / S, (m_openGL[1] + m_openGL[4]) / S);
    }
    default:
    {
      // NGL_ASSERT(0 && "SHOULDN'T GET HERE in ngl Quaternion");
      break;
    }
  } // end switch
  return Quaternion();
}


Mat4 Mat4::adjacent(const Mat4 &_mat) noexcept
{
  Mat4 m;

  m.m_00 = _mat.m_m[1][1] * (_mat.m_m[2][2] * _mat.m_m[3][3] - _mat.m_m[3][2] * _mat.m_m[2][3]) +
           _mat.m_m[1][2] * (_mat.m_m[3][1] * _mat.m_m[2][3] - _mat.m_m[2][1] * _mat.m_m[3][3]) +
           _mat.m_m[1][3] * (_mat.m_m[2][1] * _mat.m_m[3][2] - _mat.m_m[3][1] * _mat.m_m[2][2]);
  m.m_01 = _mat.m_m[1][0] * (_mat.m_m[3][2] * _mat.m_m[2][3] - _mat.m_m[2][2] * _mat.m_m[3][3]) +
           _mat.m_m[1][2] * (_mat.m_m[2][0] * _mat.m_m[3][3] - _mat.m_m[3][0] * _mat.m_m[2][3]) +
           _mat.m_m[1][3] * (_mat.m_m[3][0] * _mat.m_m[2][2] - _mat.m_m[2][0] * _mat.m_m[3][2]);
  m.m_02 = _mat.m_m[1][0] * (_mat.m_m[2][1] * _mat.m_m[3][3] - _mat.m_m[3][1] * _mat.m_m[2][3]) +
           _mat.m_m[1][1] * (_mat.m_m[3][0] * _mat.m_m[2][3] - _mat.m_m[2][0] * _mat.m_m[3][3]) +
           _mat.m_m[1][3] * (_mat.m_m[2][0] * _mat.m_m[3][1] - _mat.m_m[3][0] * _mat.m_m[2][1]);
  m.m_03 = _mat.m_m[1][0] * (_mat.m_m[3][1] * _mat.m_m[2][2] - _mat.m_m[2][1] * _mat.m_m[3][2]) +
           _mat.m_m[1][1] * (_mat.m_m[2][0] * _mat.m_m[3][2] - _mat.m_m[3][0] * _mat.m_m[2][2]) +
           _mat.m_m[1][2] * (_mat.m_m[3][0] * _mat.m_m[2][1] - _mat.m_m[2][0] * _mat.m_m[3][1]);

  m.m_10 = _mat.m_m[0][1] * (_mat.m_m[3][2] * _mat.m_m[2][3] - _mat.m_m[2][2] * _mat.m_m[3][3]) +
           _mat.m_m[0][2] * (_mat.m_m[2][1] * _mat.m_m[3][3] - _mat.m_m[3][1] * _mat.m_m[2][3]) +
           _mat.m_m[0][3] * (_mat.m_m[3][1] * _mat.m_m[2][2] - _mat.m_m[2][1] * _mat.m_m[3][2]);
  m.m_11 = _mat.m_m[0][0] * (_mat.m_m[2][2] * _mat.m_m[3][3] - _mat.m_m[3][2] * _mat.m_m[2][3]) +
           _mat.m_m[0][2] * (_mat.m_m[3][0] * _mat.m_m[2][3] - _mat.m_m[2][0] * _mat.m_m[3][3]) +
           _mat.m_m[0][3] * (_mat.m_m[2][0] * _mat.m_m[3][2] - _mat.m_m[3][0] * _mat.m_m[2][2]);
  m.m_12 = _mat.m_m[0][0] * (_mat.m_m[3][1] * _mat.m_m[2][3] - _mat.m_m[2][1] * _mat.m_m[3][3]) +
           _mat.m_m[0][1] * (_mat.m_m[2][0] * _mat.m_m[3][3] - _mat.m_m[3][0] * _mat.m_m[2][3]) +
           _mat.m_m[0][3] * (_mat.m_m[3][0] * _mat.m_m[2][1] - _mat.m_m[2][0] * _mat.m_m[3][1]);
  m.m_13 = _mat.m_m[0][0] * (_mat.m_m[2][1] * _mat.m_m[3][2] - _mat.m_m[3][1] * _mat.m_m[2][2]) +
           _mat.m_m[0][1] * (_mat.m_m[3][0] * _mat.m_m[2][2] - _mat.m_m[2][0] * _mat.m_m[3][2]) +
           _mat.m_m[0][2] * (_mat.m_m[2][0] * _mat.m_m[3][1] - _mat.m_m[3][0] * _mat.m_m[2][1]);

  m.m_20 = _mat.m_m[0][1] * (_mat.m_m[1][2] * _mat.m_m[3][3] - _mat.m_m[3][2] * _mat.m_m[1][3]) +
           _mat.m_m[0][2] * (_mat.m_m[3][1] * _mat.m_m[1][3] - _mat.m_m[1][1] * _mat.m_m[3][3]) +
           _mat.m_m[0][3] * (_mat.m_m[1][1] * _mat.m_m[3][2] - _mat.m_m[3][1] * _mat.m_m[1][2]);
  m.m_21 = _mat.m_m[0][0] * (_mat.m_m[3][2] * _mat.m_m[1][3] - _mat.m_m[1][2] * _mat.m_m[3][3]) +
           _mat.m_m[0][2] * (_mat.m_m[1][0] * _mat.m_m[3][3] - _mat.m_m[3][0] * _mat.m_m[1][3]) +
           _mat.m_m[0][3] * (_mat.m_m[3][0] * _mat.m_m[1][2] - _mat.m_m[1][0] * _mat.m_m[3][2]);
  m.m_22 = _mat.m_m[0][0] * (_mat.m_m[1][1] * _mat.m_m[3][3] - _mat.m_m[3][1] * _mat.m_m[1][3]) +
           _mat.m_m[0][1] * (_mat.m_m[3][0] * _mat.m_m[1][3] - _mat.m_m[1][0] * _mat.m_m[3][3]) +
           _mat.m_m[0][3] * (_mat.m_m[1][0] * _mat.m_m[3][1] - _mat.m_m[3][0] * _mat.m_m[1][1]);
  m.m_23 = _mat.m_m[0][0] * (_mat.m_m[3][1] * _mat.m_m[1][2] - _mat.m_m[1][1] * _mat.m_m[3][2]) +
           _mat.m_m[0][1] * (_mat.m_m[1][0] * _mat.m_m[3][2] - _mat.m_m[3][0] * _mat.m_m[1][2]) +
           _mat.m_m[0][2] * (_mat.m_m[3][0] * _mat.m_m[1][1] - _mat.m_m[1][0] * _mat.m_m[3][1]);

  m.m_30 = _mat.m_m[0][1] * (_mat.m_m[2][2] * _mat.m_m[1][3] - _mat.m_m[1][2] * _mat.m_m[2][3]) +
           _mat.m_m[0][2] * (_mat.m_m[1][1] * _mat.m_m[2][3] - _mat.m_m[2][1] * _mat.m_m[1][3]) +
           _mat.m_m[0][3] * (_mat.m_m[2][1] * _mat.m_m[1][2] - _mat.m_m[1][1] * _mat.m_m[2][2]);
  m.m_31 = _mat.m_m[0][0] * (_mat.m_m[1][2] * _mat.m_m[2][3] - _mat.m_m[2][2] * _mat.m_m[1][3]) +
           _mat.m_m[0][2] * (_mat.m_m[2][0] * _mat.m_m[1][3] - _mat.m_m[1][0] * _mat.m_m[2][3]) +
           _mat.m_m[0][3] * (_mat.m_m[1][0] * _mat.m_m[2][2] - _mat.m_m[2][0] * _mat.m_m[1][2]);
  m.m_32 = _mat.m_m[0][0] * (_mat.m_m[2][1] * _mat.m_m[1][3] - _mat.m_m[1][1] * _mat.m_m[2][3]) +
           _mat.m_m[0][1] * (_mat.m_m[1][0] * _mat.m_m[2][3] - _mat.m_m[2][0] * _mat.m_m[1][3]) +
           _mat.m_m[0][3] * (_mat.m_m[2][0] * _mat.m_m[1][1] - _mat.m_m[1][0] * _mat.m_m[2][1]);
  m.m_33 = _mat.m_m[0][0] * (_mat.m_m[1][1] * _mat.m_m[2][2] - _mat.m_m[2][1] * _mat.m_m[1][2]) +
           _mat.m_m[0][1] * (_mat.m_m[2][0] * _mat.m_m[1][2] - _mat.m_m[1][0] * _mat.m_m[2][2]) +
           _mat.m_m[0][2] * (_mat.m_m[1][0] * _mat.m_m[2][1] - _mat.m_m[2][0] * _mat.m_m[1][1]);

  return m;
}

Mat4 Mat4::adjacent() noexcept
{
  Mat4 m;

  m.m_00 = m_m[1][1] * (m_m[2][2] * m_m[3][3] - m_m[3][2] * m_m[2][3]) +
           m_m[1][2] * (m_m[3][1] * m_m[2][3] - m_m[2][1] * m_m[3][3]) +
           m_m[1][3] * (m_m[2][1] * m_m[3][2] - m_m[3][1] * m_m[2][2]);
  m.m_01 = m_m[1][0] * (m_m[3][2] * m_m[2][3] - m_m[2][2] * m_m[3][3]) +
           m_m[1][2] * (m_m[2][0] * m_m[3][3] - m_m[3][0] * m_m[2][3]) +
           m_m[1][3] * (m_m[3][0] * m_m[2][2] - m_m[2][0] * m_m[3][2]);
  m.m_02 = m_m[1][0] * (m_m[2][1] * m_m[3][3] - m_m[3][1] * m_m[2][3]) +
           m_m[1][1] * (m_m[3][0] * m_m[2][3] - m_m[2][0] * m_m[3][3]) +
           m_m[1][3] * (m_m[2][0] * m_m[3][1] - m_m[3][0] * m_m[2][1]);
  m.m_03 = m_m[1][0] * (m_m[3][1] * m_m[2][2] - m_m[2][1] * m_m[3][2]) +
           m_m[1][1] * (m_m[2][0] * m_m[3][2] - m_m[3][0] * m_m[2][2]) +
           m_m[1][2] * (m_m[3][0] * m_m[2][1] - m_m[2][0] * m_m[3][1]);

  m.m_10 = m_m[0][1] * (m_m[3][2] * m_m[2][3] - m_m[2][2] * m_m[3][3]) +
           m_m[0][2] * (m_m[2][1] * m_m[3][3] - m_m[3][1] * m_m[2][3]) +
           m_m[0][3] * (m_m[3][1] * m_m[2][2] - m_m[2][1] * m_m[3][2]);
  m.m_11 = m_m[0][0] * (m_m[2][2] * m_m[3][3] - m_m[3][2] * m_m[2][3]) +
           m_m[0][2] * (m_m[3][0] * m_m[2][3] - m_m[2][0] * m_m[3][3]) +
           m_m[0][3] * (m_m[2][0] * m_m[3][2] - m_m[3][0] * m_m[2][2]);
  m.m_12 = m_m[0][0] * (m_m[3][1] * m_m[2][3] - m_m[2][1] * m_m[3][3]) +
           m_m[0][1] * (m_m[2][0] * m_m[3][3] - m_m[3][0] * m_m[2][3]) +
           m_m[0][3] * (m_m[3][0] * m_m[2][1] - m_m[2][0] * m_m[3][1]);
  m.m_13 = m_m[0][0] * (m_m[2][1] * m_m[3][2] - m_m[3][1] * m_m[2][2]) +
           m_m[0][1] * (m_m[3][0] * m_m[2][2] - m_m[2][0] * m_m[3][2]) +
           m_m[0][2] * (m_m[2][0] * m_m[3][1] - m_m[3][0] * m_m[2][1]);

  m.m_20 = m_m[0][1] * (m_m[1][2] * m_m[3][3] - m_m[3][2] * m_m[1][3]) +
           m_m[0][2] * (m_m[3][1] * m_m[1][3] - m_m[1][1] * m_m[3][3]) +
           m_m[0][3] * (m_m[1][1] * m_m[3][2] - m_m[3][1] * m_m[1][2]);
  m.m_21 = m_m[0][0] * (m_m[3][2] * m_m[1][3] - m_m[1][2] * m_m[3][3]) +
           m_m[0][2] * (m_m[1][0] * m_m[3][3] - m_m[3][0] * m_m[1][3]) +
           m_m[0][3] * (m_m[3][0] * m_m[1][2] - m_m[1][0] * m_m[3][2]);
  m.m_22 = m_m[0][0] * (m_m[1][1] * m_m[3][3] - m_m[3][1] * m_m[1][3]) +
           m_m[0][1] * (m_m[3][0] * m_m[1][3] - m_m[1][0] * m_m[3][3]) +
           m_m[0][3] * (m_m[1][0] * m_m[3][1] - m_m[3][0] * m_m[1][1]);
  m.m_23 = m_m[0][0] * (m_m[3][1] * m_m[1][2] - m_m[1][1] * m_m[3][2]) +
           m_m[0][1] * (m_m[1][0] * m_m[3][2] - m_m[3][0] * m_m[1][2]) +
           m_m[0][2] * (m_m[3][0] * m_m[1][1] - m_m[1][0] * m_m[3][1]);

  m.m_30 = m_m[0][1] * (m_m[2][2] * m_m[1][3] - m_m[1][2] * m_m[2][3]) +
           m_m[0][2] * (m_m[1][1] * m_m[2][3] - m_m[2][1] * m_m[1][3]) +
           m_m[0][3] * (m_m[2][1] * m_m[1][2] - m_m[1][1] * m_m[2][2]);
  m.m_31 = m_m[0][0] * (m_m[1][2] * m_m[2][3] - m_m[2][2] * m_m[1][3]) +
           m_m[0][2] * (m_m[2][0] * m_m[1][3] - m_m[1][0] * m_m[2][3]) +
           m_m[0][3] * (m_m[1][0] * m_m[2][2] - m_m[2][0] * m_m[1][2]);
  m.m_32 = m_m[0][0] * (m_m[2][1] * m_m[1][3] - m_m[1][1] * m_m[2][3]) +
           m_m[0][1] * (m_m[1][0] * m_m[2][3] - m_m[2][0] * m_m[1][3]) +
           m_m[0][3] * (m_m[2][0] * m_m[1][1] - m_m[1][0] * m_m[2][1]);
  m.m_33 = m_m[0][0] * (m_m[1][1] * m_m[2][2] - m_m[2][1] * m_m[1][2]) +
           m_m[0][1] * (m_m[2][0] * m_m[1][2] - m_m[1][0] * m_m[2][2]) +
           m_m[0][2] * (m_m[1][0] * m_m[2][1] - m_m[2][0] * m_m[1][1]);

  return m;
}

Mat4 Mat4::inverse() noexcept
{

  Mat4 t;
  t.m_00 = m_11 * m_22 * m_33 + m_12 * m_23 * m_31 + m_13 * m_21 * m_32 - m_11 * m_32 * m_23 - m_12 * m_21 * m_33 -
           m_13 * m_22 * m_31;
  t.m_01 = m_01 * m_23 * m_32 + m_02 * m_21 * m_33 + m_03 * m_22 * m_31 - m_01 * m_22 * m_33 - m_02 * m_23 * m_31 -
           m_03 * m_21 * m_32;
  t.m_02 = m_01 * m_12 * m_33 + m_02 * m_13 * m_31 + m_03 * m_11 * m_32 - m_01 * m_13 * m_32 - m_02 * m_11 * m_33 -
           m_03 * m_12 * m_31;
  t.m_03 = m_01 * m_13 * m_22 + m_02 * m_11 * m_23 + m_03 * m_12 * m_21 - m_01 * m_12 * m_23 - m_02 * m_13 * m_21 -
           m_03 * m_11 * m_22;
  t.m_10 = m_10 * m_23 * m_32 + m_12 * m_20 * m_33 + m_13 * m_22 * m_30 - m_10 * m_22 * m_33 - m_12 * m_23 * m_30 -
           m_13 * m_20 * m_32;
  t.m_11 = m_00 * m_22 * m_33 + m_02 * m_23 * m_30 + m_03 * m_20 * m_32 - m_00 * m_23 * m_32 - m_02 * m_20 * m_33 -
           m_03 * m_22 * m_30;
  t.m_12 = m_00 * m_13 * m_32 + m_02 * m_10 * m_33 + m_03 * m_12 * m_30 - m_00 * m_12 * m_33 - m_02 * m_13 * m_30 -
           m_03 * m_10 * m_32;
  t.m_13 = m_00 * m_12 * m_23 + m_02 * m_13 * m_20 + m_03 * m_10 * m_22 - m_00 * m_13 * m_22 - m_02 * m_10 * m_23 -
           m_03 * m_12 * m_20;
  t.m_20 = m_10 * m_21 * m_33 + m_11 * m_23 * m_30 + m_13 * m_20 * m_31 - m_10 * m_23 * m_31 - m_11 * m_20 * m_33 -
           m_13 * m_21 * m_30;
  t.m_21 = m_00 * m_23 * m_31 + m_01 * m_20 * m_33 + m_03 * m_21 * m_30 - m_00 * m_21 * m_33 - m_01 * m_23 * m_30 -
           m_03 * m_20 * m_31;
  t.m_22 = m_00 * m_11 * m_33 + m_01 * m_13 * m_30 + m_03 * m_10 * m_31 - m_00 * m_13 * m_31 - m_01 * m_10 * m_33 -
           m_03 * m_11 * m_30;
  t.m_23 = m_00 * m_13 * m_21 + m_01 * m_10 * m_23 + m_03 * m_11 * m_20 - m_00 * m_11 * m_23 - m_01 * m_13 * m_20 -
           m_03 * m_10 * m_21;
  t.m_30 = m_10 * m_22 * m_31 + m_11 * m_20 * m_32 + m_12 * m_21 * m_30 - m_10 * m_21 * m_32 - m_11 * m_22 * m_30 -
           m_12 * m_20 * m_31;
  t.m_31 = m_00 * m_21 * m_32 + m_01 * m_22 * m_30 + m_02 * m_20 * m_31 - m_00 * m_22 * m_31 - m_01 * m_20 * m_32 -
           m_02 * m_21 * m_30;
  t.m_32 = m_00 * m_12 * m_31 + m_01 * m_10 * m_32 + m_02 * m_11 * m_30 - m_00 * m_11 * m_32 - m_01 * m_12 * m_30 -
           m_02 * m_10 * m_31;
  t.m_33 = m_00 * m_11 * m_22 + m_01 * m_12 * m_20 + m_02 * m_10 * m_21 - m_00 * m_12 * m_21 - m_01 * m_10 * m_22 -
           m_02 * m_11 * m_20;

  auto det = determinant();
  det = 1.0f / det;
  return t * det;
}


Vec3 Mat4::getLeftVector() const noexcept
{
  return Vec3(-m_openGL[0], -m_openGL[1], -m_openGL[2]);
}

Vec3 Mat4::getRightVector() const noexcept
{
  return Vec3(m_openGL[0], m_openGL[1], m_openGL[2]);
}

Vec3 Mat4::getUpVector() const noexcept
{
  return Vec3(m_openGL[4], m_openGL[5], m_openGL[6]);
}


Vec3 Mat4::getDownVector() const noexcept
{
  return Vec3(-m_openGL[4], -m_openGL[5], -m_openGL[6]);
}

Vec3 Mat4::getForwardVector() const noexcept
{
  return Vec3(-m_openGL[8], -m_openGL[9], -m_openGL[10]);
}


Vec3 Mat4::getBackVector() const noexcept
{
  return Vec3(m_openGL[8], m_openGL[9], m_openGL[10]);
}

Real &Mat4::operator[](size_t _i) noexcept
{
  NGL_ASSERT(_i <= 15)
  return m_openGL[_i];
}
Real Mat4::operator[](size_t _i) const noexcept
{
  NGL_ASSERT(_i <= 15)
  return m_openGL[_i];
}
} // end namespace ngl
