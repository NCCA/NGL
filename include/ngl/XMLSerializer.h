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
#ifndef XML_SERIALIZER_H__
#define XML_SERIALIZER_H__
/// @file XMLSerializer.h
/// @brief XML Serialization for NGL
#include "AbstractSerializer.h"
#include "rapidxml/rapidxml.hpp"
#include <stack>

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class AbstractSerializer "include/XMLSerializer.h"
/// @author Jonathan Macey
/// @version 1.0
/// @date 11/11/13
/// @brief XML serialization in NGL
//----------------------------------------------------------------------------------------------------------------------
class NGL_DLLEXPORT XMLSerializer
{

public :
  enum ACCESSMODE{READ,WRITE};
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor, uses RAII to open the file, flag indicates if we have read or write mode
  /// @param[in]  &_fname the name of file to serialize
  //----------------------------------------------------------------------------------------------------------------------
  XMLSerializer(const std::string &_fname,ACCESSMODE _mode);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor will close the file
  //----------------------------------------------------------------------------------------------------------------------
  ~XMLSerializer();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an AABB must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(AABB &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an AABB must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const AABB &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an BBox must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(BBox &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an BBox must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const BBox &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an BezierCurve must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(BezierCurve &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an BezierCurve must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const BezierCurve &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Camera must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Camera &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Camera must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Camera &_s, const std::string &_tag);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Colour must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Colour &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Colour must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Colour &_s,std::string _tag="Colour");
  virtual void write(const Colour &_s,rapidxml::xml_node<> *_parent,std::string _tag="Colour");

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Light must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Light &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Light must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Light &_s, const std::string &_tag) ;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Mat3 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Mat3 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Mat3 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(Mat3 &_s, std::string _tag="Mat3");
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Mat4 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Mat4 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Mat4 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write( Mat4 &_s, std::string _tag="Mat4");
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Material must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Material &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Material must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Material &_s, const std::string &_tag);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an PathCamera must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(PathCamera &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an PathCamera must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const PathCamera &_s, const std::string &_tag);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Plane must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Plane &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Plane must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Plane &_s, const std::string &_tag);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Quaternion must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Quaternion &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Quaternion must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Quaternion &_s,const std::string &_tag="Quat");
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an SpotLight must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(SpotLight &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an SpotLight must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const SpotLight &_s, const std::string &_tag);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Transformation must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Transformation &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Transformation must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Transformation &_s,const std::string &_tag);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Vec2 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Vec2 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Vec2 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Vec2 &_s,std::string _tag="Vec2");
  void write(const Vec2 &_s,rapidxml::xml_node<> *_parent,std::string _tag) ;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Vec3 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Vec3 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Vec3 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Vec3 &_s, std::string _tag="Vec3");
  void write(const Vec3 &_s,rapidxml::xml_node<> *_parent,std::string _tag) ;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from an Vec4 must be overriden in child
  /// @param [inout] _s the element to read
  //----------------------------------------------------------------------------------------------------------------------
  virtual void read(Vec4 &_s);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write from an Vec4 must be overriden in child
  /// @param [in] _s the element to write
  //----------------------------------------------------------------------------------------------------------------------
  virtual void write(const Vec4 &_s,std::string _tag="Vec4") ;
  void write(const Vec4 &_s,rapidxml::xml_node<> *_parent,std::string _tag) ;
  void writeToXML(const std::string &_s, const std::string &_tag);
  void writeToXML(const std::string &_s, rapidxml::xml_node<> *_parent,const std::string &_tag);
  void addNode(const std::string &_tag);
  void addNode(const std::string &_tag,rapidxml::xml_node<> *_parent);


  rapidxml::xml_node<>* getCurrentNode() const {return m_currentNode;}
private :
  /// @brief make sure we can't copy this class;
  XMLSerializer(const AbstractSerializer &){;}
  /// @brief make sure we can't copy this class;
  XMLSerializer &operator=(const XMLSerializer &);

private :
  rapidxml::xml_document<> m_doc;

  rapidxml::xml_node<> *m_currentNode;
  rapidxml::xml_node<>* m_parent;

  std::string m_fname;
  ACCESSMODE m_mode;

};



} // end of namespace ngl


#endif // end of the class
