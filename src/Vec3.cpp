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
#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "NGLassert.h"
#include <cmath>
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec3.cpp
/// @brief implementation files for Vec3 class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{




//----------------------------------------------------------------------------------------------------------------------
void Vec3::set(Real _x,   Real _y,  Real _z ) noexcept
{
	m_x=_x;
	m_y=_y;
	m_z=_z;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec3::set( const Vec3& _v ) noexcept
{
   m_x=_v.m_x;
   m_y=_v.m_y;
   m_z=_v.m_z;
}
void Vec3::set( const Vec4& _v ) noexcept
{
   m_x=_v.m_x;
   m_y=_v.m_y;
   m_z=_v.m_z;
}

//----------------------------------------------------------------------------------------------------------------------
Real Vec3::dot( const Vec3& _v  )const noexcept
{
	return m_x * _v.m_x + m_y * _v.m_y + m_z * _v.m_z;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec3::null() noexcept
{
	m_x=0.0f;
	m_y=0.0f;
	m_z=0.0f;
}

//----------------------------------------------------------------------------------------------------------------------
Real& Vec3::operator[](const int& _i ) noexcept
{
	NGL_ASSERT(_i >=0 || _i<=3);
	return (&m_x)[_i];
}



//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator-() const noexcept
{
	return Vec3(-m_x,-m_y,-m_z);
}


//----------------------------------------------------------------------------------------------------------------------
void Vec3::operator+=(const Vec3& _v) noexcept
{
	m_x+=_v.m_x;
	m_y+=_v.m_y;
	m_z+=_v.m_z;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec3::operator/=(Real _v) noexcept
{
  NGL_ASSERT(_v !=0.0f);
	m_x/=_v;
	m_y/=_v;
	m_z/=_v;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec3::operator*=(Real _v) noexcept
{
	m_x*=_v;
	m_y*=_v;
	m_z*=_v;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec3::operator-=(const Vec3& _v) noexcept
{
	m_x-=_v.m_x;
	m_y-=_v.m_y;
	m_z-=_v.m_z;
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator/(Real _v)const noexcept
{
	return Vec3(m_x/_v,m_y/_v,m_z/_v);
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator+( const Vec3& _v)const noexcept
{
	return Vec3(m_x+_v.m_x,m_y+_v.m_y,m_z+_v.m_z);
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator-(const Vec3& _v)const noexcept
{
	return Vec3(m_x-_v.m_x,m_y-_v.m_y,m_z-_v.m_z);
}

//----------------------------------------------------------------------------------------------------------------------
bool Vec3::operator==(const Vec3& _v)const noexcept
{
	return (
					FCompare(_v.m_x,m_x)  &&
					FCompare(_v.m_y,m_y)  &&
					FCompare(_v.m_z,m_z)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
bool Vec3::operator!=(const Vec3& _v  )const noexcept
{
	return (
					!FCompare(_v.m_x,m_x) ||
					!FCompare(_v.m_y,m_y) ||
					!FCompare(_v.m_z,m_z)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator*( const Vec3& _v  )const noexcept
{
	return Vec3(m_x*_v.m_x,m_y*_v.m_y,m_z*_v.m_z );
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator/( const Vec3& _v )const noexcept
{
	return Vec3(m_x/_v.m_x,m_y/_v.m_y,m_z/_v.m_z);
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator *(Real _i)const noexcept
{
	return Vec3(m_x*_i,m_y*_i,m_z*_i);
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 & Vec3::operator=(Real _v) noexcept
{
  m_x = _v;
  m_y = _v;
  m_z = _v;
  return *this;
}


//----------------------------------------------------------------------------------------------------------------------
Vec3 & Vec3::operator=(const Vec4& _v) noexcept
{
  m_x = _v.m_x;
  m_y = _v.m_y;
  m_z = _v.m_z;
  return *this;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec3::cross(const Vec3& _v1, const Vec3& _v2) noexcept
{
  m_x=_v1.m_y*_v2.m_z-_v1.m_z*_v2.m_y;
  m_y=_v1.m_z*_v2.m_x-_v1.m_x*_v2.m_z;
  m_z=_v1.m_x*_v2.m_y-_v1.m_y*_v2.m_x;
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::cross( const Vec3& _v )const noexcept
{
  return Vec3(m_y*_v.m_z - m_z*_v.m_y,
              m_z*_v.m_x - m_x*_v.m_z,
              m_x*_v.m_y - m_y*_v.m_x
             );

}


//----------------------------------------------------------------------------------------------------------------------
void Vec3::normalize() noexcept
{
  Real len=sqrtf(m_x*m_x+m_y*m_y+m_z*m_z);
  NGL_ASSERT(len!=0.0f);
  m_x/=len;
  m_y/=len;
  m_z/=len;
}

//----------------------------------------------------------------------------------------------------------------------
Real Vec3::inner( const Vec3& _v  )const noexcept
{
  return ((m_x * _v.m_x) +(m_y * _v.m_y) + (m_z * _v.m_z));
}



Mat3 Vec3::outer(const Vec3 &_v  )  const noexcept
{
  return Mat3(
              m_x * _v.m_x, m_x * _v.m_y, m_x * _v.m_z,
              m_y * _v.m_x, m_y * _v.m_y, m_y * _v.m_z,
              m_z * _v.m_x, m_z * _v.m_y, m_z * _v.m_z
            );
}

//----------------------------------------------------------------------------------------------------------------------
Real Vec3::length() const noexcept
{
  return sqrtf((m_x*m_x)+(m_y*m_y)+(m_z*m_z));
}


//----------------------------------------------------------------------------------------------------------------------
Real Vec3::lengthSquared() const noexcept
{
  return m_x * m_x+m_y * m_y+ m_z*m_z;
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Vec3::operator*(const Mat3 &_m) const noexcept
{


	 Vec3 v(
					m_x*_m.m_00 + m_y*_m.m_10 + m_z*_m.m_20,
					m_x*_m.m_01 + m_y*_m.m_11 + m_z*_m.m_21,
					m_x*_m.m_02 + m_y*_m.m_12 + m_z*_m.m_22
				 );


   return v;
 }

Vec3 Vec3::reflect(const Vec3 & _n) const noexcept
{
 float d=this->dot(_n);
 //  I - 2.0 * dot(N, I) * N
 return Vec3( m_x-2.0f*d*_n.m_x, m_y-2.0f*d*_n.m_y, m_z-2.0f*d*_n.m_z);
}

void Vec3::clamp(float _min, float _max ) noexcept
{
  m_x<_min ? m_x = _min : m_x;
  m_x>_max ? m_x = _max : m_x;

  m_y<_min ? m_y = _min : m_y;
  m_y>_max ? m_y = _max : m_y;

  m_z<_min ? m_z = _min : m_z;
  m_z>_max ? m_z = _max : m_z;


}
void Vec3::clamp(float _max ) noexcept
{
  m_x<-_max ? m_x = -_max : m_x;
  m_x>_max ? m_x = _max : m_x;

  m_y<-_max ? m_y = -_max : m_y;
  m_y>_max ? m_y = _max : m_y;

  m_z<-_max ? m_z = -_max : m_z;
  m_z>_max ? m_z = _max : m_z;


}

} // end namspace ngl



