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

#include "Mat2.h"
#include "NGLassert.h"
#include "Util.h"
#include "Vec2.h"
#include <cstring> // for memset
#include <iostream>
#ifdef USEGLM
#include <glm/gtc/type_ptr.hpp>
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file Mat2.cpp
/// @brief implementation files for Mat2s class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Mat2::Mat2() noexcept
{
  memset(&m_m, 0, sizeof(m_m));
  m_00 = 1.0f;
  m_11 = 1.0f;
}

Mat2::Mat2(Real _00, Real _01, Real _10, Real _11) noexcept
{
  m_00 = _00;
  m_01 = _01;
  m_10 = _10;
  m_11 = _11;
}

//----------------------------------------------------------------------------------------------------------------------
Mat2::Mat2(const Real _m) noexcept
{
  memset(m_m, 0, sizeof(m_m));
  m_00 = _m;
  m_11 = _m;
}

#ifdef USEGLM
Mat2::Mat2(const glm::mat2 &_m)
{
  memcpy(m_m, glm::value_ptr(_m), sizeof(m_m));
}

glm::mat2 Mat2::toGLM() const
{
  glm::mat2 result;
  memcpy(glm::value_ptr(result), m_m, sizeof(m_m));

  return result;
}

#endif

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
const Mat2 &Mat2::null() noexcept
{
  memset(&m_m, 0, sizeof(m_m));
  return *this;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat2 &Mat2::identity() noexcept
{
  memset(m_m, 0, sizeof(m_m));
  m_00 = 1.0f;
  m_11 = 1.0f;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Mat2 Mat2::operator*(const Mat2 &_m) const noexcept
{
  Mat2 temp;
  temp.m_00 = m_00 * _m.m_00 + m_01 * _m.m_10;
  temp.m_01 = m_00 * _m.m_01 + m_01 * _m.m_11;

  temp.m_10 = m_10 * _m.m_00 + m_11 * _m.m_10;
  temp.m_11 = m_10 * _m.m_01 + m_11 * _m.m_11;

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat2 &Mat2::operator*=(const Mat2 &_m) noexcept
{
  Mat2 temp(*this);
  m_00 = temp.m_00 * _m.m_00 + temp.m_01 * _m.m_10;
  m_01 = temp.m_00 * _m.m_01 + temp.m_01 * _m.m_11;

  m_10 = temp.m_10 * _m.m_00 + temp.m_11 * _m.m_10;
  m_11 = temp.m_10 * _m.m_01 + temp.m_11 * _m.m_11;

  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Mat2 Mat2::operator+(const Mat2 &_m) const noexcept
{
  Mat2 ret;
  auto iterA = std::cbegin(m_openGL);
  auto iterB = std::cbegin(_m.m_openGL);
  auto iterR = std::begin(ret.m_openGL);
  auto end = std::cend(m_openGL);
  for(; iterA != end; ++iterA, ++iterB, ++iterR)
  {
    *iterR = *iterA + *iterB;
  }
  return ret;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat2 &Mat2::operator+=(const Mat2 &_m) noexcept
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
//----------------------------------------------------------------------------------------------------------------------
Mat2 Mat2::operator*(Real _i) const noexcept
{
  Mat2 ret;
  ret.m_00 = m_00 * _i;
  ret.m_01 = m_01 * _i;
  ret.m_10 = m_10 * _i;
  ret.m_11 = m_11 * _i;
  return ret;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat2 &Mat2::operator*=(Real _i) noexcept
{
  for(int y = 0; y < 2; ++y)
  {
    for(int x = 0; x < 2; ++x)
    {
      m_m[y][x] *= _i;
    }
  }
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat2 &Mat2::transpose() noexcept
{
  Mat2 tmp(*this);

  for(int row = 0; row < 2; ++row)
  {
    for(int col = 0; col < 2; ++col)
    {
      m_m[row][col] = tmp.m_m[col][row];
    }
  }
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
[[nodiscard]] Mat2 Mat2::rotate(Real _deg) noexcept
{
  Mat2 m;
  Real beta = radians(_deg);
  Real sr = sinf(beta);
  Real cr = cosf(beta);
  m.m_00 = cr;
  m.m_01 = -sr;
  m.m_10 = sr;
  m.m_11 = cr;
  return m;
}

//----------------------------------------------------------------------------------------------------------------------
[[nodiscard]] Mat2 Mat2::scale(Real _x, Real _y) noexcept
{
  Mat2 m;
  m.m_00 = _x;
  m.m_11 = _y;
  return m;
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Mat2::operator*(const Vec2 &_v) const noexcept
{
  Vec2 temp;

  temp.m_x = _v.m_x * m_00 + _v.m_y * m_01;
  temp.m_y = _v.m_x * m_10 + _v.m_y * m_11;
  return temp;
}

} // end namespace ngl
