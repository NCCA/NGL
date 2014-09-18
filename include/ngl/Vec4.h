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
#ifndef VECTOR_H__
#define VECTOR_H__
//----------------------------------------------------------------------------------------------------------------------
/// @file Vector.h
/// @brief a simple 4D vector class
//----------------------------------------------------------------------------------------------------------------------
// part of the python bindings
#ifdef NO_PYTHON_LIB
  #include <boost/python.hpp>
  #include <boost/format.hpp>
#endif

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec2.h"
#include "Vec3.h"

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

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec4(  const Vec4& _v ) :
  m_x(_v.m_x),
  m_y(_v.m_y),
  m_z(_v.m_z),
  m_w(_v.m_w){;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief copy ctor
  /// @param[in] _v the value to set
  //----------------------------------------------------------------------------------------------------------------------
  Vec4(  const Vec3& _v  ) :
  m_x(_v.m_x),
  m_y(_v.m_y),
  m_z(_v.m_z),
  m_w(1.0){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief initialise the constructor from 3 or 4 Real
  /// @param[in]  _x x value
  /// @param[in]  _y y value
  /// @param[in]  _z z value
  /// @param[in]  _w 1.0f default so acts as a points
  //----------------------------------------------------------------------------------------------------------------------
   Vec4( Real _x=0.0, Real _y=0.0, Real _z=0.0,  Real _w=1.0f ):
   m_x(_x),
   m_y(_y),
   m_z(_z),
   m_w(_w){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return this dotted with _b
  /// @param[in]  _b vector to dot current vector with
  /// @returns  the dot product
  //----------------------------------------------------------------------------------------------------------------------
  Real dot( const Vec4 &_b )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the vector component from 3 values
  /// @param[in]  _x the x component
  /// @param[in]  _y the y component
  /// @param[in]  _z the z component
  /// @param[in]  _w the w component default to 1 for a point
  //----------------------------------------------------------------------------------------------------------------------
  void set(Real _x, Real _y,  Real _z, Real _w=1.0  );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  vector
  /// @param[in]  _v the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set( const Vec4& _v );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set from another  vector
  /// @param[in]  _v the vector to set from
  //----------------------------------------------------------------------------------------------------------------------
  void set( const Vec3 &_v );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief clears the vector to 0,0,0,1
  //----------------------------------------------------------------------------------------------------------------------
  void null();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get as a Vec3 for glsl etc
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec3 toVec3() const { return Vec3(m_x,m_y,m_z);}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get as a Vec2 for glsl etc
  //----------------------------------------------------------------------------------------------------------------------
  inline Vec2 toVec2() const { return Vec2(m_x,m_y);}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief [] index operator to access the index component of the vector
  /// @returns  this[x] as a Real
  //----------------------------------------------------------------------------------------------------------------------
  Real& operator[](  int _i  ) ;
  const Real& operator[](  int _i ) const { return m_openGL[_i]; }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the length of the vector
  /// @returns  \f$\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Real length() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  negate the vector (make all components the negative)
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &negate();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Normalize the vector using
  /// \n \f$x=x/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$y=y/\sqrt{x^2+y^2+z^2} \f$
  /// \n \f$z=z/\sqrt{x^2+y^2+z^2} \f$
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &normalize();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the vector as the cross product from 2 other vectors
  /// @param[in]  _v1 the first vector
  /// @param[in]  _v2 the second vector
  //----------------------------------------------------------------------------------------------------------------------
  void cross(const Vec4& _v1, const Vec4& _v2  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief return the cross product of this cross with b
  /// @param[in]  _b the vector cross this with
  /// @returns  the result of this cross b
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 cross(const Vec4& _b   )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief += operator add vector v to current vector
  /// @param[in]  &_v vector to add
  //----------------------------------------------------------------------------------------------------------------------
  void operator+=( const Vec4& _v );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief -= operator this-=v
  /// @param[in]  &_v vector to subtract
  //----------------------------------------------------------------------------------------------------------------------
  void operator-=(const Vec4& _v );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this * i for each element
  /// @param[in]  _i the scalar to mult by
  /// @returns Vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator *(  Real _i )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief + operator add vector+vector
  /// @param[in]  &_v the value to add
  /// @returns the vector + v
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator +(const Vec4 &_v  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide vector components by a scalar
  /// @param[in] _v the scalar to divide by
  /// @returns a vector V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator/(Real _v )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief divide this vector components by a scalar
  /// @param[in] _v the scalar to divide by
  /// sets the vector to vector V(x/v,y/v,z/v,w)
  //----------------------------------------------------------------------------------------------------------------------
  void operator/=(Real _v  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief multiply this vector components by a scalar
  /// @param[in] _v the scalar to multiply by
  /// sets the vector to vector V(x*v,y*v,z*v,w)
  //----------------------------------------------------------------------------------------------------------------------
  void operator*=( Real _v );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief subtraction operator subtract vevtor-vector
  /// @param[in]  &_v the value to sub
  /// @returns this - v
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator-(const Vec4& _v )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief * operator mult vevtor*vector
  /// @param[in]  _v the value to mult
  /// @returns new vector this*v
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator*( const Vec4 &_v  )const;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current vector to rhs
  /// @param[in] _v the vector to set
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator =( const Vec4 &_v   );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current vector to rhs
  /// @param[in] _v the vector to set
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator =(
                     const Vec3 &_v
                    );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator set the current vector to rhs
  /// @param[in] _v the vector to set
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator =( Real _v  );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief negate the vector components
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 &operator-();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief check for equality uses FCompare (from Util.h) as float values
  /// @param[in] _v the vector to check against
  /// @returns true or false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator==( const Vec4 &_v )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief not equal check
  /// @param[in] _v the vector to check against
  /// @returns true of false
  //----------------------------------------------------------------------------------------------------------------------
  bool operator!=(  const Vec4 &_v  )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief \ operator div vector/vector
  /// @param[in]  _v the value to div by
  /// @returns Vector / Vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator/( const Vec4& _v   )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the angle between current vector and _v
  /// @param[in] _v the vector to check
  /// @returns the angle between the two vectors in degrees
  //----------------------------------------------------------------------------------------------------------------------
  Real angleBetween( const Vec4 &_v  )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the inner product of this vector and vector passed in
  /// @param[in] _v the vector to calculate inner product with
  /// @returns the inner product
  //----------------------------------------------------------------------------------------------------------------------
  Real inner( const Vec4& _v  )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compute the outer product of this vector and vector
  /// @param[in] _v the vector to calc against
  /// @returns a new vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 outer(const Vec4& _v  )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief calculate the length squared of the vector
  /// @returns length squared
  //----------------------------------------------------------------------------------------------------------------------
  Real lengthSquared() const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief operator to multiply a vector by a matrix
  /// @param[in] _m the matrix to multiply
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 operator*( const Mat4 &_m  )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief accesor to the m_openGL matrix returns the address of the 0th element
  //----------------------------------------------------------------------------------------------------------------------
  inline Real* openGL(){return &m_openGL[0];}
/// @note I've made this public as some compilers automatically make the
/// anonymous unions public whereas clang++ complains see this post
/// http://jonmacey.blogspot.com/2011/03/anonymous-union-struct-weirdness.html
public :
#pragma pack(push,1)

#ifndef BUILDING_DOCS
  union
  {
    struct
    {
#endif
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief x component of the vector
      //----------------------------------------------------------------------------------------------------------------------
      Real m_x;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief y component of the vector
      //----------------------------------------------------------------------------------------------------------------------
      Real m_y;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief z component of the vector
      //----------------------------------------------------------------------------------------------------------------------
      Real m_z;
      //----------------------------------------------------------------------------------------------------------------------
      /// @brief w component of the vector 0= Vector 1=Point
      //----------------------------------------------------------------------------------------------------------------------
      Real m_w;
#ifndef BUILDING_DOCS
    };
#endif
#pragma pack(pop)
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief array of four floats mapped to the x,y,z,w components of the vector useful for openGL fv data types
  /// this is mapped as a union to the following \n
  /// m_x == m_openGL[0] \n
  /// m_y == m_openGL[1] \n
  /// m_z == m_openGL[2] \n
  /// m_w == m_openGL[3] \n
  //----------------------------------------------------------------------------------------------------------------------

  Real m_openGL[4];
#ifndef BUILDING_DOCS
  };
#endif
/// extra glue for python lib bindings nothing to see here (unless ....)
#ifdef NO_PYTHON_LIB
  public :
    std::string pyPrint();
    boost::python::tuple getOpenGL();
    bool equals( const Vec4& _x, const Vec4& _y )const ;
    Real getItem(int index);
    void setItem(int _index,Real _value);
#endif


};



//----------------------------------------------------------------------------------------------------------------------
/// @brief scalar * vector operator
/// @param _k the float value
/// @param _v the vector value
/// @returns a vector _k*v
//----------------------------------------------------------------------------------------------------------------------
inline Vec4 operator *(Real _k, const Vec4 &_v)
{
  return Vec4(_k*_v.m_x, _k*_v.m_y, _k*_v.m_z,_v.m_w);
}

}
#endif

//----------------------------------------------------------------------------------------------------------------------
