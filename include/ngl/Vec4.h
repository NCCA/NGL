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
#ifndef VEC4_H_
#define VEC4_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Vector.h
/// @brief a simple 4D vector class
//----------------------------------------------------------------------------------------------------------------------

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec2.h"
#include "Vec3.h"
#include <array>
#ifdef USEGLM
#include <glm/vec4.hpp>
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec4.h
/// @brief encapsulates a 4d Homogenous Point / Vector object
/// @author Jonathan Macey
/// @version 3.0
/// @date 28/9/09 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 24/11/04
/// @todo lots of tidying up and code optimizations
/// @todo at some stage re-write to use Machine Code and MMX extentions
/// @example AffineTransforms/Affine.cpp
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
// pre-declare the matrix class

class Mat4;

//----------------------------------------------------------------------------------------------------------------------
/// @class Vec4 "include/Vec4.h"
/// @brief simple Vector class for OpenGL graphics, contains overloaded operators for
/// most math functions, including operators for manipulation by Point3 and Matrix
/// has a simple union to allow data to be access as x,y,z,w or float[4] array
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT Vec4
{
  // added after clang++ build
  friend class Mat4;
  friend class VBOPrimitives;
  friend class Transformation;
  friend class Quaternion;
  friend class Obj;

    public:
  Vec4()=default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec4(const Vec4 &_v) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec4(const Vec3 &_v, float _w = 1.0f) noexcept
    : m_x(_v.m_x), m_y(_v.m_y), m_z(_v.m_z), m_w(_w)
  {
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialise the constructor from 3 or 4 Real
  /// @param[in]  _x x value
  /// @param[in]  _y y value
  /// @param[in]  _z z value
  /// @param[in]  _w 1.0f default so acts as a points
  //----------------------------------------------------------------------------------------------------------------------
  Vec4(Real _x, Real _y, Real _z, Real _w = 1.0f) noexcept
    : m_x(_x), m_y(_y), m_z(_z), m_w(_w)
  {
  }
#ifdef USEGLM
  Vec4(const glm::vec4 &_v) noexcept
    : m_x(_v.x), m_y(_v.y), m_z(_v.z), m_w(_v.w)
  {
    ;
  }
  glm::vec4 toGLM() const
  {
    return glm::vec4(m_x, m_y, m_z, m_w);
  }
  void set(const glm::vec4 &_r)
  {
    m_x = _r.x;
    m_y = _r.y;
    m_z = _r.z;
    m_w = _r.w;
  }

#endif

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return this dotted with _b
  /// @param[in]  _b vector to dot current vector with
  /// @returns  the dot product
  //----------------------------------------------------------------------------------------------------------------------
  Real dot(const Vec4 &_b) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the vector component from 3 values
  /// @param[in]  _x the x component
  /// @param[in]  _y the y component
  /// @param[in]  _z the z component
  /// @param[in]  _w the w component default to 1 for a point
  //----------------------------------------------------------------------------------------------------------------------
  void set(Real _x, Real _y, Real _z, Real _w = 1.0) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  vector
  /// @param[in]  _v the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(const Vec4 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  vector
  /// @param[in]  _v the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(const Vec3 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clears the vector to 0,0,0,1
  //----------------------------------------------------------------------------------------------------------------------
  void null() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get as a Vec3 for glsl etc
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 toVec3() const noexcept
  {
    return Vec3(m_x, m_y, m_z);
  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get as a Vec2 for glsl etc
  //----------------------------------------------------------------------------------------------------------------------
  Vec2 toVec2() const noexcept
  {
    return Vec2(m_x, m_y);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] index operator to access the index component of the vector
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  Real &operator[](const size_t &_i) noexcept;
  const Real &operator[](const size_t &_i) const noexcept
  {
    return m_openGL[_i];
  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length of the vector
  /// @returns  \f$\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Real length() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Normalize the vector using
  /// \n \f$x=x/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$y=y/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$z=z/\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &normalize() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the vector as the cross product from 2 other vectors
  /// @param[in]  _v1 the first vector
  /// @param[in]  _v2 the second vector
  //----------------------------------------------------------------------------------------------------------------------
  void cross(const Vec4 &_v1, const Vec4 &_v2) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the cross product of this cross with b
  /// @param[in]  _b the vector cross this with
  /// @returns  the result of this cross b
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 cross(const Vec4 &_b) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator add vector v to current vector
  /// @param[in]  &_v vector to add
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator+=(const Vec4 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief -= operator this-=v
  /// @param[in]  &_v vector to subtract
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator-=(const Vec4 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this * i for each element
  /// @param[in]  _i the scalar to mult by
  /// @returns Vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator*(Real _i) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator add vector+vector
  /// @param[in]  &_v the value to add
  /// @returns the vector + v
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator+(const Vec4 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide vector components by a scalar
  /// @param[in] _v the scalar to divide by
  /// @returns a vector V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator/(Real _v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide this vector components by a scalar
  /// @param[in] _v the scalar to divide by
  /// sets the vector to vector V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator/=(Real _v) noexcept;
  Vec4 &operator/=(const Vec4 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this vector components by a scalar
  /// @param[in] _v the scalar to multiply by
  /// sets the vector to vector V(x*v,y*v,z*v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator*=(Real _v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief subtraction operator subtract vevtor-vector
  /// @param[in]  &_v the value to sub
  /// @returns this - v
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator-(const Vec4 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator mult vevtor*vector
  /// @param[in]  _v the value to mult
  /// @returns new vector this*v
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator*(const Vec4 &_v) const noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current vector to rhs
  /// @param[in] _v the vector to set
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator=(const Vec4 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current vector to rhs
  /// @param[in] _v the vector to set
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator=(const Vec3 &_v) noexcept;


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief negate the vector components
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator-() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check for equality uses FCompare (from Util.h) as float values
  /// @param[in] _v the vector to check against
  /// @returns true or false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator==(const Vec4 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief not equal check
  /// @param[in] _v the vector to check against
  /// @returns true of false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator!=(const Vec4 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief \ operator div vector/vector
  /// @param[in]  _v the value to div by
  /// @returns Vector / Vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator/(const Vec4 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the angle between current vector and _v
  /// @param[in] _v the vector to check
  /// @returns the angle between the two vectors in degrees
  //----------------------------------------------------------------------------------------------------------------------
  Real angleBetween(const Vec4 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the inner product of this vector and vector passed in
  /// @param[in] _v the vector to calculate inner product with
  /// @returns the inner product
  //----------------------------------------------------------------------------------------------------------------------
  Real inner(const Vec4 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compute the outer product of this vector and vector
  /// @param[in] _v the vector to calc against
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Mat4 outer(const Vec4 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the length squared of the vector
  /// @returns length squared
  //----------------------------------------------------------------------------------------------------------------------
  Real lengthSquared() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator to multiply a vector by a matrix
  /// @param[in] _m the matrix to multiply
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator*(const Mat4 &_m) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the m_openGL matrix returns the address of the 0th element
  //----------------------------------------------------------------------------------------------------------------------
  Real *openGL() noexcept
  {
    return &m_openGL[0];
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clamp the vector values between _min and _max
  /// @param[in]  _min value
  /// @param[in]  _max value
  //----------------------------------------------------------------------------------------------------------------------
  void clamp(float _min, float _max) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clamp the vector values between +/-_max
  /// @param[in]  _max value
  //----------------------------------------------------------------------------------------------------------------------
  void clamp(float _max) noexcept;

  static Vec4 up()
  {
    return Vec4(0.0f, 1.0f, 0.0f, 0.0f);
  }
  static Vec4 down()
  {
    return Vec4(0.0f, -1.0f, 0.0f, 0.0f);
  }

  static Vec4 left()
  {
    return Vec4(-1.0f, 0.0f, 0.0f, 0.0f);
  }
  static Vec4 right()
  {
    return Vec4(1.0f, 0.0f, 0.0f, 0.0f);
  }

  static Vec4 in()
  {
    return Vec4(0.0f, 0.0f, 1.0f, 0.0f);
  }
  static Vec4 out()
  {
    return Vec4(0.0f, 0.0f, -1.0f, 0.0f);
  }

  static Vec4 zero()
  {
    return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
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
      Real m_x; //!< x component
      Real m_y; //!< y component
      Real m_z; //!< z component
      Real m_w; //!< w component 0 for vector 1 for point
    };
    struct
    {
      Real m_r; //!< r component
      Real m_g; //!< g component
      Real m_b; //!< b component
      Real m_a; //!< a component
    };
    std::array< Real, 4 > m_openGL={0.0f,0.0f,0.0f,1.0f};
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
inline Vec4 operator*(Real _k, const Vec4 &_v) noexcept
{
  return Vec4(_k * _v.m_x, _k * _v.m_y, _k * _v.m_z, _v.m_w);
}

} // namespace ngl
#endif

//----------------------------------------------------------------------------------------------------------------------
