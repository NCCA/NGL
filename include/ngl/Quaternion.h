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
#ifndef QUATERNION_H_
#define QUATERNION_H_

/// @file  Quaternion.h
/// @author  Jon Macey with thanks to John Vince and Rob Bateman
/// @brief  Defines the class Quaternion based on John Vinces lecture notes
/// basically we have a scalar part and then a vector part (stored as x,y,z)
/// each component of the Quat is stored as a Real value.
/// @class Quaternion "include/Quaternion.h"

// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Vec4.h"

namespace ngl
{

// need to pre-declare the matrix class
class Mat4;


class NGL_DLLEXPORT Quaternion
{

  public:
    Quaternion()=default;
    ~Quaternion()=default;
    Quaternion(const Quaternion &)=default;
    
    /// @brief constructor I use the format used in John Vinces book where we have a scalar and a vector, some libs do this
    /// the otherway round and use the w component, make sure you check if using different libs
    /// @param [in]  _s  -  the s component of the quaternion
    /// @param [in]  _x  -  the x component of the quaternion
    /// @param [in]  _y  -  the y component of the quaternion
    /// @param [in]  _z  -  the z component of the quaternion
    
    Quaternion(const Real _s,const Real _x,const Real _y,const Real _z) noexcept:
            m_s(_s),
            m_x(_x),
            m_y(_y),
            m_z(_z) {}
    
    /// @brief constructor passing in a matrix
    /// @param _m the matrix to build the quat from
    /// this is useful when using the slerp so we can interpolate
    /// between two rotation matrices
    
    Quaternion(const Mat4 &_m) noexcept;
    
    /// @brief constructor passing in a Vec3 which represents the rolls around
    /// the x y and z axis
    /// @param _rot the roatation to build the quat from
    /// this is useful when using the slerp so we can interpolate
    /// between two rotation matrices
    
    Quaternion(const Vec3 &_rot) noexcept;
    
    /// @brief method to set the quaternion values
    /// @param[in] _x the x value
    /// @param[in] _y the y value
    /// @param[in] _z the z value
    /// @param[in] _w the w value
    
    void set( Real _s,Real _x,Real _y,Real _z) noexcept
    {
      m_s=_s;
      m_x=_x;
      m_y=_y;
      m_z=_z;
    }
    
    /// @brief accesor for the scalar part
    /// @returns m_s the scalar part of the quaternion
    
    Real getS() const  noexcept{return m_s;}
    
    /// @brief accesor for the x vector components
    /// @returns m_x the scalar part of the quaternion
    
    Real getX() const  noexcept{return m_x;}
    
    /// @brief accesor for the y vector components
    /// @returns m_y the scalar part of the quaternion
    
    Real getY() const  noexcept{return m_y;}
    
    /// @brief accesor for the z vector components
    /// @returns m_z the scalar part of the quaternion
    
    Real getZ() const  noexcept{return m_z;}
    
    /// @brief accesor for the  vector components as an Vec4
    /// @returns a vector
    
    Vec4 getVector() const  noexcept{return Vec4(m_x,m_y,m_z,0);}
    
    /// @brief mutator for the  vector components as an Vec4
    /// @param[in] _v the vector to set the quat vector components from
    
    void setVector( const Vec4 &_v) noexcept
    {
      m_x=_v.m_x;
      m_y=_v.m_y;
      m_z=_v.m_z;
    }
    
    /// @brief mutator for the scalar part
    /// @param[in] _s the scalar part of the quaternion to set
    
    void setS(Real &_s) noexcept {m_s=_s;}
    
    /// @brief mutator for the x vector part
    /// @param[in] _x the x vector part of the quaternion to set
    
    void setX(Real &_x) noexcept {m_x=_x;}
    
    /// @brief mutator for the y vector part
    /// @param[in] _x the x vector part of the quaternion to set
    
    void setY(Real &_y) noexcept {m_y=_y;}
    
    /// @brief mutator for the z vector part
    /// @param[in] _z the z vector part of the quaternion to set
    
    void setZ(Real &_z) noexcept  {m_z=_z;}
    
    /// @brief  Perform a multiplication between 2 quaternions
    /// @param[in] _q the rhs quaternion argument
    /// @return  the result of the mutliplication (product)
    
    Quaternion operator *(const Quaternion& _q) const noexcept;
    
    /// @brief  Perform a multiplication this and another quaternions
    /// sets the current quat q1 = q1*q2
    /// @param[in] _q the rhs quaternion argument
    
    Quaternion &operator *=(const Quaternion& _q ) noexcept;
    
    /// @brief  Perform a multiplication between a quaternion and a scalar
    /// @param[in] _s the rhs scalar argument
    /// @return  the result of the mutliplication q*s
    
    Quaternion operator *(Real _s ) const noexcept;
    
    /// @brief  Perform a multiplication this and  a real scalar
    /// sets the current quat to q=q*_s
    /// @param[in] _s the rhs quaternion argument
    
    void operator *=( Real _s ) noexcept;
    
    /// @brief add two quaternions
    /// @param[in] _q the rhs quaternion argument
    /// @return  the result of the addition
    
    Quaternion operator +(const Quaternion& _q ) const noexcept;
    
    /// @brief  subtract two quaternions
    /// @param[in] _q the rhs quaternion argument
    /// @return  the result of the subtraction
    
    Quaternion operator -( const Quaternion& _q) const noexcept;
    
    /// @brief  add _q to the current quaternion
    /// @param[in] _q the rhs quaternion argument
    
    Quaternion &operator +=(const Quaternion& _q )  noexcept;
    
    /// @brief  subtract _q from the current quaternion
    /// @param[in] _q the rhs quaternion argument
    
    Quaternion & operator -=( const Quaternion& _q )  noexcept;

    
    /// @brief  normalise this  quaternion this sets each of the component parts
    /// by calculating the magnitude and dividing each component by this
    
    void normalise() noexcept;
    
    /// @brief  returns the magnitude of the quaternion
    /// @return  The magnitude of the quaternion
    
    Real magnitude() const  noexcept;
    
    /// @brief  conjugate negate the vector part can also be done by the -() operator
    /// @returns the conjugate of the current quaternion
    
    Quaternion  conjugate() const  noexcept {return Quaternion(m_s,-m_x,-m_y,-m_z);}
    
    /// @brief  conjugate negate the vector part can also be done by the -() operator
    /// @returns the conjugate of the current quaternion
    
    Quaternion inverse()const  noexcept;
  
    /// @brief  dot product of the quaternion
    /// @returns product
    
    float dot(const Quaternion &_lhs)const  noexcept;

    static float dot(const Quaternion &_lhs, const Quaternion &_rhs)  noexcept;

    
    /// @brief  conjugate negate the vector part but for the current vector -
    /// @returns the conjugate of the current quaternion
    
    void operator -() noexcept{m_x=-m_x; m_y=-m_y; m_z=-m_z;}
    
    /// @brief  returns the inverse of the quaternion (aka conjugate)
    /// the scalar part remains the same and we reverse the vector part
    /// @return  the conjugate of the quaternion
    
    Quaternion operator-() const noexcept {return Quaternion(m_s,-m_x,-m_y,-m_z ); }
    
    /// @brief test for equality
    /// @param [in] _q the quaternion to test against
    /// @returns true if the same (based on EPSILON test range) or false
    
    bool operator == (const Quaternion& _q) const noexcept;
    
    /// @brief  this function spherically interpolates between two quaternions with respect to t
    /// @param [in]  _q1  -  the first quaternion
    /// @param [in]  _q2  -  the second quaternion
    /// @param [in]  _t  -  the interpolating t value
    
    static Quaternion slerp( Quaternion _q1, Quaternion _q2, Real _t) noexcept;

    static Quaternion qlerp( Quaternion _q1, Quaternion _q2, Real _t) noexcept;

    void negate();

    
    /// @brief  operator to allow a quat to be multiplied by a vector
    /// V2=Q*V1 this is formed by sandwiching the vector between the current quat and the
    /// inverse of the current quat (conjugate) so we get q*_vec*q.conjugate() this is the main way to do
    /// quaternion rotation on points (or can use the rotatePoint method which does the same thing)
    /// we must ensure that the quat has been set to the correct values for rotation (i.e. set the axis and the rotation values
    /// this can be done using the rotateX/Y/Z or fromAxisAngle or fromEulerAngle methods
    /// @param[in]  _vec the vector to be multiplied
    /// @returns a vector formed from q*_vec*q^-1 (conjugate)
    
    Vec4 operator* (const Vec4 &_vec) const noexcept;
    
    /// @brief  set the current quaternion as a rotation around the X cartesian axis [1,0,0]
    /// @param[in] _angle the angle of rotation around the x axis in degrees
    
    static Quaternion rotateX(Real _angle) noexcept;
    
    /// @brief  set the current quaternion as a rotation around the Y cartesian axis [0,1,0]
    /// @param[in] _angle the angle of rotation around the y axis in degrees
    
    static Quaternion  rotateY(Real _angle) noexcept;
    
    /// @brief  set the current quaternion as a rotation around the Z cartesian axis [0,0,1]
    /// @param[in] _angle the angle of rotation around the Z axis in degrees
    
    static Quaternion rotateZ(Real _angle) noexcept;
    
    /// @brief  set the current quaternion as a rotation around the vector _axis
    /// @brief[in] _axis the axis to rotate around (will be normalized)
    /// @param[in] _angle the angle of rotation around the Z axis in degrees
    
    void fromAxisAngle(const Vec3 &_axis,Real _angle) noexcept;
    
    /// @brief  set the current quaternion as a rotation based on 3 Euler angles
    /// this will create the quat as a product of 3 seprate quats
    /// @brief[in] _x the rotation in degrees around the x axis
    /// @brief[in] _y the rotation in degrees around the y axis
    /// @brief[in] _z the rotation in degrees around the z axis
    
    void fromEulerAngles(const Real _x,const Real _y,const Real _z) noexcept;
    
    /// @brief  rotate our point by a quat (but can also be done using the * operator)
    /// @brief[in] _r the rotation Quat
    /// @brief[inout] io_p the point to be rotated (result we be set in this point)
    
    static void rotatePoint(const Quaternion& _r,Vec3 & io_p)     noexcept;
    
    /// @brief  return the axis and angle of the current quat (angle in degrees)
    /// @brief[out] o_axis the axis of rotation (
    /// @brief[out] o_angle the angle of rotation about the quat angle in degrees
    
    void toAxisAngle(Vec3 &o_axis,Real &o_angle) const noexcept;
    
    /// @brief  return the current quat as a 4x4 transform matrix
    /// @returns the quat as a matrix
    
    Mat4 toMat4() const noexcept;
    

    /// @brief  the quaternion data for the scalar real part
    Real m_s=1.0f;
    /// @brief  the quaternion data for x
    Real m_x=0.0f;
    /// @brief  the quaternion data for y
    Real m_y=0.0f;
    /// @brief  the quaternion data for z
    Real m_z=0.0f;

}; // end of class


}

inline ngl::Quaternion operator*( ngl::Real _s, const ngl::Quaternion &_lhs) noexcept
{
  return ngl::Quaternion(_lhs.m_s*_s, _lhs.m_x*_s, _lhs.m_y*_s, _lhs.m_z*_s);
}

#include "Mat4.h"

#endif
