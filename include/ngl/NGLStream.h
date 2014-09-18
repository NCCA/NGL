/*
  Copyright (C) 2013 Jon Macey

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
/// @file NGLStream.h
/// @brief stream helpers for ngl data types

#include <iostream>
#include "Types.h"
namespace ngl
{
  class Light;
  class Plane;
  class Mat3;
  class Mat4;
  class Vec2;
  class Vec3;
  class Vec4;
  class Colour;
  class TransformStack;
  class Quaternion;
  class AABB;
  class BBox;
  class Camera;
  class BezierCurve;
  class Material;
  class PathCamera;
  class SpotLight;
  class Transformation;
//----------------------------------------------------------------------------------------------------------------------
/// @brief insertion operator to print out the Vec2
/// @param[in] _output the stream to write to
/// @param[in] _s the Vec2 to write
//----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream &operator<<(std::ostream& _output, const Vec2& _s);
//----------------------------------------------------------------------------------------------------------------------
/// @brief extraction operator to read in  the Vec2
/// @param[in] _input the stream read from
/// @param[in] _s the Vec2 to write
//----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::istream& operator>>(std::istream& _input, Vec2 &_s);
//----------------------------------------------------------------------------------------------------------------------
/// @brief insertion operator to print out the Vec3
/// @param[in] _output the stream to write to
/// @param[in] _s the Vec3 to write
//----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator<<(std::ostream& _output, const Vec3& _s);
 //----------------------------------------------------------------------------------------------------------------------
/// @brief extraction operator to read in  the Vec3
/// @param[in] _input the stream read from
/// @param[in] _s the Vec3 to write
//----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::istream& operator>>(std::istream& _input, Vec3 &_s);
//----------------------------------------------------------------------------------------------------------------------
/// @brief insertion operator to print out the vector
/// @param[in] _output the stream to write to
/// @param[in] _s the vector to write
//----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator<<(std::ostream& _output, const Vec4& _s);
//----------------------------------------------------------------------------------------------------------------------
/// @brief extraction operator to read in  the vector
/// @param[in] _input the stream read from
/// @param[in] _s the vector to write
//----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::istream& operator>>(std::istream& _input, Vec4 &_s);
 //----------------------------------------------------------------------------------------------------------------------
 /// @brief << extraction operator to prints out the colour in the format [r,g,b,a]
 /// @param[in] _output the outstream class pointer
 /// @param[in] _c the camera to print out
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator<<(std::ostream& _output, const Camera& _c);
 //----------------------------------------------------------------------------------------------------------------------
 /// @brief << extraction operator to prints out the colour in the format [r,g,b,a]
 /// @param[in] _output the outstream class pointer
 /// @param[in] _s the colour to print out
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT  std::ostream&  operator<<( std::ostream& _output, const Colour& _s );
 //----------------------------------------------------------------------------------------------------------------------
 /// @brief >> insertion operator to read in the colour data r -> g -> b -> a
 /// @param[in] _input the instream class pointer
 /// @param[in] _s the colour to read in to
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT  std::istream& operator>>( std::istream& _input, Colour& _s );

 //----------------------------------------------------------------------------------------------------------------------
 /// @brief  insertion operator to write matrix to stream
 /// @param[in] output the stream to write to
 /// @param[in] M the matrix to write
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator<<(std::ostream& output, const Mat3& M);
 //----------------------------------------------------------------------------------------------------------------------
 /// @brief  insertion operator to write matrix to stream
 /// @param[in] output the stream to write to
 /// @param[in] M the matrix to write
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator<<(std::ostream& output, const Mat4& M);
 //----------------------------------------------------------------------------------------------------------------------
 /// @brief  insertion operator to write matrix to stream
 /// @param[in] _output the stream to write to
 /// @param[in] _m the matrix-stack to write
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator<<(std::ostream& _output,  TransformStack& _m);
 //----------------------------------------------------------------------------------------------------------------------
 /// @brief  the streaming operator for the quaternion
 /// @param [in]  _ifs  -  the input stream
 /// @param [in]  _q  -  the place to read the values into
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::istream& operator >> ( std::istream& _ifs, Quaternion &_q );

 //----------------------------------------------------------------------------------------------------------------------
 /// @brief  the streaming operator for the quaternion
 /// @param [in]  i_ifs  -  the input stream
 /// @param [in]  i_q  -  the place to read the values into
 //----------------------------------------------------------------------------------------------------------------------
 NGL_DLLEXPORT std::ostream& operator << ( std::ostream& i_s, const Quaternion &i_q);



} // end of namespace ngl
