/*
  Copyright (C) 2009 Rob Bateman / Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITH ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this progra_m.  If not, see <http://www.gnu.org/licenses/>.
*/

//----------------------------------------------------------------------------------------------------------------------
/// @file Quaternion.cpp
/// @brief implementation files for Quaternion class
//----------------------------------------------------------------------------------------------------------------------

#include "Quaternion.h"
#include "Util.h"
#include <boost/format.hpp>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Quaternion::Quaternion(const Mat4 &_m) noexcept
{
  Real T = 1 + _m.m_openGL[0] + _m.m_openGL[5] + _m.m_openGL[10];
  if ( T > 0.00000001f ) //to avoid large distortions!
  {
    Real S = static_cast<Real>(sqrt(T) * 2.0f);
    m_x = ( _m.m_openGL[6] - _m.m_openGL[9] ) / S;
    m_y = ( _m.m_openGL[8] - _m.m_openGL[2] ) / S;
    m_z = ( _m.m_openGL[1] - _m.m_openGL[4] ) / S;
    m_s = 0.25f * S;
  }
  else
  if ( _m.m_openGL[0] > _m.m_openGL[5] &&
       _m.m_openGL[0] > _m.m_openGL[10] )
  {		// Column 0:
    Real S  = static_cast<Real>(sqrt( 1.0f + _m.m_openGL[0] - _m.m_openGL[5] - _m.m_openGL[10] ) * 2.0f);
    m_x = 0.25f * S;
    m_y = (_m.m_openGL[1] + _m.m_openGL[4] ) / S;
    m_z = (_m.m_openGL[8] + _m.m_openGL[2] ) / S;
    m_s = (_m.m_openGL[6] - _m.m_openGL[9] ) / S;
  }
  else
  if ( _m.m_openGL[5] > _m.m_openGL[10] )
  {			// Column 1:
    Real S  = static_cast<Real>(sqrt( 1.0 + _m.m_openGL[5] - _m.m_openGL[0] - _m.m_openGL[10] ) * 2.0f);
    m_x = (_m.m_openGL[1] + _m.m_openGL[4] ) / S;
    m_y = 0.25f * S;
    m_z = (_m.m_openGL[6] + _m.m_openGL[9] ) / S;
    m_s = (_m.m_openGL[8] - _m.m_openGL[2] ) / S;
  }
  else
  {										// Column 2:
    Real S  = static_cast<Real>(sqrt( 1.0 + _m.m_openGL[10] - _m.m_openGL[0] - _m.m_openGL[5] ) * 2.0f);
    m_x = (_m.m_openGL[8] + _m.m_openGL[2] ) / S;
    m_y = (_m.m_openGL[6] + _m.m_openGL[9] ) / S;
    m_z = 0.25f * S;
    m_s = (_m.m_openGL[1] - _m.m_openGL[4] ) / S;
  }
}

Quaternion::Quaternion(const Vec3 &_rot) noexcept
{

  Real sx = sin(radians(_rot.m_x/2.0f));
  Real sy = sin(radians(_rot.m_y/2.0f));
  Real sz = sin(radians(_rot.m_z/2.0f));
  Real cx = cos(radians(_rot.m_x/2.0f));
  Real cy = cos(radians(_rot.m_y/2.0f));
  Real cz = cos(radians(_rot.m_z/2.0f));

  m_s=cx*cy*cz + sx*sy*sz,
  m_x=sx*cy*cz - cx*sy*sz,
  m_y=cx*sy*cz + sx*cy*sz,
  m_z=cx*cy*sz - sx*sy*cz;

}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator *(const Quaternion& _q)const noexcept
{
  Quaternion ret(0.0,0.0,0.0,0.0);
  // if we have two Quaternions Qa Qb we get the following
  // Qa*Qb
  // first we do the scalar parts SaSb - A . B (where A and B are  the vector parts) . the dot product
  ret.m_s=(m_s*_q.m_s)-(m_x*_q.m_x+m_y*_q.m_y+m_z*_q.m_z);
  // now the x component of the vector part
  // this is the form of saB + sbA + sbA + A x B (X is the cross product)

  Vec4 v1( m_x, m_y, m_z );
  Vec4 v2( _q.m_x, _q.m_y, _q.m_z );

  Vec4 vectorPart = (m_s * v2) + (_q.m_s * v1) + (v1.cross(v2));

  ret.m_x=vectorPart.m_x;
  ret.m_y=vectorPart.m_y;
  ret.m_z=vectorPart.m_z;
  return ret;
}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator *=(const Quaternion& _q) noexcept
{
		// as we have already written the code to do the mult above re-use
		*this=*this*_q;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator +(const Quaternion& _q) const noexcept
{
	Quaternion ret;
	ret.m_s=m_s+_q.m_s;
	ret.m_x=m_x+_q.m_x;
	ret.m_y=m_y+_q.m_y;
	ret.m_z=m_z+_q.m_z;
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator -(const Quaternion& _q) const noexcept
{
	Quaternion ret;
	ret.m_s=m_s-_q.m_s;
	ret.m_x=m_x-_q.m_x;
	ret.m_y=m_y-_q.m_y;
	ret.m_z=m_z-_q.m_z;
	return ret;
}


//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator +=(const Quaternion& _q) noexcept
{
	// re-call the code from above
	*this=*this+_q;
}
//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator -=(const Quaternion& _q) noexcept
{
	// re-call the code from above
	*this=*this-_q;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator *(Real _s) const noexcept
{
	return Quaternion(m_s*_s,m_x*_s,m_y*_s,m_z*_s);

}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::operator *=(Real _s) noexcept
{
	m_s*=_s;
	m_x*=_s;
	m_y*=_s;
	m_z*=_s;
}



//----------------------------------------------------------------------------------------------------------------------
void Quaternion::normalise() noexcept
{
	Real inverseOverOne = 1.0f/magnitude();
	m_s*=inverseOverOne;
	m_x*=inverseOverOne;
	m_y*=inverseOverOne;
	m_z*=inverseOverOne;
}


//----------------------------------------------------------------------------------------------------------------------
Real Quaternion::magnitude()const noexcept
{
	return static_cast<Real>( sqrt(m_s*m_s + m_x*m_x + m_y*m_y + m_z*m_z) );
}

//----------------------------------------------------------------------------------------------------------------------
bool Quaternion::operator == (const Quaternion& _q)const noexcept
{
	return (
					FCompare(_q.m_s,m_s) &&
					FCompare(_q.m_x,m_x) &&
					FCompare(_q.m_y,m_y) &&
					FCompare(_q.m_z,m_z)
				 );
}


//----------------------------------------------------------------------------------------------------------------------
Vec4 Quaternion::operator* (const Vec4 &_vec) const noexcept
{
	Quaternion temp=-*this;
	Quaternion point(0.0,_vec.m_x,_vec.m_y,_vec.m_z);
	point = temp*point* *this;
	return Vec4(point.m_x,point.m_y,point.m_z,1.0);
}




void Quaternion::rotateX(Real _angle) noexcept
{
_angle/=2.0;
// q=[cos 1/2 theta, sin 1/2 theta V]
m_s=cos(radians(_angle));
m_x=sin(radians(_angle));
m_y=0;
m_z=0;
}

void Quaternion::rotateY(Real _angle) noexcept
{
	_angle/=2.0;
	// q=[cos 1/2 theta, sin 1/2 theta V]
	m_s=cos(radians(_angle));
	m_x=0;

	m_y=sin(radians(_angle));
	m_z=0;
}

void Quaternion::rotateZ(Real _angle) noexcept
{

	_angle/=2.0;
	// q=[cos 1/2 theta, sin 1/2 theta V]
	m_s=cos(radians(_angle));
	m_x=0;
	m_y=0;
	m_z=sin(radians(_angle));

}


void Quaternion::fromAxisAngle(const Vec3& _axis, Real _angle) noexcept
{
  Vec3 axis = _axis;
  axis.normalize();
  _angle=radians(_angle);
  Real sinAngle = static_cast<Real>(sin( _angle / 2.0f ));
  Real cosAngle = static_cast<Real>(cos( _angle / 2.0f ));
  m_s = cosAngle;
  m_x = axis.m_x * sinAngle;
  m_y = axis.m_y * sinAngle;
  m_z = axis.m_z * sinAngle;
}


void Quaternion::fromEulerAngles(const Real _x,const Real _y,const Real _z) noexcept
{
  Real sx = sin(radians(_x/2.0f));
  Real sy = sin(radians(_y/2.0f));
  Real sz = sin(radians(_z/2.0f));
  Real cx = cos(radians(_x/2.0f));
  Real cy = cos(radians(_y/2.0f));
  Real cz = cos(radians(_z/2.0f));

  m_s=cx*cy*cz + sx*sy*sz,
  m_x=sx*cy*cz - cx*sy*sz,
  m_y=cx*sy*cz + sx*cy*sz,
  m_z=cx*cy*sz - sx*sy*cz;
}

void Quaternion::rotatePoint(const Quaternion& _r,Vec3 & io_p) noexcept
{
Quaternion temp = -_r;
Quaternion point(0.0,io_p.m_x, io_p.m_y, io_p.m_z);
point = temp * point * _r;
io_p.set(point.m_x, point.m_y, point.m_z);
}

void Quaternion::toAxisAngle(Vec3& o_axis,Real &o_angle) noexcept
{
  o_angle = degrees(static_cast<Real>(acos( m_s ) * 2.0f));
  Real sinA = static_cast<Real>(sqrt( 1.0f - m_s * m_s ));
  if( fabs( sinA ) < 0.0005f )
  {
    sinA = 1.0f;
  }
  o_axis.m_x = m_x / sinA;
  o_axis.m_y = m_y / sinA;
  o_axis.m_z = m_z / sinA;
}

Quaternion Quaternion::slerp(const Quaternion &_q1, const Quaternion &_q2, const Real &_t) noexcept
{
  // based on the http://ggt.sourceforge.net/ gmtl version from assimp
  Quaternion out;
  // calc cosine theta
  Real cosom = _q1.m_x * _q2.m_x + _q1.m_y * _q2.m_y + _q1.m_z * _q2.m_z + _q1.m_s * _q2.m_s;

  // adjust signs (if necessary)
  Quaternion end = _q2;
  if( cosom < static_cast<Real>(0.0))
  {
    cosom = -cosom;
    end.m_x = -end.m_x;   // Reverse all signs
    end.m_y = -end.m_y;
    end.m_z = -end.m_z;
    end.m_s = -end.m_s;
  }

  // Calculate coefficients
  Real sclp, sclq;
  if( (static_cast<Real>(1.0) - cosom) > static_cast<Real>(0.0001)) // 0.0001 -> some epsillon
  {
    // Standard case (slerp)
    Real omega, sinom;
    omega = acos( cosom); // extract theta from dot product's cos theta
    sinom = sin( omega);
    sclp  = sin( (static_cast<Real>(1.0) - _t) * omega) / sinom;
    sclq  = sin( _t * omega) / sinom;
  }
  else
  {
    // Very close, do linear interp (because it's faster)
    sclp = static_cast<Real>(1.0) - _t;
    sclq = _t;
  }

  out.m_x = sclp * _q1.m_x + sclq * end.m_x;
  out.m_y = sclp * _q1.m_y + sclq * end.m_y;
  out.m_z = sclp * _q1.m_z + sclq * end.m_z;
  out.m_s = sclp * _q1.m_s + sclq * end.m_s;
  return out;
}



Mat4 Quaternion::toMat4() const noexcept
{
  // written by Rob Bateman
  // sacrafice a few bytes to pre-calculate some values
  Real xx = m_x * m_x;
  Real xy = m_x * m_y;
  Real xz = m_x * m_z;
  Real xs = m_x * m_s;
  Real yy = m_y * m_y;
  Real yz = m_y * m_z;
  Real ys = m_y * m_s;
  Real zz = m_z * m_z;
  Real zs = m_z * m_s;
  Mat4 o;
  o.m_openGL[0] = 1.0f - 2.0f * (yy+zz);
  o.m_openGL[1] = 2.0f * (xy+zs);
  o.m_openGL[2] = 2.0f * (xz-ys);
  o.m_openGL[3] = 0.0f;

  // [4] -> [7]
  o.m_openGL[4] = 2.0f * (xy-zs);
  o.m_openGL[5] = 1.0f - 2.0f * (xx+zz);
  o.m_openGL[6] = 2.0f * (yz+xs);
  o.m_openGL[7] = 0.0f;

  // [8] -> [11]
  o.m_openGL[8] = 2.0f * (xz+ys);
  o.m_openGL[9] = 2.0f * (yz-xs);
  o.m_openGL[10]= 1.0f - 2.0f * (xx+yy);
  o.m_openGL[11] = 0.0f;

  // [12] -> [15]
  o.m_openGL[12] = 0.0f;
  o.m_openGL[13] = 0.0f;
  o.m_openGL[14] = 0.0f;
  o.m_openGL[15] = 1.0f;
  return o;
}

Mat4 Quaternion::toMat4Transpose() const noexcept
{
  // written by Rob Bateman
  // sacrafice a few bytes to pre-calculate some values
  Real xx = m_x * m_x;
  Real xy = m_x * m_y;
  Real xz = m_x * m_z;
  Real xs = m_x * m_s;
  Real yy = m_y * m_y;
  Real yz = m_y * m_z;
  Real ys = m_y * m_s;
  Real zz = m_z * m_z;
  Real zs = m_z * m_s;
  Mat4 o;
  o.m_openGL[0] = 1.0f - 2.0f * (yy+zz);
  o.m_openGL[4] = 2.0f * (xy+zs);
  o.m_openGL[8] = 2.0f * (xz-ys);
  o.m_openGL[12] = 0.0f;

  // [4] -> [7]
  o.m_openGL[1] = 2.0f * (xy-zs);
  o.m_openGL[5] = 1.0f - 2.0f * (xx+zz);
  o.m_openGL[9] = 2.0f * (yz+xs);
  o.m_openGL[13] = 0.0f;

  // [8] -> [11]
  o.m_openGL[2] = 2.0f * (xz+ys);
  o.m_openGL[6] = 2.0f * (yz-xs);
  o.m_openGL[10]= 1.0f - 2.0f * (xx+yy);
  o.m_openGL[14] = 0.0f;

  // [12] -> [15]
  o.m_openGL[3] = 0.0f;
  o.m_openGL[7] = 0.0f;
  o.m_openGL[11] = 0.0f;
  o.m_openGL[15] = 1.0f;
  return o;
}




} // end ngl namespace
//----------------------------------------------------------------------------------------------------------------------



