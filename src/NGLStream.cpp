#include "Camera.h"
#include "Colour.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Quaternion.h"
#include <iostream>
#include <limits>
#include <iomanip>
namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator<<( std::ostream& _output, const Vec2& _v	)
{
  return _output<<"["<<_v.m_x<<","<<_v.m_y<<"]";
}
//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::istream& operator>>( std::istream& _input, Vec2& _s	)
{
  return _input >> _s.m_x >> _s.m_y ;
}


//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator<<( std::ostream& _output, const Vec3& _v	)
{
  return _output<<"["<<_v.m_x<<","<<_v.m_y<<","<<_v.m_z<<"]";
}
//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::istream& operator>>(std::istream& _input,	 Vec3& _s	)
{
  return _input >> _s.m_x >> _s.m_y >> _s.m_z;
}


//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator<<( std::ostream& _output, const Vec4& _v )
{
  return _output<<"["<<_v.m_x<<","<<_v.m_y<<","<<_v.m_z<<","<<_v.m_w<<"]";
}
//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::istream& operator>>(std::istream& _input, Vec4& _s)
{
  return _input >> _s.m_x >> _s.m_y >> _s.m_z >> _s.m_w;
}

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator<<(std::ostream& _output, const Camera &_c	)
{
  return _output<<"m_eye"<<_c.getEye()<<" m_look"<<_c.getLook()<<" Up"<<_c.getUp();
}

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT  std::ostream&  operator<<( std::ostream &_output, const Colour& _s )
{
 return _output<<"["<<_s.m_r<<","<<_s.m_g<<","<<_s.m_b<<","<<_s.m_a<<"]";
}

//----------------------------------------------------------------------------------------------------------------------

NGL_DLLEXPORT  std::istream& operator>>( std::istream &_input, Colour &_s )
{
 _input >> _s.m_r >> _s.m_g >> _s.m_b >> _s.m_a;
 return _input;
}

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator<<(std::ostream &_output,const Mat3 &_m )
{
  std::cout.setf(std::ios::fixed|std::ios::adjustfield|std::ios::showpos);
  std::cout.precision(12);
  return _output
  <<"["<<_m.m_00<<","<<_m.m_01<<","<<_m.m_02<<","<<"]"<<std::endl
  <<"["<<_m.m_10<<","<<_m.m_11<<","<<_m.m_12<<","<<"]"<<std::endl
  <<"["<<_m.m_20<<","<<_m.m_21<<","<<_m.m_22<<","<<"]"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator<<(std::ostream &_output,const Mat4 &_m)
{
  std::cout.setf(std::ios::fixed|std::ios::adjustfield|std::ios::showpos);
 // std::cout.precision(std::numeric_limits<double>::digits10 + 1);
  return _output
        <<"["<<_m.m_00<<","<<_m.m_10<<","<<_m.m_20<<","<<_m.m_30<<"]"<<std::endl
        <<"["<<_m.m_01<<","<<_m.m_11<<","<<_m.m_21<<","<<_m.m_31<<"]"<<std::endl
        <<"["<<_m.m_02<<","<<_m.m_12<<","<<_m.m_22<<","<<_m.m_32<<"]"<<std::endl
        <<"["<<_m.m_03<<","<<_m.m_13<<","<<_m.m_23<<","<<_m.m_33<<"]"<<std::endl;

}

//----------------------------------------------------------------------------------------------------------------------
//NGL_DLLEXPORT std::istream& operator >> ( std::istream& _ifs, Quaternion &_q )
//{
// //return _ifs >> _q.setS >> _q.m_x >> _q.m_y >> _q.m_z;
//}
//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT std::ostream& operator << ( std::ostream& i_s, const Quaternion &i_q)
{
  return i_s << i_q.getS() << " [" << i_q.getX() << "i," << i_q.getY() << "j," << i_q.getZ()<<"k]";
}

}
