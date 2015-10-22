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

#include "Mat3.h"
#include "Mat4.h"
#include "NGLassert.h"
#include "Quaternion.h"
#include "Util.h"
#include "Vec2.h"
#include <iostream>
#include <cstring> // for memset
#include <boost/format.hpp>
//----------------------------------------------------------------------------------------------------------------------
/// @file Mat3x3.cpp
/// @brief implementation files for Mat3x3 class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Mat3::Mat3() noexcept
{
	memset(&m_m,0,sizeof(m_m));
	m_00=1.0f;
	m_11=1.0f;
	m_22=1.0f;
}

Mat3::Mat3( const Mat4 &_m ) noexcept
{
  m_00=_m.m_00;
  m_01=_m.m_01;
  m_02=_m.m_02;
  m_10=_m.m_10;
  m_11=_m.m_11;
  m_12=_m.m_12;
  m_20=_m.m_20;
  m_21=_m.m_21;
  m_22=_m.m_22;
}

Mat3::Mat3(Real _00, Real _01, Real _02, Real _10,  Real _11, Real _12,Real _20, Real _21, Real _22) noexcept
{
	m_00=_00;
	m_01=_01;
	m_02=_02;

	m_10=_10;
	m_11=_11;
	m_12=_12;
	m_20=_20;
	m_21=_21;
	m_22=_22;

}
//----------------------------------------------------------------------------------------------------------------------
Mat3::Mat3(const Mat3& _m) noexcept
{
	memcpy(m_m,&_m.m_m,sizeof(m_m));
}



//----------------------------------------------------------------------------------------------------------------------
Mat3::Mat3(const Real _m  ) noexcept
{
  memset(m_m,0,sizeof(m_m));
  m_00=_m;
  m_11=_m;
  m_22=_m;
}





//----------------------------------------------------------------------------------------------------------------------
/// @todo replace this with function operator overload ()
void Mat3::setAtXY( GLint _x,GLint _y, Real _equals ) noexcept
{
	m_m[_x][_y]=_equals;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat3& Mat3::null() noexcept
{
	memset(&m_m,0,sizeof(m_m));
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat3&  Mat3::identity() noexcept
{
	memset(m_m,0,sizeof(m_m));
	m_00=1.0f;
	m_11=1.0f;
	m_22=1.0f;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Mat3 Mat3::operator*(const Mat3& _m   )const noexcept
{
  Mat3 temp;

  temp.m_m[0][0] = m_m[0][0] * _m.m_m[0][0] + m_m[0][1] * _m.m_m[1][0] + m_m[0][2] * _m.m_m[2][0] ;
  temp.m_m[0][1] = m_m[0][0] * _m.m_m[0][1] + m_m[0][1] * _m.m_m[1][1] + m_m[0][2] * _m.m_m[2][1] ;
  temp.m_m[0][2] = m_m[0][0] * _m.m_m[0][2] + m_m[0][1] * _m.m_m[1][2] + m_m[0][2] * _m.m_m[2][2] ;
  temp.m_m[1][0] = m_m[1][0] * _m.m_m[0][0] + m_m[1][1] * _m.m_m[1][0] + m_m[1][2] * _m.m_m[2][0] ;
  temp.m_m[1][1] = m_m[1][0] * _m.m_m[0][1] + m_m[1][1] * _m.m_m[1][1] + m_m[1][2] * _m.m_m[2][1] ;
  temp.m_m[1][2] = m_m[1][0] * _m.m_m[0][2] + m_m[1][1] * _m.m_m[1][2] + m_m[1][2] * _m.m_m[2][2] ;
  temp.m_m[2][0] = m_m[2][0] * _m.m_m[0][0] + m_m[2][1] * _m.m_m[1][0] + m_m[2][2] * _m.m_m[2][0] ;
  temp.m_m[2][1] = m_m[2][0] * _m.m_m[0][1] + m_m[2][1] * _m.m_m[1][1] + m_m[2][2] * _m.m_m[2][1] ;
  temp.m_m[2][2] = m_m[2][0] * _m.m_m[0][2] + m_m[2][1] * _m.m_m[1][2] + m_m[2][2] * _m.m_m[2][2] ;
  return temp;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat3& Mat3::operator*= ( const Mat3 &_m ) noexcept
{
	Mat3 temp(*this);

	//  row 0
	m_00  =  temp.m_00 * _m.m_00;
	m_01  =  temp.m_01 * _m.m_00;
	m_02  =  temp.m_02 * _m.m_00;

	m_00 +=  temp.m_10 * _m.m_01;
	m_01 +=  temp.m_11 * _m.m_01;
	m_02 +=  temp.m_12 * _m.m_01;

	m_00 +=  temp.m_20 * _m.m_02;
	m_01 +=  temp.m_21 * _m.m_02;
	m_02 +=  temp.m_22 * _m.m_02;


	//  row 1
	m_10  =  temp.m_00 * _m.m_10;
	m_11  =  temp.m_01 * _m.m_10;
	m_12  =  temp.m_02 * _m.m_10;

	m_10 +=  temp.m_10 * _m.m_11;
	m_11 +=  temp.m_11 * _m.m_11;
	m_12 +=  temp.m_12 * _m.m_11;

	m_10 +=  temp.m_20 * _m.m_12;
	m_11 +=  temp.m_21 * _m.m_12;
	m_12 +=  temp.m_22 * _m.m_12;



	//  row 2
	m_20  =  temp.m_00 * _m.m_20;
	m_21  =  temp.m_01 * _m.m_20;
	m_22  =  temp.m_02 * _m.m_20;

	m_20 +=  temp.m_10 * _m.m_21;
	m_21 +=  temp.m_11 * _m.m_21;
	m_22 +=  temp.m_12 * _m.m_21;

	m_20 +=  temp.m_20 * _m.m_22;
	m_21 +=  temp.m_21 * _m.m_22;
	m_22 +=  temp.m_22 * _m.m_22;

	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Mat3 Mat3::operator+(const Mat3 &_m ) const noexcept
{
  Mat3 Ret;
        const Real* iterA = m_openGL;
        const Real* iterB = _m.m_openGL;
        Real* iterR = Ret.m_openGL;
  const Real* end   = m_openGL+9;

	for( ; iterA != end; ++iterA, ++iterB, ++iterR)
	{
		*iterR = *iterA + *iterB;
	}
	return Ret;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat3& Mat3::operator+=( const Mat3 &_m  ) noexcept
{
	Real* iterA =m_openGL;
	const Real* iterB = _m.m_openGL;
	const Real* end   = m_openGL+9;

	for( ; iterA != end; ++iterA, ++iterB)
	{
		*iterA += *iterB;
	}
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Mat3 Mat3::operator*( Real _i  ) const noexcept
{
  Mat3 ret;
        const Real* iterA = m_openGL;
        Real* iterB = ret.m_openGL;
  const Real* end   = m_openGL+9;

	for( ; iterA != end; ++iterA, ++iterB)
	{
		*iterB = (*iterA) * _i;
	}
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat3& Mat3::operator*=(Real _i) noexcept
{
	for(int y=0; y<3; y++)
	{
		for(int x=0; x<3; x++)
		{
			m_m[y][x]*=_i;
		}
	}
	return *this;
}




//----------------------------------------------------------------------------------------------------------------------
const Mat3& Mat3::transpose() noexcept
{
	Mat3 tmp(*this);

	for(int row=0; row<3; row++)
	{
		for(int col=0; col<3; col++)
		{
			m_m[row][col]=tmp.m_m[col][row];
		}
	}
	return *this;
}



//----------------------------------------------------------------------------------------------------------------------
void Mat3::rotateX( Real _deg) noexcept
{
	Real beta=radians(_deg);
	Real sr = sin( beta );
	Real cr = cos( beta );
	m_11 =  cr;
	m_21 = -sr;
	m_12 =  sr;
	m_22 =  cr;
}

//----------------------------------------------------------------------------------------------------------------------
void Mat3::rotateY(Real _deg) noexcept
{
	Real beta=radians(_deg);
	Real sr = sin( beta );
	Real cr = cos( beta );
	m_00 =  cr;
	m_20 =  sr;
	m_02 = -sr;
	m_22 =  cr;
}

//----------------------------------------------------------------------------------------------------------------------
void Mat3::rotateZ( Real _deg) noexcept
{
	Real beta=radians(_deg);
	Real sr = sin( beta );
	Real cr = cos( beta );
	m_00 =  cr;
	m_10 = -sr;
	m_01 =  sr;
	m_11 =  cr;
}



//----------------------------------------------------------------------------------------------------------------------
void Mat3::scale(Real _x,  Real _y,  Real _z) noexcept
{
	m_00 = _x;
	m_11 = _y;
	m_22 = _z;
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat3::operator * (const Vec3 &_v) const noexcept
{
  Vec3 temp;

  temp.m_x=_v.m_x * m_00 + _v.m_y* m_01 + _v.m_z * m_02;
  temp.m_y=_v.m_x * m_10 + _v.m_y* m_11 + _v.m_z * m_12;
  temp.m_z=_v.m_x * m_20 + _v.m_y* m_21 + _v.m_z * m_22;

  return temp;
}





//----------------------------------------------------------------------------------------------------------------------
void Mat3::euler( Real _angle,Real _x,  Real _y, Real _z) noexcept
{
  // Axis and Angle Mat3x3 rotation see
  // http://en.wikipedia.org/wiki/Rotation_Mat3x3 for more details
  Real beta=radians(_angle);
  Real c = cos(radians(beta));
  Real s = sin(radians(beta));
  Real C=1-c;
  Real xs  = _x*s;  Real  ys = _y*s;  Real  zs = _z*s;
  Real xC  = _x*C;  Real  yC = _y*C;  Real  zC = _z*C;
  Real xyC = _x*yC; Real yzC = _y*zC; Real zxC = _z*xC;

  m_m[0][0]=_x*xC+c;  m_m[0][1]= xyC-zs;  m_m[0][2]= zxC+ys;
  m_m[1][0]=xyC+zs;   m_m[1][1]=_y*yC+c;  m_m[1][2]= yzC-xs;
  m_m[2][0]=zxC-ys;   m_m[2][1]=yzC+xs;  m_m[2][2]=_z*zC+c;
}


Real Mat3::determinant() const noexcept
{
    return +m_00*(m_11*m_22-m_21*m_12)
            -m_01*(m_10*m_22-m_12*m_20)
            +m_02*(m_10*m_21-m_11*m_20);
}


void Mat3::inverse() noexcept
{
  Real det = determinant();
  if(det==0.0f)
  {
    std::cerr<<"ngl 0 determinant \n";
    return;

  }
  Real invdet = 1/det;

  Mat3 tmp;
  tmp.m_00 =  (m_11*m_22-m_21*m_12)*invdet;
  tmp.m_01 = -(m_10*m_22-m_12*m_20)*invdet;
  tmp.m_02 =  (m_10*m_21-m_20*m_11)*invdet;

  tmp.m_10 = -(m_01*m_22-m_02*m_21)*invdet;
  tmp.m_11 =  (m_00*m_22-m_02*m_20)*invdet;
  tmp.m_12 = -(m_00*m_21-m_20*m_01)*invdet;

  tmp.m_20 =  (m_01*m_12-m_02*m_11)*invdet;
  tmp.m_21 = -(m_00*m_12-m_10*m_02)*invdet;
  tmp.m_22 =  (m_00*m_11-m_10*m_01)*invdet;
  *this=tmp;
}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat3::getLeftVector() const noexcept
{
  return Vec3(-m_openGL[0],-m_openGL[1],-m_openGL[2]);
}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat3::getRightVector() const noexcept
{
  return Vec3( m_openGL[0],m_openGL[1],m_openGL[2]);

}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat3::getUpVector() const noexcept
{
  return Vec3(m_openGL[3],m_openGL[4],m_openGL[5]);

}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat3::getDownVector() const noexcept
{
  return Vec3(-m_openGL[3],-m_openGL[4],-m_openGL[5]);

}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat3::getForwardVector() const noexcept
{
  return Vec3(-m_openGL[6],-m_openGL[7],-m_openGL[8]);
}
//----------------------------------------------------------------------------------------------------------------------

Vec3 Mat3::getBackVector() const noexcept
{
  return Vec3(m_openGL[6],m_openGL[7],m_openGL[8]);

}
//----------------------------------------------------------------------------------------------------------------------



} // end namespace ngl



