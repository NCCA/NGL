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
#include "NGLassert.h"
#include "Mat4.h"
#include "Quaternion.h"
#include "Util.h"
#include "Vec3.h"
#include <iostream>
#include <cstring> // for memset
#include <boost/format.hpp>

//----------------------------------------------------------------------------------------------------------------------
/// @file Mat4.cpp
/// @brief implementation files for Matrix class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Mat4::Mat4()
{
	memset(&m_m,0,sizeof(m_m));
	m_00=1.0f;
	m_11=1.0f;
	m_22=1.0f;
	m_33=1.0f;
}

Mat4::Mat4(Real _m[4][4])
{
  for(int y=0; y<4; ++y)
  {
    for(int x=0; x<4; ++x)
    {
      m_m[y][x]=_m[y][x];
    }
  }

}

Mat4::Mat4(
            Real _00,Real _01,Real _02,Real _03,
            Real _10,Real _11,Real _12,Real _13,
            Real _20,Real _21,Real _22,Real _23,
            Real _30, Real _31, Real _32, Real _33 )
{
	m_00=_00;
	m_01=_01;
	m_02=_02;
	m_03=_03;

	m_10=_10;
	m_11=_11;
	m_12=_12;
	m_13=_13;
	m_20=_20;
	m_21=_21;
	m_22=_22;
	m_23=_23;
	m_30=_30;
	m_31=_31;
	m_32=_32;
	m_33=_33;
}
//----------------------------------------------------------------------------------------------------------------------
Mat4::Mat4(const Mat4& _m )
{
	memcpy(m_m,&_m.m_m,sizeof(m_m));
}
//----------------------------------------------------------------------------------------------------------------------
Mat4& Mat4::operator=(const Mat4& _m )
{
	memcpy(m_m,&_m.m_m,sizeof(m_m));
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Mat4::Mat4(Real _m)
{
	memset(m_m,0,sizeof(m_m));
	m_00=_m;
	m_11=_m;
	m_22=_m;
	m_33=1.0f;
}





//----------------------------------------------------------------------------------------------------------------------
/// @todo replace this with function operator overload ()
void Mat4::setAtXY(GLint _x,GLint _y, Real _equals  )
{
	m_m[_x][_y]=_equals;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat4& Mat4::null()
{
	memset(&m_m,0,sizeof(m_m));
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat4&  Mat4::identity()
{
	memset(m_m,0,sizeof(m_m));
	m_00=1.0f;
	m_11=1.0f;
	m_22=1.0f;
	m_33=1.0f;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Mat4 Mat4::operator*(const Mat4& _m )const
{
  Mat4 temp;
  // according to this http://www.research.scea.com/research/pdfs/GDC2003_Memory_Optimization_18Mar03.pdf
  // we get better cache performance and less in the way of
  // cache misses by prefectching the data using the consume / process pardigm
  // not really tested this yet so will be interesting to do so
/*
  ngl::Real  m00=m_m[0][0];
  ngl::Real  m01=m_m[0][1];
  ngl::Real  m02=m_m[0][2];
  ngl::Real  m03=m_m[0][3];

  ngl::Real  m10=m_m[1][0];
  ngl::Real  m11=m_m[1][1];
  ngl::Real  m12=m_m[1][2];
  ngl::Real  m13=m_m[1][3];

  ngl::Real  m20=m_m[2][0];
  ngl::Real  m21=m_m[2][1];
  ngl::Real  m22=m_m[2][2];
  ngl::Real  m23=m_m[2][3];

  ngl::Real  m30=m_m[3][0];
  ngl::Real  m31=m_m[3][1];
  ngl::Real  m32=m_m[3][2];
  ngl::Real  m33=m_m[3][3];

  ngl::Real  b00=_m.m_m[0][0];
  ngl::Real  b01=_m.m_m[0][1];
  ngl::Real  b02=_m.m_m[0][2];
  ngl::Real  b03=_m.m_m[0][3];

  ngl::Real  b10=_m.m_m[1][0];
  ngl::Real  b11=_m.m_m[1][1];
  ngl::Real  b12=_m.m_m[1][2];
  ngl::Real  b13=_m.m_m[1][3];

  ngl::Real  b20=_m.m_m[2][0];
  ngl::Real  b21=_m.m_m[2][1];
  ngl::Real  b22=_m.m_m[2][2];
  ngl::Real  b23=_m.m_m[2][3];

  ngl::Real  b30=_m.m_m[3][0];
  ngl::Real  b31=_m.m_m[3][1];
  ngl::Real  b32=_m.m_m[3][2];
  ngl::Real  b33=_m.m_m[3][3];

  temp.m_m[0][0] = m00 * b00 + m01 * b10 + m02 * b20 + m03 * b30;
  temp.m_m[0][1] = m00 * b01 + m01 * b11 + m02 * b21 + m03 * b31;
  temp.m_m[0][2] = m00 * _m.m_m[0][2] + m01 * b12 + m02 * b22 + m03 * b32;
  temp.m_m[0][3] = m00 * b03 + m01 * b13 + m02 * b23 + m03 * b33;
  temp.m_m[1][0] = m10 * b00 + m11 * b10 + m12 * b20 + m13 * b30;
  temp.m_m[1][1] = m10 * b01 + m11 * b11 + m12 * b21 + m13 * b31;
  temp.m_m[1][2] = m10 * _m.m_m[0][2] + m11 * b12 + m12 * b22 + m13 * b32;
  temp.m_m[1][3] = m10 * b03 + m11 * b13 + m12 * b23 + m13 * b33;
  temp.m_m[2][0] = m20 * b00 + m21 * b10 + m22 * b20 + m23 * b30;
  temp.m_m[2][1] = m20 * b01 + m21 * b11 + m22 * b21 + m23 * b31;
  temp.m_m[2][2] = m20 * _m.m_m[0][2] + m21 * b12 + m22 * b22 + m23 * b32;
  temp.m_m[2][3] = m20 * b03 + m21 * b13 + m22 * b23 + m23 * b33;
  temp.m_m[3][0] = m30 * b00 + m31 * b10 + m32 * b20 + m33 * b30;
  temp.m_m[3][1] = m30 * b01 + m31 * b11 + m32 * b21 + m33 * b31;
  temp.m_m[3][2] = m30 * _m.m_m[0][2] + m31 * b12 + m32 * b22 + m33 * b32;
  temp.m_m[3][3] = m30 * b03 + m31 * b13 + m32 * b23 + m33 * b33;
*/
// orignal

  temp.m_m[0][0] = m_m[0][0] * _m.m_m[0][0] + m_m[0][1] * _m.m_m[1][0] + m_m[0][2] * _m.m_m[2][0] + m_m[0][3] * _m.m_m[3][0];
  temp.m_m[0][1] = m_m[0][0] * _m.m_m[0][1] + m_m[0][1] * _m.m_m[1][1] + m_m[0][2] * _m.m_m[2][1] + m_m[0][3] * _m.m_m[3][1];
  temp.m_m[0][2] = m_m[0][0] * _m.m_m[0][2] + m_m[0][1] * _m.m_m[1][2] + m_m[0][2] * _m.m_m[2][2] + m_m[0][3] * _m.m_m[3][2];
  temp.m_m[0][3] = m_m[0][0] * _m.m_m[0][3] + m_m[0][1] * _m.m_m[1][3] + m_m[0][2] * _m.m_m[2][3] + m_m[0][3] * _m.m_m[3][3];
  temp.m_m[1][0] = m_m[1][0] * _m.m_m[0][0] + m_m[1][1] * _m.m_m[1][0] + m_m[1][2] * _m.m_m[2][0] + m_m[1][3] * _m.m_m[3][0];
  temp.m_m[1][1] = m_m[1][0] * _m.m_m[0][1] + m_m[1][1] * _m.m_m[1][1] + m_m[1][2] * _m.m_m[2][1] + m_m[1][3] * _m.m_m[3][1];
  temp.m_m[1][2] = m_m[1][0] * _m.m_m[0][2] + m_m[1][1] * _m.m_m[1][2] + m_m[1][2] * _m.m_m[2][2] + m_m[1][3] * _m.m_m[3][2];
  temp.m_m[1][3] = m_m[1][0] * _m.m_m[0][3] + m_m[1][1] * _m.m_m[1][3] + m_m[1][2] * _m.m_m[2][3] + m_m[1][3] * _m.m_m[3][3];
  temp.m_m[2][0] = m_m[2][0] * _m.m_m[0][0] + m_m[2][1] * _m.m_m[1][0] + m_m[2][2] * _m.m_m[2][0] + m_m[2][3] * _m.m_m[3][0];
  temp.m_m[2][1] = m_m[2][0] * _m.m_m[0][1] + m_m[2][1] * _m.m_m[1][1] + m_m[2][2] * _m.m_m[2][1] + m_m[2][3] * _m.m_m[3][1];
  temp.m_m[2][2] = m_m[2][0] * _m.m_m[0][2] + m_m[2][1] * _m.m_m[1][2] + m_m[2][2] * _m.m_m[2][2] + m_m[2][3] * _m.m_m[3][2];
  temp.m_m[2][3] = m_m[2][0] * _m.m_m[0][3] + m_m[2][1] * _m.m_m[1][3] + m_m[2][2] * _m.m_m[2][3] + m_m[2][3] * _m.m_m[3][3];
  temp.m_m[3][0] = m_m[3][0] * _m.m_m[0][0] + m_m[3][1] * _m.m_m[1][0] + m_m[3][2] * _m.m_m[2][0] + m_m[3][3] * _m.m_m[3][0];
  temp.m_m[3][1] = m_m[3][0] * _m.m_m[0][1] + m_m[3][1] * _m.m_m[1][1] + m_m[3][2] * _m.m_m[2][1] + m_m[3][3] * _m.m_m[3][1];
  temp.m_m[3][2] = m_m[3][0] * _m.m_m[0][2] + m_m[3][1] * _m.m_m[1][2] + m_m[3][2] * _m.m_m[2][2] + m_m[3][3] * _m.m_m[3][2];
  temp.m_m[3][3] = m_m[3][0] * _m.m_m[0][3] + m_m[3][1] * _m.m_m[1][3] + m_m[3][2] * _m.m_m[2][3] + m_m[3][3] * _m.m_m[3][3];

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat4& Mat4::operator*= ( const Mat4 &_m )
{
	Mat4 temp(*this);



	//  row 0
	m_00  =  temp.m_00 * _m.m_00;
	m_01  =  temp.m_01 * _m.m_00;
	m_02  =  temp.m_02 * _m.m_00;
	m_03  =  temp.m_03 * _m.m_00;

	m_00 +=  temp.m_10 * _m.m_01;
	m_01 +=  temp.m_11 * _m.m_01;
	m_02 +=  temp.m_12 * _m.m_01;
	m_03 +=  temp.m_13 * _m.m_01;

	m_00 +=  temp.m_20 * _m.m_02;
	m_01 +=  temp.m_21 * _m.m_02;
	m_02 +=  temp.m_22 * _m.m_02;
	m_03 +=  temp.m_23 * _m.m_02;

	m_00 +=  temp.m_30 * _m.m_03;
	m_01 +=  temp.m_31 * _m.m_03;
	m_02 +=  temp.m_32 * _m.m_03;
	m_03 +=  temp.m_33 * _m.m_03;


	//  row 1
	m_10  =  temp.m_00 * _m.m_10;
	m_11  =  temp.m_01 * _m.m_10;
	m_12  =  temp.m_02 * _m.m_10;
	m_13  =  temp.m_03 * _m.m_10;

	m_10 +=  temp.m_10 * _m.m_11;
	m_11 +=  temp.m_11 * _m.m_11;
	m_12 +=  temp.m_12 * _m.m_11;
	m_13 +=  temp.m_13 * _m.m_11;

	m_10 +=  temp.m_20 * _m.m_12;
	m_11 +=  temp.m_21 * _m.m_12;
	m_12 +=  temp.m_22 * _m.m_12;
	m_13 +=  temp.m_23 * _m.m_12;

	m_10 +=  temp.m_30 * _m.m_13;
	m_11 +=  temp.m_31 * _m.m_13;
	m_12 +=  temp.m_32 * _m.m_13;
	m_13 +=  temp.m_33 * _m.m_13;


	//  row 2
	m_20  =  temp.m_00 * _m.m_20;
	m_21  =  temp.m_01 * _m.m_20;
	m_22  =  temp.m_02 * _m.m_20;
	m_23  =  temp.m_03 * _m.m_20;

	m_20 +=  temp.m_10 * _m.m_21;
	m_21 +=  temp.m_11 * _m.m_21;
	m_22 +=  temp.m_12 * _m.m_21;
	m_23 +=  temp.m_13 * _m.m_21;

	m_20 +=  temp.m_20 * _m.m_22;
	m_21 +=  temp.m_21 * _m.m_22;
	m_22 +=  temp.m_22 * _m.m_22;
	m_23 +=  temp.m_23 * _m.m_22;

	m_20 +=  temp.m_30 * _m.m_23;
	m_21 +=  temp.m_31 * _m.m_23;
	m_22 +=  temp.m_32 * _m.m_23;
	m_23 +=  temp.m_33 * _m.m_23;


	//  row 3
	m_30  =  temp.m_00 * _m.m_30;
	m_31  =  temp.m_01 * _m.m_30;
	m_32  =  temp.m_02 * _m.m_30;
	m_33  =  temp.m_03 * _m.m_30;

	m_30 +=  temp.m_10 * _m.m_31;
	m_31 +=  temp.m_11 * _m.m_31;
	m_32 +=  temp.m_12 * _m.m_31;
	m_33 +=  temp.m_13 * _m.m_31;

	m_30 +=  temp.m_20 * _m.m_32;
	m_31 +=  temp.m_21 * _m.m_32;
	m_32 +=  temp.m_22 * _m.m_32;
	m_33 +=  temp.m_23 * _m.m_32;

	m_30 +=  temp.m_30 * _m.m_33;
	m_31 +=  temp.m_31 * _m.m_33;
	m_32 +=  temp.m_32 * _m.m_33;
	m_33 +=  temp.m_33 * _m.m_33;

	return *this;
}


//----------------------------------------------------------------------------------------------------------------------
Mat4 Mat4::operator+(const Mat4 &_m ) const
{
	Mat4 Ret;
	const Real* iterA = m_openGL;
	const Real* iterB = _m.m_openGL;
	Real* iterR = Ret.m_openGL;
	const Real* end   = m_openGL+16;

	for( ; iterA != end; ++iterA, ++iterB, ++iterR)
	{
		*iterR = *iterA + *iterB;
	}
	return Ret;
}
//----------------------------------------------------------------------------------------------------------------------
const Mat4& Mat4::operator+=(const Mat4 &_m  )
{
	Real* iterA =m_openGL;
	const Real* iterB = _m.m_openGL;
	const Real* end   = m_openGL+16;

	for( ; iterA != end; ++iterA, ++iterB)
	{
		*iterA += *iterB;
	}
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Mat4 Mat4::operator*( const Real _i  ) const
{
	Mat4 ret;
	const Real* iterA = m_openGL;
	Real* iterB = ret.m_openGL;
	const Real* end   = m_openGL+16;

	for( ; iterA != end; ++iterA, ++iterB)
	{
		*iterB = (*iterA) * _i;
	}
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
const Mat4& Mat4::operator*=(const Real _i)
{
	for(int y=0; y<4; y++)
	{
		for(int x=0; x<4; x++)
		{
			m_m[y][x]*=_i;
		}
	}
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vec4 Mat4::operator * (const Vec4 &_v ) const
{
  Vec4 temp;

  temp.m_x=_v.m_x * m_00 + _v.m_y	* m_01 + _v.m_z * m_02 + _v.m_w * m_03;
  temp.m_y=_v.m_x * m_10 + _v.m_y	* m_11 + _v.m_z * m_12 + _v.m_w * m_13;
  temp.m_z=_v.m_x * m_20 + _v.m_y	* m_21 + _v.m_z * m_22 + _v.m_w * m_23;
  temp.m_w=_v.m_x * m_30 + _v.m_y	* m_31 + _v.m_z * m_32 + _v.m_w * m_33;

return temp;
}


//----------------------------------------------------------------------------------------------------------------------
const Mat4& Mat4::transpose()
{
	Mat4 tmp(*this);

	for(int row=0; row<4; row++)
	{
		for(int col=0; col<4; col++)
		{
			m_m[row][col]=tmp.m_m[col][row];
		}
	}
	return *this;
}



//----------------------------------------------------------------------------------------------------------------------
void Mat4::rotateX( const Real _deg)
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
void Mat4::rotateY( const Real _deg )
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
void Mat4::rotateZ(const Real _deg )
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
void Mat4::translate( const Real _x,const Real _y,  const Real _z )
{
	m_30 = _x;
	m_31 = _y;
	m_32 = _z;
}

//----------------------------------------------------------------------------------------------------------------------
void Mat4::scale(const Real _x, const Real _y,  const Real _z )
{
	m_00 = _x;
	m_11 = _y;
	m_22 = _z;
}

//----------------------------------------------------------------------------------------------------------------------
void Mat4::subMatrix3x3(const int _i, const int _j, Real o_mat[]  ) const
{
  int ti, tj, idst=0, jdst=0;

  for ( ti = 0; ti != 4; ++ti )
  {
    if ( ti < _i )
    {
      idst = ti;
    }
    else
    {
      if ( ti > _i )
      {
      idst = ti-1;
      }

      for ( tj = 0; tj != 4; ++tj )
      {
        if ( tj < _j )
        {
          jdst = tj;
        }
        else if ( tj > _j )
        {
          jdst = tj-1;
        }
        if ( ti != _i && tj != _j )
        {
          o_mat[idst*3 + jdst] = m_openGL[ti*4 + tj];
        }
      }
    } // end else
  }// end for
}
//----------------------------------------------------------------------------------------------------------------------
Real Mat4::determinant() const
{
    // Our matrices are 4.4 only, so we can just write the full formula instead of a complex algorithm.
    return (
      m_m[0][0]*m_m[1][1]*m_m[2][2]*m_m[3][3] - m_m[0][0]*m_m[1][1]*m_m[2][3]*m_m[3][2] + m_m[0][0]*m_m[1][2]*m_m[2][3]*m_m[3][1] - m_m[0][0]*m_m[1][2]*m_m[2][1]*m_m[3][3] + m_m[0][0]*m_m[1][3]*m_m[2][1]*m_m[3][2] - m_m[0][0]*m_m[1][3]*m_m[2][2]*m_m[3][1]
    - m_m[1][0]*m_m[2][1]*m_m[3][2]*m_m[0][3] + m_m[1][0]*m_m[2][1]*m_m[0][2]*m_m[3][3] - m_m[1][0]*m_m[3][1]*m_m[0][2]*m_m[2][3] + m_m[1][0]*m_m[3][1]*m_m[2][2]*m_m[0][3] - m_m[1][0]*m_m[0][1]*m_m[2][2]*m_m[3][3] + m_m[1][0]*m_m[0][1]*m_m[3][2]*m_m[2][3]
    + m_m[2][0]*m_m[3][1]*m_m[0][2]*m_m[1][3] - m_m[2][0]*m_m[3][1]*m_m[1][2]*m_m[0][3] + m_m[2][0]*m_m[0][1]*m_m[1][2]*m_m[3][3] - m_m[2][0]*m_m[0][1]*m_m[3][2]*m_m[1][3] + m_m[2][0]*m_m[1][1]*m_m[3][2]*m_m[0][3] - m_m[2][0]*m_m[1][1]*m_m[0][2]*m_m[3][3]
    - m_m[3][0]*m_m[0][1]*m_m[1][2]*m_m[2][3] + m_m[3][0]*m_m[0][1]*m_m[2][2]*m_m[1][3] - m_m[3][0]*m_m[1][1]*m_m[2][2]*m_m[0][3] + m_m[3][0]*m_m[1][1]*m_m[0][2]*m_m[2][3] - m_m[3][0]*m_m[2][1]*m_m[0][2]*m_m[1][3] + m_m[3][0]*m_m[2][1]*m_m[1][2]*m_m[0][3]
    );
}







//----------------------------------------------------------------------------------------------------------------------
void Mat4::euler(const Real _angle, const Real _x, const Real _y, const Real _z   )
{
  // Axis and Angle matrix rotation see
  // http://en.wikipedia.org/wiki/Rotation_matrix for more details
  Real beta=radians(_angle);
  Real c = cos((beta));
  Real s = sin((beta));
  Real C=1-c;
  Real xs  = _x*s;  Real  ys = _y*s;  Real  zs = _z*s;
  Real xC  = _x*C;  Real  yC = _y*C;  Real  zC = _z*C;
  Real xyC = _x*yC; Real yzC = _y*zC; Real zxC = _z*xC;

  m_m[0][0]=_x*xC+c;  m_m[0][1]= xyC-zs;  m_m[0][2]= zxC+ys;
  m_m[1][0]=xyC+zs;   m_m[1][1]=_y*yC+c;  m_m[1][2]= yzC-xs;
  m_m[2][0]=zxC-ys;   m_m[2][1]=yzC+xs;  m_m[2][2]=_z*zC+c;
}

void Mat4::as3x3Array(Real _d[9]) const
{
  _d[0]=m_m[0][0];
  _d[1]=m_m[1][0];
  _d[2]=m_m[2][0];

  _d[3]=m_m[0][1];
  _d[4]=m_m[1][1];
  _d[5]=m_m[2][1];

  _d[6]=m_m[0][2];
  _d[7]=m_m[1][2];
  _d[8]=m_m[2][2];
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Mat4::asQuaternion() const
{
  // calculate trace of the matrix
  Real T = m_openGL[0] + m_openGL[5] + m_openGL[10] + 1;

  // if trace is greater than 0, calculate an instant calculation
  if( T > 0 )
  {
    Real S = static_cast<Real>( 0.5f / sqrt(T) );
    return Quaternion(  static_cast<Real>( ( m_openGL[6] - m_openGL[9] ) * S),
        static_cast<Real>( ( m_openGL[8] - m_openGL[2] ) * S),
        static_cast<Real>( ( m_openGL[1] - m_openGL[4] ) * S),
        static_cast<Real>( 0.25f / S)
        );
  }
  Real BigF = m_openGL[0];
  unsigned char check=0;
  if( m_openGL[5] > BigF )
  {
    check = 1;
    BigF = m_openGL[5];
  }
  if( m_openGL[10] > BigF )
  {
    check = 2;
    BigF = m_openGL[10];
  }
  switch(check)
  {
  case 0:
  {
    Real S  = static_cast<Real>( sqrt( 1.0f + m_openGL[0] - m_openGL[5] - m_openGL[10] ) * 2.0f );

    return Quaternion( 0.5f / S,
    (m_openGL[1] + m_openGL[4] ) / S,
    (m_openGL[2] + m_openGL[8] ) / S,
    (m_openGL[6] + m_openGL[9] ) / S );
  }
  case 1:
  {
    Real S  = static_cast<Real>( sqrt( 1.0f + m_openGL[5] - m_openGL[0] - m_openGL[10] ) * 2.0f );

    return Quaternion((m_openGL[1] + m_openGL[4] ) / S,
    0.5f / S,
    (m_openGL[6] + m_openGL[9] ) / S,
    (m_openGL[2] + m_openGL[8] ) / S );
  }
  case 2:
  {
    Real S  = static_cast<Real>( sqrt( 1.0f + m_openGL[10] - m_openGL[0] - m_openGL[5] ) * 2.0f );

    return Quaternion((m_openGL[2] + m_openGL[8] ) / S,
    (m_openGL[6] + m_openGL[9] ) / S,
    0.5f / S,
    (m_openGL[1] + m_openGL[4] ) / S );
  }
  default:
  {
    NGL_ASSERT(0 && "SHOULDN'T GET HERE in ngl Quaternion");
    break;
  }
  }// end switch
  return Quaternion();

}
//----------------------------------------------------------------------------------------------------------------------

Mat4  Mat4::Adjacent( const Mat4 &_mat )
{
    Mat4 m;

    m.m_00 = _mat.m_m[1][1]*(_mat.m_m[2][2]*_mat.m_m[3][3]-_mat.m_m[3][2]*_mat.m_m[2][3])+_mat.m_m[1][2]*(_mat.m_m[3][1]*_mat.m_m[2][3]-_mat.m_m[2][1]*_mat.m_m[3][3])+_mat.m_m[1][3]*(_mat.m_m[2][1]*_mat.m_m[3][2]-_mat.m_m[3][1]*_mat.m_m[2][2]);
    m.m_01 = _mat.m_m[1][0]*(_mat.m_m[3][2]*_mat.m_m[2][3]-_mat.m_m[2][2]*_mat.m_m[3][3])+_mat.m_m[1][2]*(_mat.m_m[2][0]*_mat.m_m[3][3]-_mat.m_m[3][0]*_mat.m_m[2][3])+_mat.m_m[1][3]*(_mat.m_m[3][0]*_mat.m_m[2][2]-_mat.m_m[2][0]*_mat.m_m[3][2]);
    m.m_02 = _mat.m_m[1][0]*(_mat.m_m[2][1]*_mat.m_m[3][3]-_mat.m_m[3][1]*_mat.m_m[2][3])+_mat.m_m[1][1]*(_mat.m_m[3][0]*_mat.m_m[2][3]-_mat.m_m[2][0]*_mat.m_m[3][3])+_mat.m_m[1][3]*(_mat.m_m[2][0]*_mat.m_m[3][1]-_mat.m_m[3][0]*_mat.m_m[2][1]);
    m.m_03 = _mat.m_m[1][0]*(_mat.m_m[3][1]*_mat.m_m[2][2]-_mat.m_m[2][1]*_mat.m_m[3][2])+_mat.m_m[1][1]*(_mat.m_m[2][0]*_mat.m_m[3][2]-_mat.m_m[3][0]*_mat.m_m[2][2])+_mat.m_m[1][2]*(_mat.m_m[3][0]*_mat.m_m[2][1]-_mat.m_m[2][0]*_mat.m_m[3][1]);

    m.m_10 = _mat.m_m[0][1]*(_mat.m_m[3][2]*_mat.m_m[2][3]-_mat.m_m[2][2]*_mat.m_m[3][3])+_mat.m_m[0][2]*(_mat.m_m[2][1]*_mat.m_m[3][3]-_mat.m_m[3][1]*_mat.m_m[2][3])+_mat.m_m[0][3]*(_mat.m_m[3][1]*_mat.m_m[2][2]-_mat.m_m[2][1]*_mat.m_m[3][2]);
    m.m_11 = _mat.m_m[0][0]*(_mat.m_m[2][2]*_mat.m_m[3][3]-_mat.m_m[3][2]*_mat.m_m[2][3])+_mat.m_m[0][2]*(_mat.m_m[3][0]*_mat.m_m[2][3]-_mat.m_m[2][0]*_mat.m_m[3][3])+_mat.m_m[0][3]*(_mat.m_m[2][0]*_mat.m_m[3][2]-_mat.m_m[3][0]*_mat.m_m[2][2]);
    m.m_12 = _mat.m_m[0][0]*(_mat.m_m[3][1]*_mat.m_m[2][3]-_mat.m_m[2][1]*_mat.m_m[3][3])+_mat.m_m[0][1]*(_mat.m_m[2][0]*_mat.m_m[3][3]-_mat.m_m[3][0]*_mat.m_m[2][3])+_mat.m_m[0][3]*(_mat.m_m[3][0]*_mat.m_m[2][1]-_mat.m_m[2][0]*_mat.m_m[3][1]);
    m.m_13=  _mat.m_m[0][0]*(_mat.m_m[2][1]*_mat.m_m[3][2]-_mat.m_m[3][1]*_mat.m_m[2][2])+_mat.m_m[0][1]*(_mat.m_m[3][0]*_mat.m_m[2][2]-_mat.m_m[2][0]*_mat.m_m[3][2])+_mat.m_m[0][2]*(_mat.m_m[2][0]*_mat.m_m[3][1]-_mat.m_m[3][0]*_mat.m_m[2][1]);

    m.m_20 = _mat.m_m[0][1]*(_mat.m_m[1][2]*_mat.m_m[3][3]-_mat.m_m[3][2]*_mat.m_m[1][3])+_mat.m_m[0][2]*(_mat.m_m[3][1]*_mat.m_m[1][3]-_mat.m_m[1][1]*_mat.m_m[3][3])+_mat.m_m[0][3]*(_mat.m_m[1][1]*_mat.m_m[3][2]-_mat.m_m[3][1]*_mat.m_m[1][2]);
    m.m_21 = _mat.m_m[0][0]*(_mat.m_m[3][2]*_mat.m_m[1][3]-_mat.m_m[1][2]*_mat.m_m[3][3])+_mat.m_m[0][2]*(_mat.m_m[1][0]*_mat.m_m[3][3]-_mat.m_m[3][0]*_mat.m_m[1][3])+_mat.m_m[0][3]*(_mat.m_m[3][0]*_mat.m_m[1][2]-_mat.m_m[1][0]*_mat.m_m[3][2]);
    m.m_22 = _mat.m_m[0][0]*(_mat.m_m[1][1]*_mat.m_m[3][3]-_mat.m_m[3][1]*_mat.m_m[1][3])+_mat.m_m[0][1]*(_mat.m_m[3][0]*_mat.m_m[1][3]-_mat.m_m[1][0]*_mat.m_m[3][3])+_mat.m_m[0][3]*(_mat.m_m[1][0]*_mat.m_m[3][1]-_mat.m_m[3][0]*_mat.m_m[1][1]);
    m.m_23 = _mat.m_m[0][0]*(_mat.m_m[3][1]*_mat.m_m[1][2]-_mat.m_m[1][1]*_mat.m_m[3][2])+_mat.m_m[0][1]*(_mat.m_m[1][0]*_mat.m_m[3][2]-_mat.m_m[3][0]*_mat.m_m[1][2])+_mat.m_m[0][2]*(_mat.m_m[3][0]*_mat.m_m[1][1]-_mat.m_m[1][0]*_mat.m_m[3][1]);

    m.m_30 = _mat.m_m[0][1]*(_mat.m_m[2][2]*_mat.m_m[1][3]-_mat.m_m[1][2]*_mat.m_m[2][3])+_mat.m_m[0][2]*(_mat.m_m[1][1]*_mat.m_m[2][3]-_mat.m_m[2][1]*_mat.m_m[1][3])+_mat.m_m[0][3]*(_mat.m_m[2][1]*_mat.m_m[1][2]-_mat.m_m[1][1]*_mat.m_m[2][2]);
    m.m_31 = _mat.m_m[0][0]*(_mat.m_m[1][2]*_mat.m_m[2][3]-_mat.m_m[2][2]*_mat.m_m[1][3])+_mat.m_m[0][2]*(_mat.m_m[2][0]*_mat.m_m[1][3]-_mat.m_m[1][0]*_mat.m_m[2][3])+_mat.m_m[0][3]*(_mat.m_m[1][0]*_mat.m_m[2][2]-_mat.m_m[2][0]*_mat.m_m[1][2]);
    m.m_32 = _mat.m_m[0][0]*(_mat.m_m[2][1]*_mat.m_m[1][3]-_mat.m_m[1][1]*_mat.m_m[2][3])+_mat.m_m[0][1]*(_mat.m_m[1][0]*_mat.m_m[2][3]-_mat.m_m[2][0]*_mat.m_m[1][3])+_mat.m_m[0][3]*(_mat.m_m[2][0]*_mat.m_m[1][1]-_mat.m_m[1][0]*_mat.m_m[2][1]);
    m.m_33 = _mat.m_m[0][0]*(_mat.m_m[1][1]*_mat.m_m[2][2]-_mat.m_m[2][1]*_mat.m_m[1][2])+_mat.m_m[0][1]*(_mat.m_m[2][0]*_mat.m_m[1][2]-_mat.m_m[1][0]*_mat.m_m[2][2])+_mat.m_m[0][2]*(_mat.m_m[1][0]*_mat.m_m[2][1]-_mat.m_m[2][0]*_mat.m_m[1][1]);

    return m;
}

Mat4  Mat4::Adjacent( )
{
    Mat4 m;

    m.m_00 = m_m[1][1]*(m_m[2][2]*m_m[3][3]-m_m[3][2]*m_m[2][3])+m_m[1][2]*(m_m[3][1]*m_m[2][3]-m_m[2][1]*m_m[3][3])+m_m[1][3]*(m_m[2][1]*m_m[3][2]-m_m[3][1]*m_m[2][2]);
    m.m_01 = m_m[1][0]*(m_m[3][2]*m_m[2][3]-m_m[2][2]*m_m[3][3])+m_m[1][2]*(m_m[2][0]*m_m[3][3]-m_m[3][0]*m_m[2][3])+m_m[1][3]*(m_m[3][0]*m_m[2][2]-m_m[2][0]*m_m[3][2]);
    m.m_02 = m_m[1][0]*(m_m[2][1]*m_m[3][3]-m_m[3][1]*m_m[2][3])+m_m[1][1]*(m_m[3][0]*m_m[2][3]-m_m[2][0]*m_m[3][3])+m_m[1][3]*(m_m[2][0]*m_m[3][1]-m_m[3][0]*m_m[2][1]);
    m.m_03 = m_m[1][0]*(m_m[3][1]*m_m[2][2]-m_m[2][1]*m_m[3][2])+m_m[1][1]*(m_m[2][0]*m_m[3][2]-m_m[3][0]*m_m[2][2])+m_m[1][2]*(m_m[3][0]*m_m[2][1]-m_m[2][0]*m_m[3][1]);

    m.m_10 = m_m[0][1]*(m_m[3][2]*m_m[2][3]-m_m[2][2]*m_m[3][3])+m_m[0][2]*(m_m[2][1]*m_m[3][3]-m_m[3][1]*m_m[2][3])+m_m[0][3]*(m_m[3][1]*m_m[2][2]-m_m[2][1]*m_m[3][2]);
    m.m_11 = m_m[0][0]*(m_m[2][2]*m_m[3][3]-m_m[3][2]*m_m[2][3])+m_m[0][2]*(m_m[3][0]*m_m[2][3]-m_m[2][0]*m_m[3][3])+m_m[0][3]*(m_m[2][0]*m_m[3][2]-m_m[3][0]*m_m[2][2]);
    m.m_12 = m_m[0][0]*(m_m[3][1]*m_m[2][3]-m_m[2][1]*m_m[3][3])+m_m[0][1]*(m_m[2][0]*m_m[3][3]-m_m[3][0]*m_m[2][3])+m_m[0][3]*(m_m[3][0]*m_m[2][1]-m_m[2][0]*m_m[3][1]);
    m.m_13=  m_m[0][0]*(m_m[2][1]*m_m[3][2]-m_m[3][1]*m_m[2][2])+m_m[0][1]*(m_m[3][0]*m_m[2][2]-m_m[2][0]*m_m[3][2])+m_m[0][2]*(m_m[2][0]*m_m[3][1]-m_m[3][0]*m_m[2][1]);

    m.m_20 = m_m[0][1]*(m_m[1][2]*m_m[3][3]-m_m[3][2]*m_m[1][3])+m_m[0][2]*(m_m[3][1]*m_m[1][3]-m_m[1][1]*m_m[3][3])+m_m[0][3]*(m_m[1][1]*m_m[3][2]-m_m[3][1]*m_m[1][2]);
    m.m_21 = m_m[0][0]*(m_m[3][2]*m_m[1][3]-m_m[1][2]*m_m[3][3])+m_m[0][2]*(m_m[1][0]*m_m[3][3]-m_m[3][0]*m_m[1][3])+m_m[0][3]*(m_m[3][0]*m_m[1][2]-m_m[1][0]*m_m[3][2]);
    m.m_22 = m_m[0][0]*(m_m[1][1]*m_m[3][3]-m_m[3][1]*m_m[1][3])+m_m[0][1]*(m_m[3][0]*m_m[1][3]-m_m[1][0]*m_m[3][3])+m_m[0][3]*(m_m[1][0]*m_m[3][1]-m_m[3][0]*m_m[1][1]);
    m.m_23 = m_m[0][0]*(m_m[3][1]*m_m[1][2]-m_m[1][1]*m_m[3][2])+m_m[0][1]*(m_m[1][0]*m_m[3][2]-m_m[3][0]*m_m[1][2])+m_m[0][2]*(m_m[3][0]*m_m[1][1]-m_m[1][0]*m_m[3][1]);

    m.m_30 = m_m[0][1]*(m_m[2][2]*m_m[1][3]-m_m[1][2]*m_m[2][3])+m_m[0][2]*(m_m[1][1]*m_m[2][3]-m_m[2][1]*m_m[1][3])+m_m[0][3]*(m_m[2][1]*m_m[1][2]-m_m[1][1]*m_m[2][2]);
    m.m_31 = m_m[0][0]*(m_m[1][2]*m_m[2][3]-m_m[2][2]*m_m[1][3])+m_m[0][2]*(m_m[2][0]*m_m[1][3]-m_m[1][0]*m_m[2][3])+m_m[0][3]*(m_m[1][0]*m_m[2][2]-m_m[2][0]*m_m[1][2]);
    m.m_32 = m_m[0][0]*(m_m[2][1]*m_m[1][3]-m_m[1][1]*m_m[2][3])+m_m[0][1]*(m_m[1][0]*m_m[2][3]-m_m[2][0]*m_m[1][3])+m_m[0][3]*(m_m[2][0]*m_m[1][1]-m_m[1][0]*m_m[2][1]);
    m.m_33 = m_m[0][0]*(m_m[1][1]*m_m[2][2]-m_m[2][1]*m_m[1][2])+m_m[0][1]*(m_m[2][0]*m_m[1][2]-m_m[1][0]*m_m[2][2])+m_m[0][2]*(m_m[1][0]*m_m[2][1]-m_m[2][0]*m_m[1][1]);

    return m;
}

Mat4 Mat4::inverse()
{


  Mat4 t;
  t.m_00 = m_11*m_22*m_33 + m_12*m_23*m_31 + m_13*m_21*m_32 - m_11*m_32*m_23 - m_12*m_21*m_33 - m_13*m_22*m_31;
  t.m_01 = m_01*m_23*m_32 + m_02*m_21*m_33 + m_03*m_22*m_31 - m_01*m_22*m_33 - m_02*m_23*m_31 - m_03*m_21*m_32;
  t.m_02 = m_01*m_12*m_33 + m_02*m_13*m_31 + m_03*m_11*m_32 - m_01*m_13*m_32 - m_02*m_11*m_33 - m_03*m_12*m_31;
  t.m_03 = m_01*m_13*m_22 + m_02*m_11*m_23 + m_03*m_12*m_21 - m_01*m_12*m_23 - m_02*m_13*m_21 - m_03*m_11*m_22;
  t.m_10 = m_10*m_23*m_32 + m_12*m_20*m_33 + m_13*m_22*m_30 - m_10*m_22*m_33 - m_12*m_23*m_30 - m_13*m_20*m_32;
  t.m_11 = m_00*m_22*m_33 + m_02*m_23*m_30 + m_03*m_20*m_32 - m_00*m_23*m_32 - m_02*m_20*m_33 - m_03*m_22*m_30;
  t.m_12 = m_00*m_13*m_32 + m_02*m_10*m_33 + m_03*m_12*m_30 - m_00*m_12*m_33 - m_02*m_13*m_30 - m_03*m_10*m_32;
  t.m_13 = m_00*m_12*m_23 + m_02*m_13*m_20 + m_03*m_10*m_22 - m_00*m_13*m_22 - m_02*m_10*m_23 - m_03*m_12*m_20;
  t.m_20 = m_10*m_21*m_33 + m_11*m_23*m_30 + m_13*m_20*m_31 - m_10*m_23*m_31 - m_11*m_20*m_33 - m_13*m_21*m_30;
  t.m_21 = m_00*m_23*m_31 + m_01*m_20*m_33 + m_03*m_21*m_30 - m_00*m_21*m_33 - m_01*m_23*m_30 - m_03*m_20*m_31;
  t.m_22 = m_00*m_11*m_33 + m_01*m_13*m_30 + m_03*m_10*m_31 - m_00*m_13*m_31 - m_01*m_10*m_33 - m_03*m_11*m_30;
  t.m_23 = m_00*m_13*m_21 + m_01*m_10*m_23 + m_03*m_11*m_20 - m_00*m_11*m_23 - m_01*m_13*m_20 - m_03*m_10*m_21;
  t.m_30 = m_10*m_22*m_31 + m_11*m_20*m_32 + m_12*m_21*m_30 - m_10*m_21*m_32 - m_11*m_22*m_30 - m_12*m_20*m_31;
  t.m_31 = m_00*m_21*m_32 + m_01*m_22*m_30 + m_02*m_20*m_31 - m_00*m_22*m_31 - m_01*m_20*m_32 - m_02*m_21*m_30;
  t.m_32 = m_00*m_12*m_31 + m_01*m_10*m_32 + m_02*m_11*m_30 - m_00*m_11*m_32 - m_01*m_12*m_30 - m_02*m_10*m_31;
  t.m_33 = m_00*m_11*m_22 + m_01*m_12*m_20 + m_02*m_10*m_21 - m_00*m_12*m_21 - m_01*m_10*m_22 - m_02*m_11*m_20;


  double det = determinant();
  det = 1/det;
  return  t*det;


}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat4::getLeftVector() const
{
  return Vec3(-m_openGL[0],-m_openGL[1],-m_openGL[2]);
}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat4::getRightVector() const
{
  return Vec3( m_openGL[0],m_openGL[1],m_openGL[2]);

}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat4::getUpVector() const
{
  return Vec3(m_openGL[4],m_openGL[5],m_openGL[6]);

}

//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat4::getDownVector() const
{
  return Vec3(-m_openGL[4],-m_openGL[5],-m_openGL[6]);

}
//----------------------------------------------------------------------------------------------------------------------
Vec3 Mat4::getForwardVector() const
{
  return Vec3(-m_openGL[8],-m_openGL[9],-m_openGL[10]);
}
//----------------------------------------------------------------------------------------------------------------------

Vec3 Mat4::getBackVector() const
{
  return Vec3(m_openGL[8],m_openGL[9],m_openGL[10]);

}



} // end namespace ngl



