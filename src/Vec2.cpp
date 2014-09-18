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
#include "Vec2.h"
#include "Vec4.h"
#include "NGLassert.h"
#include <boost/format.hpp>
#include <cmath>
//----------------------------------------------------------------------------------------------------------------------
/// @file Vec2.cpp
/// @brief implementation files for Vec2 class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
void Vec2::set(Real _x, Real _y)
{
	m_x=_x;
	m_y=_y;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec2::set(const Vec2& _v  )
{
   m_x=_v.m_x;
   m_y=_v.m_y;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec2::set(const Vec2* _v	)
{
	m_x=_v->m_x;
	m_y=_v->m_y;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec2::null()
{
	m_x=0.0f;
	m_y=0.0f;
}

//----------------------------------------------------------------------------------------------------------------------
Real& Vec2::operator[]( int _i)
{
	NGL_ASSERT(_i >=0 || _i<=2);
	return (&m_x)[_i];
}



//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator-() const
{
	return Vec2(-m_x,-m_y);
}


//----------------------------------------------------------------------------------------------------------------------
void Vec2::operator+=(const Vec2& _v  )
{
	m_x+=_v.m_x;
	m_y+=_v.m_y;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec2::operator/=(Real _v  )
{
	NGL_ASSERT(_v !=0);
	m_x/=_v;
	m_y/=_v;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec2::operator*=(Real _v)
{
	m_x*=_v;
	m_y*=_v;
}
//----------------------------------------------------------------------------------------------------------------------
void Vec2::operator-=(const Vec2& _v )
{
	m_x-=_v.m_x;
	m_y-=_v.m_y;
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator/( Real _v )const
{
	return Vec2(
								m_x/_v,
								m_y/_v
								);
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator+(const Vec2& _v )const
{
	return Vec2(
								m_x+_v.m_x,
								m_y+_v.m_y
							);
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator-( const Vec2& _v  )const
{
	return Vec2(m_x-_v.m_x,	m_y-_v.m_y );
}

//----------------------------------------------------------------------------------------------------------------------
bool Vec2::operator==(const Vec2& _v )const
{
	return (
					FCompare(_v.m_x,m_x)  &&
					FCompare(_v.m_y,m_y)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
bool Vec2::operator!=(const Vec2& _v  )const
{
	return (
					!FCompare(_v.m_x,m_x) ||
					!FCompare(_v.m_y,m_y)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator*(const Vec2& _v  )const
{
	return Vec2(
								m_x*_v.m_x,
								m_y*_v.m_y
							);
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator/( const Vec2& _v )const
{
	return Vec2(
								m_x/_v.m_x,
								m_y/_v.m_y
							);
}

//----------------------------------------------------------------------------------------------------------------------
Vec2 Vec2::operator *(Real _i )const
{
	return Vec2(
								m_x*_i,
								m_y*_i
							 );
}



//----------------------------------------------------------------------------------------------------------------------
Vec2 & Vec2::operator=(const Vec2& _v)
{
	m_x = _v.m_x;
	m_y = _v.m_y;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
void Vec2::normalize()
{
  Real len=(Real)sqrt(m_x*m_x+m_y*m_y);
  NGL_ASSERT(len!=0);
  m_x/=len;
  m_y/=len;
}






Real Vec2::dot(const Vec2& _v )const
{
  return m_x * _v.m_x + m_y * _v.m_y;
}


//----------------------------------------------------------------------------------------------------------------------
Real Vec2::lengthSquared() const
{
  return (Real)(m_x*m_x)+(m_y*m_y);
}






//----------------------------------------------------------------------------------------------------------------------
Real Vec2::length() const
{
	return (Real)sqrt((m_x*m_x)+(m_y*m_y));
}



} // end namspace ngl



