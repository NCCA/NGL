/*
  Copyright (C) 2011 Jon Macey

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
#ifndef VEC2_H_
#define VEC2_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec2.h
/// @brief a simple 2 tuple container for compatibility with glsl
//----------------------------------------------------------------------------------------------------------------------

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include <array>
#ifdef USEGLM
#include <glm/vec2.hpp>
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec2.h
/// @brief encapsulates a 2 float object like glsl Vec2 but not maths
/// use the Vec2 class for maths and the asVec2 to return a Vec2
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/6/11 initial version
/// Revision History :
/// Initial Version 20/6/11
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @class Vec2 "include/Vec2.h"
/// @brief simple Vec2 encapsulates a 3 float object like glsl Vec2 but not maths
/// use the Vec2 class for maths and the asVec2 to return a Vec2
//----------------------------------------------------------------------------------------------------------------------

class Vec4;
class Mat2;
class NGL_DLLEXPORT Vec2
{

public:
  Vec2()=default;
  Vec2(const Vec2 &_v) =  default;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialise the constructor from 3 or 4 Real
  /// @param[in]  _x x value
  /// @param[in]  _y y value
  //----------------------------------------------------------------------------------------------------------------------
  Vec2(Real _x,Real _y ) noexcept : m_x(_x), m_y(_y){}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the Vec2 component from 3 values
  /// @param[in]  _x the x component
  /// @param[in]  _y the y component
  //----------------------------------------------------------------------------------------------------------------------
  void set(Real _x, Real _y) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec2
  /// @param[in]  _v the Vec2 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(const Vec2 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vector
  /// @param[in]  _v the Vec2 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(const Vec4 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
#ifdef USEGLM
  Vec2(const glm::vec2 &_v) noexcept
    : m_x(_v.x), m_y(_v.y)
  {
  }
  glm::vec2 toGLM() const
  {
    return glm::vec2(m_x, m_y);
  }
  void set(const glm::vec2 &_r)
  {
    m_x = _r.x;
    m_y = _r.y;
  }

#endif
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clears the Vec2 to 0,0,0
  //----------------------------------------------------------------------------------------------------------------------
  void null() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] index operator to access the index component of the Vec2
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  Real &operator[](const size_t &_i) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief const [] index operator to access the index component of the Vec2
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  const Real &operator[](const size_t &_i) const noexcept
  {
    return m_openGL[_i];
  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator add Vec2 v to current Vec2
  /// @param[in]  &_v Vec2 to add
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 &operator+=(const Vec2 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief -= operator this-=v
  /// @param[in]  &_v Vec2 to subtract
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 &operator-=(const Vec2 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length of the vector
  /// @returns  \f$\sqrt{x^2+y^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Real length() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length squared of the vector (no sqrt so quicker)
  /// @returns  \f$x^2+y^2\f$
  //----------------------------------------------------------------------------------------------------------------------
  Real lengthSquared() const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator add Vec2+Vec2
  /// @param[in]  &_v the value to add
  /// @returns the Vec2 + v
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator+(const Vec2 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide Vec2 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// @returns a Vec2 V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator/(Real _v) const noexcept;
  Vec2 &operator/=(const Vec2 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide this Vec2 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// sets the Vec2 to Vec2 V(x/v,y/v)
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 &operator/=(Real _v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this Vec2 components by a scalar
  /// @param[in] _v the scalar to multiply by
  /// sets the Vec2 to Vec2 V(x*v,y*v)
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 &operator*=(Real _v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief subtraction operator subtract vevtor-Vec2
  /// @param[in]  &_v the value to sub
  /// @returns this - v
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator-(const Vec2 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator mult vevtor*Vec2
  /// @param[in]  _v the value to mult
  /// @returns new Vec2 this*v
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator*(const Vec2 &_v) const noexcept;
  Vec2 operator*(const Mat2 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current Vec2 to rhs
  /// @param[in] _v the Vec2 to set
  /// @returns a new Vec2
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 &operator=(const Vec2 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief negate the Vec2 components
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator-() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check for equality uses FCompare (from Util.h) as float values
  /// @param[in] _v the Vec2 to check against
  /// @returns true or false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator==(const Vec2 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief not equal check
  /// @param[in] _v the Vec2 to check against
  /// @returns true of false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator!=(const Vec2 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief \ operator div Vec2/Vec2
  /// @param[in]  _v the value to div by
  /// @returns Vec2 / Vec2
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator/(const Vec2 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this * i for each element
  /// @param[in]  _i the scalar to mult by
  /// @returns Vec2
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 operator*(Real _i) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Normalize the vector using
  /// \n \f$x=x/\sqrt{x^2+y^2} \f$
  /// \n \f$y=y/\sqrt{x^2+y^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  void normalize() noexcept;
  static Vec2 zero();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return this dotted with _b
  /// @param[in]  _b vector to dot current vector with
  /// @returns  the dot product
  //----------------------------------------------------------------------------------------------------------------------
  Real dot(const Vec2 &_b) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the m_openGL matrix returns the address of the 0th element
  //----------------------------------------------------------------------------------------------------------------------
  Real *openGL() noexcept
  {
    return &m_openGL[0];
  }

  /// @note I've made this public as some compilers automatically make the
  /// anonymous unions public whereas clang++ complains see this post
  /// http://jonmacey.blogspot.com/2011/03/anonymous-union-struct-weirdness.html
    public:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma pack(push, 1)
  union
  {
    struct
    {
      Real m_x;
      Real m_y;

    };
    std::array< Real, 2 > m_openGL={0.0f,0.0f};
#pragma pack(pop)
  };
};
#pragma GCC diagnostic pop

//----------------------------------------------------------------------------------------------------------------------
/// @brief scalar * vector operator
/// @param _k the float value
/// @param _v the vector value
/// @returns a vector _k*v
//----------------------------------------------------------------------------------------------------------------------
inline Vec2 operator*(Real _k, const Vec2 &_v) noexcept
{
  return Vec2(_k * _v.m_x, _k * _v.m_y);
}

} // end namespace ngl
#endif

//----------------------------------------------------------------------------------------------------------------------
