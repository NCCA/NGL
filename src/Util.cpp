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
#include "Types.h"
#include "Mat4.h"
#include "Vec4.h"
#include <cmath>
#include <iostream>
#include <string>
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.cpp
/// @brief implementation files for Util class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT Vec3 calcNormal(const Vec4 &_p1, const Vec4 &_p2, const Vec4 &_p3 ) noexcept
{

	Real coa, cob, coc ;
	Real px1, py1, pz1 ;
	Real px2, py2, pz2 ;
	Real px3, py3, pz3 ;
	Real absvec;
	Vec3 norm;
	px1 = _p1.m_x; py1 = _p1.m_y; pz1 = _p1.m_z;
	px2 = _p2.m_x; py2 = _p2.m_y; pz2 = _p2.m_z;
	px3 = _p3.m_x; py3 = _p3.m_y; pz3 = _p3.m_z;

	// generate cross product

	coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
	cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
	coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

  // normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;
  norm.m_x = coa/absvec ;
  norm.m_y = cob/absvec ;
  norm.m_z = coc/absvec ;

  return norm;
}


//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT Vec3 calcNormal (const Vec3 &_p1,  const Vec3 &_p2, const Vec3 &_p3  ) noexcept
{

  Real coa, cob, coc ;
  Real px1, py1, pz1 ;
  Real px2, py2, pz2 ;
  Real px3, py3, pz3 ;
  Real absvec;
  Vec3 norm;
  px1 = _p1.m_x; py1 = _p1.m_y; pz1 = _p1.m_z;
  px2 = _p2.m_x; py2 = _p2.m_y; pz2 = _p2.m_z;
  px3 = _p3.m_x; py3 = _p3.m_y; pz3 = _p3.m_z;

  // generate cross product

  coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
  cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
  coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

  // normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;
  norm.m_x = coa/absvec ;
  norm.m_y = cob/absvec ;
  norm.m_z = coc/absvec ;

  return norm;
}

NGL_DLLEXPORT Real radians(const Real _deg )
{
  return (_deg/180.0f) * static_cast<Real>(M_PI);
}

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT Real degrees( const Real _rad   ) noexcept
{
  return (_rad / static_cast<Real>(M_PI)) * 180.0f;
}


NGL_DLLEXPORT  void NGLCheckGLError( const std::string  &_file, const int _line ) noexcept
{
 //std::cout<<"NGLCheckGLError Called ______________________\n";
 auto errNum = glGetError();
  while (errNum != GL_NO_ERROR)
  {
   // std::cout<<errNum<<"\n";
    std::string str;
    switch(errNum)
    {
      case GL_INVALID_ENUM : str="GL_INVALID_ENUM error"; break;
      case GL_INVALID_VALUE : str="GL_INVALID_VALUE error"; break;
      case GL_INVALID_OPERATION : str="GL_INVALID_OPERATION error"; break;
      case GL_OUT_OF_MEMORY : str="GL_OUT_OF_MEMORY error"; break;
      case GL_INVALID_FRAMEBUFFER_OPERATION : str="GL_INVALID_FRAMEBUFFER_OPERATION error";  break;
      #ifndef USINGIOS_
        case GL_STACK_UNDERFLOW : str= "GL_STACK_UNDERFLOW error"; break;
        case GL_STACK_OVERFLOW : str= "GL_STACK_OVERFLOW error"; break;
      #endif
      // this should be in the spec but it's not on the mac! will check linux
      default : break;
    }
    if(errNum !=GL_NO_ERROR)
    {
      std::cerr<<"GL error "<< str<<" line : "<<_line<<" file : "<<_file<<"\n";
    }
    errNum = glGetError();

   }
}


NGL_DLLEXPORT Mat4 perspective(Real _fovy,Real _aspect, Real _zNear, Real _zFar) noexcept
{
  Mat4 result;
  //glm usues a zero matrix and we are copying their funcs (see my unit tests here
  // https://github.com/NCCA/VectorGLM)

  result.null();
//  Real tanHalfFovy = tan(radians(_fovy) / 2.0f);

//  result.m_00  = 1.0f / (_aspect * tanHalfFovy);
//  result.m_11   = 1.0f / (tanHalfFovy);
//  result.m_22   = - (_zFar + _zNear) / (_zFar - _zNear);
//  result.m_23   = - 1.0;
//  result.m_32  = - (2.0f * _zFar * _zNear) / (_zFar - _zNear);

    Real range = tanf(radians(_fovy / 2.0f)) * _zNear;
    Real left = -range * _aspect;
    Real right = range * _aspect;
    Real bottom = -range;
    Real top = range;
    result.m_00 = (2.0f * _zNear) / (right - left);
    result.m_11 = (2.0f * _zNear) / (top - bottom);
    result.m_22 = - (_zFar + _zNear) / (_zFar - _zNear);
    result.m_23 = - 1.0f;
    result.m_32 = - (2.0f* _zFar * _zNear) / (_zFar - _zNear);
    return result;
}


NGL_DLLEXPORT Mat4 perspectiveFov(Real const & _fov, Real const & _width, Real const & _height, Real const & _zNear, Real const & _zFar) noexcept
{
    Real rad = radians(_fov);
    Real h = cosf(0.5f * rad) / sinf(0.5f * rad);
    Real w = h * _height / _width;
    Mat4 result;
    //glm usues a zero matrix and we are copying their funcs (see my unit tests here
    // https://github.com/NCCA/VectorGLM)
    result.null();
    result.m_00 = w;
    result.m_11 = h;
    result.m_22 = - (_zFar + _zNear) / (_zFar - _zNear);
    result.m_23 = - 1.0f;
    result.m_32 = - (2.0f* _zFar * _zNear) / (_zFar - _zNear);
    return result;
}


NGL_DLLEXPORT Mat4 infinitePerspective(Real _fovy, Real _aspect, Real _zNear) noexcept
{
  Real const range = tanf(radians(_fovy / 2.0f)) * _zNear;
  Real left = -range * _aspect;
  Real right = range * _aspect;
  Real bottom = -range;
  Real top = range;

  Mat4 result;
  //glm usues a zero matrix and we are copying their funcs (see my unit tests here
  // https://github.com/NCCA/VectorGLM)
  result.null();
  result.m_00 = (2.0f * _zNear) / (right - left);
  result.m_11 = (2.0f * _zNear) / (top - bottom);
  result.m_22 = - 1.0f;
  result.m_23 = - 1.0f;
  result.m_32 = - 2.0f * _zNear;
  return result;
}


NGL_DLLEXPORT Mat4 lookAt(const Vec3  & _eye,const Vec3  & _center,const Vec3  & _up) noexcept
{

    Vec3 n =   _center-_eye;
    Vec3 u = _up;
    Vec3 v = n.cross(u);
    u = v.cross(n);
    n.normalize();
    v.normalize();
    u.normalize();

    Mat4 result(1.0f);
    result.m_00= v.m_x;
    result.m_10= v.m_y;
    result.m_20= v.m_z;
    result.m_01= u.m_x;
    result.m_11= u.m_y;
    result.m_21= u.m_z;
    result.m_02=-n.m_x;
    result.m_12=-n.m_y;
    result.m_22=-n.m_z;
    result.m_30=-_eye.dot(v);
    result.m_31=-_eye.dot(u);
    result.m_32= _eye.dot(n);
    return result;
}

NGL_DLLEXPORT Mat4 ortho(Real _left, Real _right, Real _bottom, Real _top, Real _zNear, Real _zFar) noexcept
{
  Mat4 result(1.0f);
  result.m_00= 2.0f / (_right - _left);
  result.m_11= 2.0f / (_top - _bottom);
  result.m_22= - 2.0f / (_zFar - _zNear);
  result.m_30= - (_right + _left) / (_right - _left);
  result.m_31= - (_top + _bottom) / (_top - _bottom);
  result.m_32= - (_zFar + _zNear) / (_zFar - _zNear);
  return result;
}

NGL_DLLEXPORT Mat4 ortho(Real _left, Real _right, Real _bottom, Real _top) noexcept
{
  Mat4 result(1);
  result.m_00= Real(2) / (_right - _left);
  result.m_11= Real(2) / (_top - _bottom);
  result.m_22= - Real(1);
  result.m_30= - (_right + _left) / (_right - _left);
  result.m_31= - (_top + _bottom) / (_top - _bottom);
  return result;
}

NGL_DLLEXPORT Mat4 frustum(Real _left, Real _right, Real _bottom, Real _top, Real _nearVal, Real _farVal) noexcept
{
  Mat4 result;
  result.null();
  result.m_00 = (2.0f * _nearVal) / (_right - _left);
  result.m_11 = (2.0f * _nearVal) / (_top - _bottom);
  result.m_20 = (_right + _left) / (_right - _left);
  result.m_21 = (_top + _bottom) / (_top - _bottom);
  result.m_22 = -(_farVal + _nearVal) / (_farVal - _nearVal);
  result.m_23 = -1.0f;
  result.m_32 = -(2.0f * _farVal * _nearVal) / (_farVal - _nearVal);
  return result;
}

NGL_DLLEXPORT Vec3 unProject(const Vec3 &_win, const Mat4 &_model, const Mat4 &_project, const Vec4 &_viewport ) noexcept
{
  ngl::Mat4 p,m;
  p=_project;
  m=_model;

  Mat4 inverse=( p.transpose()*m.transpose()).inverse();

  Vec4 tmp(0,0,_win.m_z,1.0f);
  // convert into NDC
  tmp.m_x=(2.0f * _win.m_x) / _viewport.m_openGL[2] - 1.0f;
  tmp.m_y=1.0f - (2.0f * _win.m_y) / _viewport.m_openGL[3];
  // scale by inverse MV * Project transform
  Vec4 obj=inverse*tmp;
  // Scale by w
  obj/=obj.m_w;
  return obj.toVec3();
}

NGL_DLLEXPORT Vec3 project(const Vec3 &_pos, const Mat4 &_model, const Mat4 &_project, const Vec4 &_viewport ) noexcept
{
  Vec4 tmp(_pos, 1.0);
//  tmp =   tmp*_model;
//  tmp =   tmp * _project;
  tmp = _model*_project*tmp;
  tmp /= tmp.m_w;
  tmp = tmp * float(0.5);// + float(0.5);
  tmp+=ngl::Vec3(0.5,0.5,0.5);
  tmp[0] = tmp[0] * float(_viewport[2]) + float(_viewport[0]);
  tmp[1] = tmp[1] * float(_viewport[3]) + float(_viewport[1]);

  return tmp.toVec3();
}

// for more details see this site some greate stuff here (this code was modified from it)
// http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
NGL_DLLEXPORT bool isPowerOfTwo (unsigned int _x) noexcept
{
 while (((_x % 2) == 0) && _x > 1) /* While x is even and > 1 */
 {
     _x /= 2;
 }
  return (_x == 1);
}

// from http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

NGL_DLLEXPORT unsigned int nextPow2(unsigned int _x) noexcept
{
	_x -= 1;
	_x |= _x >> 1;
	_x |= _x >> 2;
	_x |= _x >> 4;
	_x |= _x >> 8;
	_x |= _x >> 16;
	return _x + 1;
}


} // end of namespace

//----------------------------------------------------------------------------------------------------------------------



