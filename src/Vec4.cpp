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
#include "Vec4.h"
#include "Vec3.h"
#include "Vec2.h"

#include "NGLassert.h"
#include "Mat4.h"
#include <cmath>



//----------------------------------------------------------------------------------------------------------------------
/// @file Vec3.cpp
/// @brief implementation files for Vec3 class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{



//----------------------------------------------------------------------------------------------------------------------
Real Vec4::dot(const Vec4& _v )const noexcept
{
	return m_x * _v.m_x + m_y * _v.m_y + m_z * _v.m_z;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec4::set( Real _x, Real _y, Real _z, Real _w) noexcept
{
	m_x=_x;
	m_y=_y;
	m_z=_z;
	m_w=_w;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec4::set( const Vec4& _v) noexcept
{
   m_x=_v.m_x;
   m_y=_v.m_y;
   m_z=_v.m_z;
   m_w=_v.m_w;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec4::set( const Vec3 &_v ) noexcept
{
  m_x=_v.m_x;
  m_y=_v.m_y;
  m_z=_v.m_z;
  m_w=1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec4::null() noexcept
{
	m_x=0.0f;
	m_y=0.0f;
	m_z=0.0f;
	m_w=1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
Real& Vec4::operator[](const size_t  &_i ) noexcept
{
  NGL_ASSERT(_i<=3)
	return (&m_x)[_i];
}

//----------------------------------------------------------------------------------------------------------------------
Real Vec4::length() const noexcept
{
  return sqrtf((m_x*m_x)+(m_y*m_y)+(m_z*m_z));
}


//----------------------------------------------------------------------------------------------------------------------
Vec4 &Vec4::operator-() noexcept
{
  m_x=-m_x;
  m_y=-m_y;
  m_z=-m_z;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 &Vec4::normalize() noexcept
{
  Real len=sqrtf(m_x*m_x+m_y*m_y+m_z*m_z);
  NGL_ASSERT(len!=0.0f)
	m_x/=len;
	m_y/=len;
	m_z/=len;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec4::cross( const Vec4& _v1, const Vec4& _v2) noexcept
{
	m_x=_v1.m_y*_v2.m_z-_v1.m_z*_v2.m_y;
	m_y=_v1.m_z*_v2.m_x-_v1.m_x*_v2.m_z;
	m_z=_v1.m_x*_v2.m_y-_v1.m_y*_v2.m_x;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::cross(const Vec4& _v )const noexcept
{
	return Vec4(
								m_y*_v.m_z - m_z*_v.m_y,
								m_z*_v.m_x - m_x*_v.m_z,
								m_x*_v.m_y - m_y*_v.m_x,
								0.0f
							 );

}

//----------------------------------------------------------------------------------------------------------------------
Vec4& Vec4::operator+=( const Vec4& _v) noexcept
{
	m_x+=_v.m_x;
	m_y+=_v.m_y;
	m_z+=_v.m_z;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4& Vec4::operator/=(Real _v) noexcept
{
  NGL_ASSERT(_v !=0.0f)
	m_x/=_v;
	m_y/=_v;
	m_z/=_v;
  return *this;
}


Vec4& Vec4::operator/=(const Vec4 &_v) noexcept
{
  NGL_ASSERT(_v.m_x !=0.0f && _v.m_y !=0.0f && _v.m_z !=0.0f)
  m_x/=_v.m_x;
  m_y/=_v.m_y;
  m_z/=_v.m_y;
  return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Vec4& Vec4::operator*=(Real _v) noexcept
{
	m_x*=_v;
	m_y*=_v;
	m_z*=_v;
  return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Vec4& Vec4::operator-=( const Vec4& _v) noexcept
{
	m_x-=_v.m_x;
	m_y-=_v.m_y;
	m_z-=_v.m_z;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator/(Real _v )const noexcept
{
	return Vec4(m_x/_v,m_y/_v,m_z/_v,m_w);
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator+(const Vec4& _v )const noexcept
{
	return Vec4(
								m_x+_v.m_x,
								m_y+_v.m_y,
								m_z+_v.m_z,
								m_w
								);
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator-(const Vec4& _v )const noexcept
{
	return Vec4(
								m_x-_v.m_x,
								m_y-_v.m_y,
								m_z-_v.m_z,
								m_w
							 );
}

//----------------------------------------------------------------------------------------------------------------------
bool Vec4::operator==(const Vec4& _v   )const noexcept
{
	return (
					FCompare(_v.m_x,m_x)  &&
					FCompare(_v.m_y,m_y)  &&
					FCompare(_v.m_z,m_z)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
bool Vec4::operator!=( const Vec4& _v  )const noexcept
{
	return (
					!FCompare(_v.m_x,m_x) ||
					!FCompare(_v.m_y,m_y) ||
					!FCompare(_v.m_z,m_z)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator*( const Vec4& _v )const noexcept
{
	return Vec4(
								m_x*_v.m_x,
								m_y*_v.m_y,
								m_z*_v.m_z,
								m_w
							 );
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator/(const Vec4& _v )const noexcept
{
	return Vec4(
								m_x/_v.m_x,
								m_y/_v.m_y,
								m_z/_v.m_z,
								m_w
								);
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator *( Real _i )const noexcept
{
	return Vec4(
								m_x*_i,
								m_y*_i,
								m_z*_i,
								m_w
							 );
}

//----------------------------------------------------------------------------------------------------------------------
Real Vec4::angleBetween( const Vec4& _v  )const noexcept
{
 // uses cos(t) = |a| . |b|
// create tmp Vec3s so we don't have to
// normalize existing ones
  Vec4 v1 = _v;
  Vec4 v2 = *this;
  v1.normalize();
  v2.normalize();
  return acosf(v1.dot(v2));
}

//----------------------------------------------------------------------------------------------------------------------
Real Vec4::inner(const Vec4& _v  )const noexcept
{
	return (
					(m_x * _v.m_x) +
					(m_y * _v.m_y) +
					(m_z * _v.m_z)
				 );
}

//----------------------------------------------------------------------------------------------------------------------
Mat4 Vec4::outer(const Vec4& _v  )  const noexcept
{
  return Mat4(
              m_x * _v.m_x, m_x * _v.m_y, m_x * _v.m_z, m_x * _v.m_w,
              m_y * _v.m_x, m_y * _v.m_y, m_y * _v.m_z, m_y * _v.m_w,
              m_z * _v.m_x, m_z * _v.m_y, m_z * _v.m_z, m_z * _v.m_w,
              m_w * _v.m_x, m_w * _v.m_y, m_w * _v.m_z, m_w * _v.m_w
            );

}


//----------------------------------------------------------------------------------------------------------------------
Vec4 & Vec4::operator=( const Vec4& _v) noexcept
{
	m_x = _v.m_x;
	m_y = _v.m_y;
	m_z = _v.m_z;
	m_w = _v.m_w;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 & Vec4::operator=( const Vec3& _v) noexcept
{
  m_x = _v.m_x;
  m_y = _v.m_y;
  m_z = _v.m_z;
  m_w = 0.0f;
  return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 & Vec4::operator=( Real _v) noexcept
{
  m_x = _v;
  m_y = _v;
  m_z = _v;
  m_w = 0.0f;
  return *this;
}


//----------------------------------------------------------------------------------------------------------------------
Real Vec4::lengthSquared() const noexcept
{
  return m_x * m_x+m_y * m_y+ m_z*m_z;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Vec4::operator*(const Mat4 &_m ) const noexcept
{
/*
	 Vec4 v(
						m_x*_m.m_00 + m_y*_m.m_10 + m_z*_m.m_20+ m_w*_m.m_30,
						m_x*_m.m_01 + m_y*_m.m_11 + m_z*_m.m_21+ m_w*_m.m_31,
						m_x*_m.m_02 + m_y*_m.m_12 + m_z*_m.m_22+ m_w*_m.m_32,
						m_x*_m.m_03 + m_y*_m.m_13 + m_z*_m.m_23+ m_w*_m.m_33
				 );

   return v;
*/
  Vec4 temp;

  temp.m_x=m_x * _m.m_00 + m_y	* _m.m_01 + m_z * _m.m_02 + m_w * _m.m_03;
  temp.m_y=m_x * _m.m_10 + m_y	* _m.m_11 + m_z * _m.m_12 + m_w * _m.m_13;
  temp.m_z=m_x * _m.m_20 + m_y	* _m.m_21 + m_z * _m.m_22 + m_w * _m.m_23;
  temp.m_w=m_x * _m.m_30 + m_y	* _m.m_31 + m_z * _m.m_32 + m_w * _m.m_33;

return temp;
}

void Vec4::clamp(float _min, float _max ) noexcept
{
  m_x<_min ? m_x = _min : m_x;
  m_x>_max ? m_x = _max : m_x;

  m_y<_min ? m_y = _min : m_y;
  m_y>_max ? m_y = _max : m_y;

  m_z<_min ? m_z = _min : m_z;
  m_z>_max ? m_z = _max : m_z;
}

void Vec4::clamp(float _max ) noexcept
{
  m_x<-_max ? m_x = -_max : m_x;
  m_x>_max ? m_x = _max : m_x;

  m_y<-_max ? m_y = -_max : m_y;
  m_y>_max ? m_y = _max : m_y;

  m_z<-_max ? m_z = -_max : m_z;
  m_z>_max ? m_z = _max : m_z;


}

} // end namspace ngl



