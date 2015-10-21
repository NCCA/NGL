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
#ifndef ABSTRACT_SERIALIZER_H__
#define ABSTRACT_SERIALIZER_H__
/// @file AbstractSerializer.h
/// @brief this class is the base class for all NGL serialisation code
#include "Types.h"
#include <vector>
#include <string>
#include <iostream>
#include "Colour.h"
#include "Mat3.h"
#include "Quaternion.h"

namespace ngl
{
class Light;
class Plane;
class Mat3;
class Mat4;
class Vec2;
class Vec3;
class Vec4;
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
/// @class AbstractSerializer "include/AbstractSerializer.h"
/// @author Jonathan Macey
/// @version 1.0
/// @date 11/11/13
/// @brief an abstract base clase for all serialization in NGL
//----------------------------------------------------------------------------------------------------------------------
class NGL_DLLEXPORT AbstractSerializer
{

public :
  enum ACCESSMODE{READ,WRITE};
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor, uses RAII to open the file, flag indicates if we have read or write mode
  /// @param[in]  &_fname the name of file to serialize
  //----------------------------------------------------------------------------------------------------------------------
  AbstractSerializer(const std::string &_fname,ACCESSMODE _mode) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor will close the file
  //----------------------------------------------------------------------------------------------------------------------
  ~AbstractSerializer() noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an AABB must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(AABB &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an AABB must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const AABB &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an BBox must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(BBox &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an BBox must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const BBox &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an BezierCurve must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(BezierCurve &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an BezierCurve must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const BezierCurve &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Camera must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Camera &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Camera must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Camera &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Colour must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Colour &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Colour must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Colour &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Light must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Light &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Light must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Light &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Mat3 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Mat3 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Mat3 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Mat3 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Mat4 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Mat4 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Mat4 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Mat4 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Material must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Material &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Material must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Material &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an PathCamera must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(PathCamera &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an PathCamera must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const PathCamera &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Plane must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Plane &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Plane must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Plane &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Quaternion must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Quaternion &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Quaternion must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Quaternion &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an SpotLight must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(SpotLight &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an SpotLight must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const SpotLight &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Transformation must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Transformation &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Transformation must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Transformation &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Vec2 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Vec2 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Vec2 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Vec2 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Vec3 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Vec3 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Vec3 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Vec3 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Vec4 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Vec4 &_s) noexcept=0;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Vec4 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Vec4 &_s) noexcept=0;

private :
  /// @brief make sure we can't copy this class;
  AbstractSerializer(const AbstractSerializer &){;}
  /// @brief make sure we can't copy this class;
  AbstractSerializer &operator=(const AbstractSerializer &);
};


} // end of namespace ngl


#endif // end of the class
