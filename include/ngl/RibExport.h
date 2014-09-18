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
#ifndef RIBEXPORT_H__
#define RIBEXPORT_H__
/// @file RibExport.h
/// @brief a simple rib exporter function
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include <fstream>
#include <string>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @file RibExport.h
/// @class RibExport "include/RibExport.h"
/// @brief simple rib export class, attempts to auto tab the rib file etc. needs lots of work to make it  complete!!
/// @brief allows for OpenGL programs to export to Rib files, very much work in progress, note I don't use the coding standard
/// in the method names so it better matches the Rib file format / python rules
/// @author Jonathan Macey
/// @version 1.2
/// @date 24/11/04
/// @todo  add code for exporting basic Rib geometry patches etc.
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT RibExport
{
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to auto write tabs
  //----------------------------------------------------------------------------------------------------------------------
  void writeTabs();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor passing in the name of the rib file to open
  /// @param[in] _fileName the rib file to open
  //----------------------------------------------------------------------------------------------------------------------
  RibExport(  const std::string &_fileName );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief destructor
  //----------------------------------------------------------------------------------------------------------------------
  ~RibExport();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  write a comment to the rib stream
  /// @param[in] _sText the text to write
  //----------------------------------------------------------------------------------------------------------------------
  void comment( const std::string &_sText );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief open a rib file for writing
  //----------------------------------------------------------------------------------------------------------------------
  void open();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Close the rib file
  //----------------------------------------------------------------------------------------------------------------------
  void close();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write world begin and auto tab
  //----------------------------------------------------------------------------------------------------------------------
  void WorldBegin();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write world begin and un tab
  //----------------------------------------------------------------------------------------------------------------------
  void WorldEnd();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write attribute begin and tab in
  //----------------------------------------------------------------------------------------------------------------------
  void AttributeBegin();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write attribute end and un tab
  //----------------------------------------------------------------------------------------------------------------------
  void AttributeEnd();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write transform begin and tab in
  //----------------------------------------------------------------------------------------------------------------------
  void TransformBegin();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write transform end and un tab
  //----------------------------------------------------------------------------------------------------------------------
  void TransformEnd();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Write text to rib file
  /// @param[in] _string the string to write
  //----------------------------------------------------------------------------------------------------------------------
  void writeToFile(std::string _string);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiTranslate to file
  /// @param[in] _x the x translate value
  /// @param[in] _y the y translate value
  /// @param[in] _z the z translate value
  //----------------------------------------------------------------------------------------------------------------------
  void Translate(const Real _x, const Real _y, const Real _z );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiRotate
  /// @param[in] _angle the angle to rotate around the axis specified
  /// @param[in] _x the x axis value
  /// @param[in] _y the y axis value
  /// @param[in] _z the z axis value
  //----------------------------------------------------------------------------------------------------------------------
  void Rotate( const Real _angle, const Real _x, const Real _y, const Real _z );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiScale
  /// @param[in] _x the x scale value
  /// @param[in] _y the y scale value
  /// @param[in] _z the z scale value
  //----------------------------------------------------------------------------------------------------------------------
  void Scale( const Real _x, const Real _y, const Real _z );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiSphere
  /// @param[in] _radius the radius of the sphere
  /// @param[in] _zMin the min z sweep
  /// @param[in] _zMax the max z sweep
  /// @param[in] _sweep how much of the sphere to draw
  //----------------------------------------------------------------------------------------------------------------------
  void Sphere( const Real _radius, const Real _zMin, const Real _zMax, const Real _sweep    );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiCylinder
  /// @param[in] _radius the radius of the Cylinder
  /// @param[in] _zMin the min z sweep
  /// @param[in] _zMax the max z sweep
  /// @param[in] _sweep how much of the sphere to draw
  //----------------------------------------------------------------------------------------------------------------------
  void Cylinder(const Real _radius, const Real _zMin,  const Real _zMax, const Real _sweep);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiCone to the stream
  /// @param[in] _height the height of the cone
  /// @param[in] _radius the radius of the cone
  /// @param[in] _sweep the sweep of the cone
  //----------------------------------------------------------------------------------------------------------------------
  void Cone( const Real _height, const Real _radius, const Real _sweep );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write an RiParaboloid to the stream
  /// @param[in] _topRad the top radius of the paraboloid
  /// @param[in] _zMin the min z sweep
  /// @param[in] _zMax the max z sweep
  /// @param[in] _sweep the sweep of the paraboloid
  //----------------------------------------------------------------------------------------------------------------------
  void Paraboloid( const Real _topRad, const Real _zMin, const Real _zMax,  const Real _sweep  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw a hyperboloid to the stream
  /// @param[in] _p1 the first point of the hyperboloid sweep
  /// @param[in] _p2 the 2nd point of the hyperboloid sweep
  /// @param[in] _sweep the sweep of the hyperboloid
  //----------------------------------------------------------------------------------------------------------------------
  void Hyperboloid( const Real _p1, const Real _p2, const Real _sweep );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw an RiDisk to the stream
  /// @param[in] _height the height of the disk
  /// @param[in] _radius the radius of the disk
  /// @param[in] _sweep the sweep of the disk
  //----------------------------------------------------------------------------------------------------------------------
  void Disk( const Real _height, const Real _radius, const Real _sweep );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw an  RiTorus to the stream
  /// @param[in] _major the major radius of the torus
  /// @param[in] _minor the minor radius of the torus
  /// @param[in] _phiMin the min value of the radial sweep
  /// @param[in] _phiMax the max value of the radial sweep
  /// @param[in] _sweep the sweep of the torus
  //----------------------------------------------------------------------------------------------------------------------
  void Torus( const Real _major,const Real _minor,const Real _phiMin,  const Real _phiMax,const Real _sweep);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to see if stream is open
  //----------------------------------------------------------------------------------------------------------------------
  inline bool isOpen(){return m_isOpen;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a method to get the rib stream
  //----------------------------------------------------------------------------------------------------------------------
  inline std::fstream & getStream(){return m_ribFile;}

protected :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the RibFile stream opened in the ctor
  //----------------------------------------------------------------------------------------------------------------------
  std::fstream m_ribFile;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  count calls to AttributeBegin to ensure matching
  //----------------------------------------------------------------------------------------------------------------------
  int m_attribCount;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  count calls to TransformBegin to ensure matching
  //----------------------------------------------------------------------------------------------------------------------
  int m_transformCount;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  count calls to WorldBegin to ensure matching
  //----------------------------------------------------------------------------------------------------------------------
  int m_worldCount;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  Hold the frame number for calls to Frame
  //----------------------------------------------------------------------------------------------------------------------
  int m_frameNumber;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  The name of the RibFile
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_ribFileName;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  the current tab level for auto tabing of rib file
  //----------------------------------------------------------------------------------------------------------------------
  int m_tabs;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  if the stream is open
  //----------------------------------------------------------------------------------------------------------------------
  bool m_isOpen;
};
} // end ngl namespace

#endif

//----------------------------------------------------------------------------------------------------------------------

