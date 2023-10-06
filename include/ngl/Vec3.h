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
#ifndef VEC3_H_
#define VEC3_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec3.h
/// @brief a simple 3 tuple container for compatibility with glsl
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include <array>
#ifdef USEGLM
#include <glm/vec3.hpp>
#endif

//----------------------------------------------------------------------------------------------------------------------
/// @file Vec3.h
/// @brief encapsulates a 3 float object like glsl vec3 but not maths
/// use the Vec3 class for maths and the asVec3 to return a vec3
/// @author Jonathan Macey
/// @version 1.0
/// @date 20/6/11 initial version
/// Revision History :
/// Initial Version 20/6/11
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
// pre-declare the vector class
class Vec4;
class Mat3;

//----------------------------------------------------------------------------------------------------------------------
/// @class Vec3 "include/Vec3.h"
/// @brief simple Vec3 encapsulates a 3 float object like glsl vec3 but not maths
/// use the Vec3 class for maths and the asVec3 to return a vec3
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT Vec3
{

    public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor use default and set to (0.0f,0.0f,0.0f) as attributes are initialised
  //----------------------------------------------------------------------------------------------------------------------
  Vec3() = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor we have POD data so let the compiler do the work!
  //----------------------------------------------------------------------------------------------------------------------
  Vec3(const Vec3 &_v) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialise the constructor from 3 floats
  /// @param[in]  _x x value
  /// @param[in]  _y y value
  /// @param[in]  _z z value
  //----------------------------------------------------------------------------------------------------------------------
  Vec3(Real _x, Real _y, Real _z) noexcept
    : m_x(_x), m_y(_y), m_z(_z)
  {
  }
#ifdef USEGLM
  Vec3(const glm::vec3 &_v) noexcept
    : m_x(_v.x), m_y(_v.y), m_z(_v.z)
  {
    ;
  }
  glm::vec3 toGLM() const
  {
    return glm::vec3(m_x, m_y, m_z);
  }
  void set(const glm::vec3 &_r)
  {
    m_x = _r.x;
    m_y = _r.y;
    m_z = _r.z;
  }

#endif

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the Vec3 component from 3 values
  /// @param[in]  _x the x component
  /// @param[in]  _y the y component
  /// @param[in]  _z the z component
  //----------------------------------------------------------------------------------------------------------------------
  void set(Real _x, Real _y, Real _z) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec3
  /// @param[in]  _v the Vec3 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(const Vec3 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  Vec4 ( you may need to convert somtimes)
  /// @param[in]  _v the Vec4 to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set(const Vec4 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return this dotted with _b
  /// @param[in]  _b vector to dot current vector with
  /// @returns  the dot product
  //----------------------------------------------------------------------------------------------------------------------
  Real dot(const Vec3 &_b) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clears the Vec3 to 0,0,0
  //----------------------------------------------------------------------------------------------------------------------
  void null() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] index operator to access the index component of the Vec3
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  Real &operator[](const size_t &_i) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] const index operator to access the index component of the Vec3
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  const Real &operator[](const size_t &_i) const noexcept
  {
    return m_openGL[_i];
  }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Normalize the vector using
  /// \n \f$x=x/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$y=y/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$z=z/\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  void normalize() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the inner product of this vector and vector passed in
  /// @param[in] _v the vector to calculate inner product with
  /// @returns the inner product
  //----------------------------------------------------------------------------------------------------------------------
  Real inner(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compute the outer product of this vector and vector (requested by PJ)
  /// @param[in] _v the vector to calc against
  /// @returns a mat 3
  //----------------------------------------------------------------------------------------------------------------------

  Mat3 outer(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length of the vector
  /// @returns  \f$\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Real length() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length squared of the vector (no sqrt so quicker)
  /// @returns  \f$x^2+y^2+z^2 \f$
  //----------------------------------------------------------------------------------------------------------------------
  Real lengthSquared() const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator add Vec3 v to current Vec3
  /// @param[in]  &_v Vec3 to add
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator+=(const Vec3 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief -= operator this-=v
  /// @param[in]  &_v Vec3 to subtract
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator-=(const Vec3 &_v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this * i for each element
  /// @param[in]  _i the scalar to mult by
  /// @returns Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator*(Real _i) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator add Vec3+Vec3
  /// @param[in]  &_v the value to add
  /// @returns the Vec3 + v
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator+(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide Vec3 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// @returns a Vec3 V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator/(Real _v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide this Vec3 components by a scalar
  /// @param[in] _v the scalar to divide by
  /// sets the Vec3 to Vec3 V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator/=(Real _v) noexcept;
  Vec3 &operator/=(const Vec3 &_v) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this Vec3 components by a scalar
  /// @param[in] _v the scalar to multiply by
  /// sets the Vec3 to Vec3 V(x*v,y*v,z*v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator*=(Real _v) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief subtraction operator subtract vevtor-Vec3
  /// @param[in]  &_v the value to sub
  /// @returns this - v
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator-(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator mult vevtor*Vec3
  /// @param[in]  _v the value to mult
  /// @returns new Vec3 this*v
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator*(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current Vec3 to rhs
  /// @param[in] _v the Vec3 to set
  /// @returns a new Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator=(const Vec3 &_v) = default;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current Vec4 to rhs
  /// @param[in] _v the Vec3 to set
  /// @returns a new Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 &operator=(const Vec4 &_v) noexcept;


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator to multiply a vector by a matrix
  /// @param[in] _m the matrix to multiply
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator*(const Mat3 &_m) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief negate the Vec3 components
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator-() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check for equality uses FCompare (from Util.h) as float values
  /// @param[in] _v the Vec3 to check against
  /// @returns true or false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator==(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief not equal check
  /// @param[in] _v the Vec3 to check against
  /// @returns true of false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator!=(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief \ operator div Vec3/Vec3
  /// @param[in]  _v the value to div by
  /// @returns Vec3 / Vec3
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 operator/(const Vec3 &_v) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the Vec3 as the cross product from 2 other Vec3
  /// @param[in]  _v1 the first vector
  /// @param[in]  _v2 the second vector
  //----------------------------------------------------------------------------------------------------------------------
  void cross(const Vec3 &_v1, const Vec3 &_v2) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the cross product of this cross with b
  /// @param[in]  _b the vector cross this with
  /// @returns  the result of this cross b
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 cross(const Vec3 &_b) const noexcept;
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
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the vector reflected with this and N
  /// @param[in]  _n the normal vector
  /// @returns  the reflection vector of this with N
  //----------------------------------------------------------------------------------------------------------------------
  Vec3 reflect(const Vec3 &_n) const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the m_openGL array returns the address of the 0th element
  //----------------------------------------------------------------------------------------------------------------------
  inline Real *openGL() noexcept
  {
    return &m_openGL[0];
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return Y up vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 up()
  {
    return Vec3(0.0f, 1.0f, 0.0f);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return Y down vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 down()
  {
    return Vec3(0.0f, -1.0f, 0.0f);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return X left vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 left()
  {
    return Vec3(-1.0f, 0.0f, 0.0f);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return X right vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 right()
  {
    return Vec3(1.0f, 0.0f, 0.0f);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return Z out vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 in()
  {
    return Vec3(0.0f, 0.0f, 1.0f);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return Z in vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 out()
  {
    return Vec3(0.0f, 0.0f, -1.0f);
  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief simple static method to return zero vector
  //----------------------------------------------------------------------------------------------------------------------
  static Vec3 zero()
  {
    return Vec3(0.0f, 0.0f, 0.0f);
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
    };
    struct
    {
      Real m_r; //!< r component
      Real m_g; //!< g component
      Real m_b; //!< b component
    };
    std::array< Real, 3 > m_openGL={0.0f,0.0f,0.0f};
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
inline Vec3 operator*(Real _k, const Vec3 &_v) noexcept
{
  return Vec3(_k * _v.m_x, _k * _v.m_y, _k * _v.m_z);
}

} // end namespace ngl
#endif

//----------------------------------------------------------------------------------------------------------------------
