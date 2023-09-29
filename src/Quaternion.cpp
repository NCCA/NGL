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
#include <algorithm>
namespace ngl
{

Quaternion::Quaternion(const Mat4 &_m) noexcept
{  
  if ( auto T = 1 + _m.m_openGL[0] + _m.m_openGL[5] + _m.m_openGL[10]; T > 0.00000001f ) //to avoid large distortions!
  {
    auto S = sqrtf(T) * 2.0f;
    m_x = ( _m.m_openGL[6] - _m.m_openGL[9] ) / S;
    m_y = ( _m.m_openGL[8] - _m.m_openGL[2] ) / S;
    m_z = ( _m.m_openGL[1] - _m.m_openGL[4] ) / S;
    m_s = 0.25f * S;
  }
  else if ( _m.m_openGL[0] > _m.m_openGL[5] &&
       _m.m_openGL[0] > _m.m_openGL[10] )
  {		// Column 0:
    auto S  = sqrtf( 1.0f + _m.m_openGL[0] - _m.m_openGL[5] - _m.m_openGL[10] ) * 2.0f;
    m_x = 0.25f * S;
    m_y = (_m.m_openGL[1] + _m.m_openGL[4] ) / S;
    m_z = (_m.m_openGL[8] + _m.m_openGL[2] ) / S;
    m_s = (_m.m_openGL[6] - _m.m_openGL[9] ) / S;
  }
  else if ( _m.m_openGL[5] > _m.m_openGL[10] )
  {			// Column 1:
    auto S  = sqrtf( 1.0f + _m.m_openGL[5] - _m.m_openGL[0] - _m.m_openGL[10] ) * 2.0f;
    m_x = (_m.m_openGL[1] + _m.m_openGL[4] ) / S;
    m_y = 0.25f * S;
    m_z = (_m.m_openGL[6] + _m.m_openGL[9] ) / S;
    m_s = (_m.m_openGL[8] - _m.m_openGL[2] ) / S;
  }
  else
  {										// Column 2:
    auto S  = sqrtf( 1.0f + _m.m_openGL[10] - _m.m_openGL[0] - _m.m_openGL[5] ) * 2.0f;
    m_x = (_m.m_openGL[8] + _m.m_openGL[2] ) / S;
    m_y = (_m.m_openGL[6] + _m.m_openGL[9] ) / S;
    m_z = 0.25f * S;
    m_s = (_m.m_openGL[1] - _m.m_openGL[4] ) / S;
  }
}

Quaternion::Quaternion(const Vec3 &_rot) noexcept
{

  auto sx = sinf(radians(_rot.m_x/2.0f));
  auto sy = sinf(radians(_rot.m_y/2.0f));
  auto sz = sinf(radians(_rot.m_z/2.0f));
  auto cx = cosf(radians(_rot.m_x/2.0f));
  auto cy = cosf(radians(_rot.m_y/2.0f));
  auto cz = cosf(radians(_rot.m_z/2.0f));

  m_s=cx*cy*cz + sx*sy*sz;
  m_x=sx*cy*cz - cx*sy*sz;
  m_y=cx*sy*cz + sx*cy*sz;
  m_z=cx*cy*sz - sx*sy*cz;

}

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


Quaternion & Quaternion::operator *=(const Quaternion& _q) noexcept
{
		// as we have already written the code to do the mult above re-use
		*this=*this*_q;
    return *this;
}

Quaternion Quaternion::operator +(const Quaternion& _q) const noexcept
{
	Quaternion ret;
	ret.m_s=m_s+_q.m_s;
	ret.m_x=m_x+_q.m_x;
	ret.m_y=m_y+_q.m_y;
	ret.m_z=m_z+_q.m_z;
	return ret;
}

Quaternion Quaternion::operator -(const Quaternion& _q) const noexcept
{
	Quaternion ret;
	ret.m_s=m_s-_q.m_s;
	ret.m_x=m_x-_q.m_x;
	ret.m_y=m_y-_q.m_y;
	ret.m_z=m_z-_q.m_z;
	return ret;
}

Quaternion & Quaternion::operator +=(const Quaternion& _q) noexcept
{
  m_s=m_s+_q.m_s;
  m_x=m_x+_q.m_x;
  m_y=m_y+_q.m_y;
  m_z=m_z+_q.m_z;
  return *this;

}

Quaternion &Quaternion::operator -=(const Quaternion& _q) noexcept
{
    m_s=m_s-_q.m_s;
    m_x=m_x-_q.m_x;
    m_y=m_y-_q.m_y;
    m_z=m_z-_q.m_z;
    return *this;
}


Quaternion Quaternion::operator *(Real _s) const noexcept
{
	return Quaternion(m_s*_s,m_x*_s,m_y*_s,m_z*_s);

}


void Quaternion::operator *=(Real _s) noexcept
{
	m_s*=_s;
	m_x*=_s;
	m_y*=_s;
	m_z*=_s;
}

void Quaternion::normalise() noexcept
{
	Real inverseOverOne = 1.0f/magnitude();
	m_s*=inverseOverOne;
	m_x*=inverseOverOne;
	m_y*=inverseOverOne;
	m_z*=inverseOverOne;
}


Quaternion Quaternion::inverse() const noexcept
{

  auto scale=this->magnitude();
  scale=1.0f/(scale*scale);
  auto conj=this->conjugate();
  return conj*scale;
}



Real Quaternion::magnitude()const noexcept
{
  return  sqrtf(m_s*m_s + m_x*m_x + m_y*m_y + m_z*m_z);
}

bool Quaternion::operator == (const Quaternion& _q)const noexcept
{
	return (
					FCompare(_q.m_s,m_s) &&
					FCompare(_q.m_x,m_x) &&
					FCompare(_q.m_y,m_y) &&
					FCompare(_q.m_z,m_z)
				 );
}



Vec4 Quaternion::operator *(const Vec4 &_vec) const noexcept
{

  Vec4 qv(m_x,m_y,m_z);
  Vec4 uv(qv.cross(_vec));
  Vec4 uuv(qv.cross(uv));
  return _vec + ((uv * m_s) + uuv) * 2.0f;
}

float Quaternion::dot(const Quaternion &_lhs)const  noexcept
{
  return m_x * _lhs.m_x + m_y * _lhs.m_y + m_z * _lhs.m_z + m_s * _lhs.m_s;
}

float Quaternion::dot(const Quaternion &_lhs, const Quaternion &_rhs) noexcept
{
  return _rhs.m_x * _lhs.m_x + _rhs.m_y * _lhs.m_y + _rhs.m_z * _lhs.m_z + _rhs.m_s * _lhs.m_s;
}


Quaternion Quaternion::rotateX(Real _angle) noexcept
{
  Quaternion q;
  _angle/=2.0f;
  // q=[cos 1/2 theta, sin 1/2 theta V]
  q.m_s=cosf(radians(_angle));
  q.m_x=sinf(radians(_angle));
  q.m_y=0.0f;
  q.m_z=0.0f;
  return q;
}

Quaternion Quaternion::rotateY(Real _angle) noexcept
{
    Quaternion q;
    _angle/=2.0f;
    // q=[cos 1/2 theta, sin 1/2 theta V]
    q.m_s=cosf(radians(_angle));
    q.m_x=0.0f;
    q.m_y=sinf(radians(_angle));
    q.m_z=0.0f;
    return q;
}

Quaternion Quaternion::rotateZ(Real _angle) noexcept
{
  Quaternion q;
  _angle/=2.0f;
	// q=[cos 1/2 theta, sin 1/2 theta V]
  q.m_s=cosf(radians(_angle));
  q.m_x=0.0f;
  q.m_y=0.0f;
  q.m_z=sinf(radians(_angle));
  return q;
}

void Quaternion::fromAxisAngle(const Vec3& _axis, Real _angle) noexcept
{
  Vec3 axis = _axis;
  axis.normalize();
  _angle=radians(_angle);
  auto sinAngle = sinf( _angle / 2.0f );
  auto cosAngle = cosf( _angle / 2.0f );
  m_s = cosAngle;
  m_x = axis.m_x * sinAngle;
  m_y = axis.m_y * sinAngle;
  m_z = axis.m_z * sinAngle;
}


void Quaternion::fromEulerAngles(const Real _x,const Real _y,const Real _z) noexcept
{
  auto sx = sinf(radians(_x/2.0f));
  auto sy = sinf(radians(_y/2.0f));
  auto sz = sinf(radians(_z/2.0f));
  auto cx = cosf(radians(_x/2.0f));
  auto cy = cosf(radians(_y/2.0f));
  auto cz = cosf(radians(_z/2.0f));

  m_s=cx*cy*cz + sx*sy*sz;
  m_x=sx*cy*cz - cx*sy*sz;
  m_y=cx*sy*cz + sx*cy*sz;
  m_z=cx*cy*sz - sx*sy*cz;
}

void Quaternion::rotatePoint(const Quaternion& _r,Vec3 & io_p) const noexcept
{
Quaternion temp = -_r;
Quaternion point(0.0,io_p.m_x, io_p.m_y, io_p.m_z);
point = temp * point * _r;
io_p.set(point.m_x, point.m_y, point.m_z);
}

void Quaternion::toAxisAngle(Vec3& o_axis,Real &o_angle) const noexcept
{
  o_angle = degrees(acosf( m_s ) * 2.0f);
  auto sinA = sqrtf( 1.0f - m_s * m_s );
  if( fabsf( sinA ) < 0.0005f )
  {
    sinA = 1.0f;
  }
  o_axis.m_x = m_x / sinA;
  o_axis.m_y = m_y / sinA;
  o_axis.m_z = m_z / sinA;
}

Quaternion Quaternion::qlerp( Quaternion _v0, Quaternion _v1, Real _t) noexcept
{

  // converts to Vec4 to lerp
  ngl::Vec4 start(_v0.m_x,_v0.m_y,_v0.m_z,_v0.m_s);
  ngl::Vec4 end(_v1.m_x,_v1.m_y,_v1.m_z,_v1.m_s);
  auto interp = lerp(start,end,_t);
  interp.normalize();
  return Quaternion(interp.m_w,interp.m_x,interp.m_y,interp.m_z);
}


void Quaternion::negate()
{
  m_s=-m_s;
  m_x=-m_x;
  m_y=-m_y;
  m_z=-m_z;

}

Quaternion Quaternion::slerp( Quaternion _v0,  Quaternion _v1,  Real _t) noexcept
{

  auto dotp = dot(_v0,_v1);
  constexpr float thereshold=0.9995f;
  if( dotp < 0.0f)
  {
    dotp = -dotp;
    _v1.negate();
  }

  // quicker to do linear interp here as they are now close
  if(dotp > thereshold)
  {
    return lerp(_v0,_v1,_t);
  }
  dotp = std::clamp(dotp,-1.0f,1.0f);
  auto theta_0 =acosf(dotp);
  auto theta = theta_0*_t;
  Quaternion v2 = _v1 - _v0 * dotp;
  v2.normalise();
  return _v0 * cosf(theta) + v2 * sinf(theta);
}



Mat4 Quaternion::toMat4() const noexcept
{
  // written by Rob Bateman
  // sacrifice a few bytes to pre-calculate some values
  auto xx = m_x * m_x;
  auto xy = m_x * m_y;
  auto xz = m_x * m_z;
  auto xs = m_x * m_s;
  auto yy = m_y * m_y;
  auto yz = m_y * m_z;
  auto ys = m_y * m_s;
  auto zz = m_z * m_z;
  auto zs = m_z * m_s;
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





} // end ngl namespace




