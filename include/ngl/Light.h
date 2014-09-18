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
#ifndef LIGHT_H__
#define LIGHT_H__
/// @file Light.h
/// @brief an encapsulation of an OpenGL Light
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include "Colour.h"
#include "Vec4.h"
#include "Vec3.h"
#include "Mat4.h"
#include <string>


namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
///  @enum LIGHTMODES used to flag if a light is local or remote to the scene
///
///  DIRECTIONAL used to set the light as directional light
///  POINT used to set the light as a point light
///
//----------------------------------------------------------------------------------------------------------------------
// for c++ 11 use enum class LIGHTMODES : int
enum LIGHTMODES
  {
   DIRECTIONALLIGHT, /// @brief directional light from old OPenGL
  POINTLIGHT,  /// @brief point light
  SPOTLIGHT=1
  };


//----------------------------------------------------------------------------------------------------------------------
/// @class Light "include/Light.h"
/// @brief Simple class to encapsulate OpenGL Light functions
/// this will fill in the following structure
///
/// struct Lights
/// {
///   vec4 position;
///   vec4 ambient;
///   vec4 diffuse;
///   vec4 specular;
/// };
///  @author Jon Macey
///  @version 5.0
///  @date 18/08/11 updated to remove deprecated GL stuff and all work with glsl 150
/// Last Revision 29/10/09 Updated to NCCA coding standard
/// @todo this will need to be changed to work with GLSL lights for GL_VERSION > 3.x
//----------------------------------------------------------------------------------------------------------------------


class NGL_DLLEXPORT Light
{
public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  set the light position
  /// @param[in]  _p the new light position
  //----------------------------------------------------------------------------------------------------------------------
  inline void setPosition( const Vec3& _p )
              {
                m_position.set(_p.m_x,_p.m_y,_p.m_z,static_cast<Real>(m_lightMode));
              }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the light colour
  /// @param[in] _c the colour to set
  //----------------------------------------------------------------------------------------------------------------------
  inline void setColour(const Colour& _c)
              {
                m_diffuse.set(_c);
              }

  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief set the specular colour
  /// @param[in] _c the colour to set for the specular
  //----------------------------------------------------------------------------------------------------------------------
  inline void setSpecColour(const Colour& _c )
              {
                m_specular.set(_c);
              }

  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief default constructor
  ///  this set nothing so the light will not illuminate
  //----------------------------------------------------------------------------------------------------------------------
  inline Light(){;}
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief copy ctor
  ///  this set nothing so the light will not illuminate
  //----------------------------------------------------------------------------------------------------------------------
  Light(const Light &_l);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor to create the light
  /// @param[in] _pos the light position
  /// @param[in] _col the light colour
  /// @param[in] _lightmode the mode to set the light to either local or remote
  //----------------------------------------------------------------------------------------------------------------------
  Light( const Vec3& _pos, const Colour& _col, LIGHTMODES _lightmode );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor to create the light
  /// @param[in] _pos the light position
  /// @param[in] _col the light colour
  /// @param[in] _specColour the specular component of the light
  /// @param[in] _lightmode the mode to set the light to either local or remote
  //----------------------------------------------------------------------------------------------------------------------
  Light(const Vec3& _pos, const Colour& _col,const Colour& _specColour,LIGHTMODES _lightmode);
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief destructor when light is destroyed we turn it off
  ///
  //----------------------------------------------------------------------------------------------------------------------
  virtual inline ~Light(){;}
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief Disable the light by calling glDisable(GL_LIGHT0+LightNo);
  //----------------------------------------------------------------------------------------------------------------------
  void disable();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  Enables the light and automatically allocates an OpenGL light ID.
  /// @return  true if there is a free openGL light ID available.
  //----------------------------------------------------------------------------------------------------------------------
  virtual void enable();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief displays the light in the scene
  //----------------------------------------------------------------------------------------------------------------------
  void show();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the current light position as a Vector
  /// @returns Vector pos
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 getPos()const {return m_position; }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the current light colour
  /// @returns Colour colour
  //----------------------------------------------------------------------------------------------------------------------
  Colour getColour()const { return m_diffuse; }

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the current light Specular colour
  /// @returns Colour Spec colour
  //----------------------------------------------------------------------------------------------------------------------
  Colour getSpecColour() const{ return m_specular; }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the light attenuation
  /// @param[in] _constant the constant attenuation
  /// @param[in] _linear attenuation
  /// @param[in] _quadratic attenuation
  //----------------------------------------------------------------------------------------------------------------------
  void setAttenuation(Real _constant=1.0, Real _linear=0.0, Real _quadratic=0.0 );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load the current light values to the shader that is active at present
  /// @param[in] _uniformName name of the uniform to set
  //----------------------------------------------------------------------------------------------------------------------
  void loadToShader(std::string _uniformName )const;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set a transform so that the light position is multiplied by this value (default is identity matrix)
  /// @param[in] _t the transform matrix
  //----------------------------------------------------------------------------------------------------------------------
  void setTransform( Mat4 &_t );
protected :
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief m_pos is used to store the light position w used for point / dir light values
   //----------------------------------------------------------------------------------------------------------------------
   Vec4 m_position;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief   Colour used to give the light a colour
   //----------------------------------------------------------------------------------------------------------------------
   Colour m_diffuse;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief   specular highlight colour used for the lights
   //----------------------------------------------------------------------------------------------------------------------
   Colour m_specular;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief   ambient light colour used for the lights
   //----------------------------------------------------------------------------------------------------------------------
   Colour m_ambient;
   //----------------------------------------------------------------------------------------------------------------------
   ///  @brief  used to hold the current lights mode
   //----------------------------------------------------------------------------------------------------------------------
   LIGHTMODES m_lightMode;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief attenuation value for constant falloff
   //----------------------------------------------------------------------------------------------------------------------
   Real m_constantAtten;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief attenuation value for linear falloff
   //----------------------------------------------------------------------------------------------------------------------
   Real m_linearAtten;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief attenuation value for Quadratic falloff
   //----------------------------------------------------------------------------------------------------------------------
   Real m_quadraticAtten;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief active if true else off
   //----------------------------------------------------------------------------------------------------------------------
   bool m_active;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief the spot cutoff angle for directional and point lights this is set to 180 by default, and other
   /// values are cos(radians(angle))
   //----------------------------------------------------------------------------------------------------------------------
   Real m_cutoffAngle;
   //----------------------------------------------------------------------------------------------------------------------
   /// @brief the transform applied to the light before loading to the shader
   /// this is usually the inverse projection matrix for normal OpenGL style eye-cord calculations but
   /// is left for the Application to calculate and pass for easier implementation of different light models
   //----------------------------------------------------------------------------------------------------------------------
   Mat4 m_transform;


private:


}; // end class

}// end namespace

#endif // __LIGHT__

//----------------------------------------------------------------------------------------------------------------------




