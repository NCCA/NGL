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
#ifndef MATERIAL_H__
#define MATERIAL_H__
// must include types.h first for Real and GLEW if required
#include "Colour.h"
#include "Types.h"
#include "rapidxml/rapidxml.hpp"

/// @file Material.h
/// @brief a simple Ambient Diffuse, Specular type GL material this will fill in the
/// following glsl shader structure when a shader is passed
/// @verbatim
/// struct Material
/// {
///  vec4 ambient;
///  vec4 diffuse;
///  vec4 specular;
///  float shininess;
/// };


namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class Material "include/Material.h"
/// @brief a simple OpenGL material class and set the parameters
/// @author Jonathan Macey
/// @version 5.0
/// @date 18/08/11 removed deprecated GL stuff and added new structures for glsl
/// Last Revision 29/10/09 Updated to meet NCCA coding standard
/// @todo add better file read and write support and make it support mtl file format used with obj files
/// @todo add GL_FRONT, GL_BACK and GL_FRONT_AND_BACK support as part of the  ctor
/// @example Materials/Material.cpp
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// @enum used to give offset into materials array for some standard matertial values
/// the actual values are taken from the Hill Book
//----------------------------------------------------------------------------------------------------------------------

enum STDMAT { BLACKPLASTIC,BRASS,BRONZE,CHROME,COPPER,GOLD,PEWTER,SILVER,POLISHEDSILVER};

//----------------------------------------------------------------------------------------------------------------------
/// @brief material values for some standard material values taken from the Hill Book
//----------------------------------------------------------------------------------------------------------------------
const static Real s_materials [9][10]=
  {
    { 0.0f,0.0f,0.0f,0.01f,0.01f,0.01f,0.50f,0.50f,0.50f,32.0f}, //Black plastic
    { 0.329412f,0.223529f,0.027451f,0.780392f,0.568627f,0.113725f,0.992157f,
      0.941176f,0.807843f,27.8974f}, //Brass
    { 0.2125f,0.1275f,0.054f,0.714f,0.4284f,0.18144f,0.393548f,0.271906f,
      0.166721f,25.6f}, // Bronze
    { 0.25f,0.25f,0.25f,0.4f,0.4f,0.4f,0.774597f,0.774597f,0.774597f,76.8f}, //Chrome
    { 0.19125f,0.0735f,0.0225f,0.7038f,0.27048f,0.0828f,0.256777f,0.137622f,
      0.086014f,12.8f}, // Copper
    { 0.274725f,0.1995f,0.0745f,0.75164f,0.60648f,0.22648f,0.628281f,
      0.555802f,0.3666065f,51.2f}, // Gold
    { 0.10588f,0.058824f,0.113725f,0.427451f,0.470588f,0.541176f,
      0.3333f,0.3333f,0.521569f,9.84615f}, // Pewter
    { 0.19225f,0.19225f,0.19225f,0.50754f,0.50754f,0.50754f,0.508273f,
      0.508273f,0.508273f,51.2f}, // Silver
    { 0.23125f,0.23125f,0.23125f,0.2775f,0.2775f,0.2775f,0.77391f,
      0.77391f,0.77391f,89.6f} // PolishedSilver
  };
//----------------------------------------------------------------------------------------------------------------------


class NGL_DLLEXPORT Material
{
public :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the default material properties
  //----------------------------------------------------------------------------------------------------------------------
  void setDefault();
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief set the material properties based on another matherial
  ///  @param[in]  _m the material to use
  //----------------------------------------------------------------------------------------------------------------------
  void set( const Material &_m );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief change the material to one of the standard materials
  /// @param[in] _mat the material to use
  //----------------------------------------------------------------------------------------------------------------------
  void change( const STDMAT _mat );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for material
  /// @param[in]  _amb the ambient colour
  /// @param[in]  _dif the diffuse colour
  /// @param[in]  _spec the specular colour
  /// @param[in]  _emis the emimissive colour
  //----------------------------------------------------------------------------------------------------------------------
  Material( Colour _amb=0.0f,  Colour _dif=0.5f, Colour _spec=1.0f ) :
            m_ambient(_amb),
            m_diffuse(_dif),
            m_specular(_spec)
            {;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor using a STDMAT for the coulour
  /// @param[in]  _mat the standard material to set
  //----------------------------------------------------------------------------------------------------------------------
  Material( STDMAT _mat );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor using an index into the default colour array from sdtmat for the coulour
  /// @param[in] _mat the  index
  //----------------------------------------------------------------------------------------------------------------------
  Material( int _mat );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor to load material from a file, need implimenting properly
  /// @param[in] _fName the name of the file to load the material from
  //----------------------------------------------------------------------------------------------------------------------
  Material( const std::string &_fName );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load a material from a file needs work
  /// @param[in] _fName  the name of the file to load
  //----------------------------------------------------------------------------------------------------------------------
  void load(  const std::string &_fName  );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief mutator to set the Ambient colour value
  /// @param[in] _c  colour values to be set
  //----------------------------------------------------------------------------------------------------------------------
  inline void setAmbient(const Colour &_c){ m_ambient = _c;}
  inline Colour getAmbient() const {return m_ambient;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief mutator to set the Diffuse colour value
  /// @param[in] _c  colour values to be set
  //----------------------------------------------------------------------------------------------------------------------
  inline void setDiffuse(const Colour &_c){ m_diffuse = _c;}
  inline Colour getDiffuse() const {return m_diffuse;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief mutator to set the Specular colour value
  /// @param[in] _c  colour values to be set
  //----------------------------------------------------------------------------------------------------------------------
  inline void setSpecular(const Colour &_c){ m_specular = _c;}
  inline Colour getSpecular() const {return m_specular;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief mutator to set the specular exponent colour value
  /// @param[in] _s  specular exponent value smaller = larger highlights
  //----------------------------------------------------------------------------------------------------------------------
  inline void setSpecularExponent(Real _s){ m_specularExponent=_s;}
  inline Real getSpecularExponent()const { return m_specularExponent;}

  inline Real getTransparency()const { return m_transparency;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief mutator to set the surface roughness, will effect the spread in shading
  /// @param[in] _r  value to set
  //----------------------------------------------------------------------------------------------------------------------
  inline void setRoughness(Real _r){m_surfaceRoughness=_r;}
  inline Real getRoughness()const {return m_surfaceRoughness;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load the material values to the currently active shader passed this will set the following glsl shader parameters
  /// struct Material
  /// {
  ///  vec4 ambient;
  ///  vec4 diffuse;
  ///  vec4 specular;
  ///  float shininess;
  /// };
  /// @param[in] _uniformName
  //----------------------------------------------------------------------------------------------------------------------
  void loadToShader( std::string _uniformName )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief write class to xml stream
  /// @brief _doc the xml doc to write to
  /// @param _name an overidable token name for the xml tag
  //----------------------------------------------------------------------------------------------------------------------
  void writeXML(rapidxml::xml_document<> &_doc ,std::string _tag="Vec3") const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read xml from stream
  /// @brief _doc the xml document to read
  //----------------------------------------------------------------------------------------------------------------------
  void readXML( rapidxml::xml_document<> &_doc );



protected :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ambient component of the material
  //----------------------------------------------------------------------------------------------------------------------
  Colour m_ambient;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief diffuse component of the material
  //----------------------------------------------------------------------------------------------------------------------
  Colour m_diffuse;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief specular component of the material
  //----------------------------------------------------------------------------------------------------------------------
  Colour m_specular;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief specular exponent used for OpenGL material
  //----------------------------------------------------------------------------------------------------------------------
  Real m_specularExponent;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief used for setting alpha values
  //----------------------------------------------------------------------------------------------------------------------
  Real m_transparency;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief roughness used for specular spread
  //----------------------------------------------------------------------------------------------------------------------
  Real m_surfaceRoughness;

}; // end of Material


}

#endif // MATERIAL
//----------------------------------------------------------------------------------------------------------------------

