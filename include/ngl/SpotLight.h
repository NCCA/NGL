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


#ifndef SPOTLIGHT_H__
#define SPOTLIGHT_H__
// must include types.h first for Real and GLEW if required
//----------------------------------------------------------------------------------------------------------------------
/// @file SpotLight.h
/// @brief Encapsulation of OpenGL spotlight inherits from the Light class
//----------------------------------------------------------------------------------------------------------------------
#include "Light.h"


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
/// @class SpotLight "include/SpotLight.h"
/// @brief Encapsulation of OpenGL spotlight inherits from the Light class
/// @file SpotLight.h
/// @author Jonathan Macey
/// @version 2.0
/// @date 24/11/04
/// this will fill in the following structure
///
/// struct Lights
/// {
///   vec4 position;
///   vec3 direction;
///   vec4 ambient;
///   vec4 diffuse;
///   vec4 specular;
///   float spotCosCutoff;
///   float spotCosInnerCutoff;
///   float spotExponent;
///   float constantAttenuation;
///   float linearAttenuation;
///   float quadraticAttenuation;
/// };
//----------------------------------------------------------------------------------------------------------------------


class NGL_DLLEXPORT SpotLight : public Light
{
public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default ctor
  //----------------------------------------------------------------------------------------------------------------------
  SpotLight() noexcept{;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  ctor
  /// @param[in]  _pos    -  the spot position
  /// @param[in]  _dir    -  the spot direction
  /// @param[in]  _col    -  the spot colour
  //----------------------------------------------------------------------------------------------------------------------
  SpotLight( const Vec3 &_pos,const Vec3 &_dir,const Colour& _col ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  copy ctor
  //----------------------------------------------------------------------------------------------------------------------
  SpotLight(const SpotLight &_l) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a method to set the spotlight parameters
  /// @param [in] _pos the position of the Light
  /// @param [in] _dir the direction of the light
  /// @param [in] _col the colour of the light
  //----------------------------------------------------------------------------------------------------------------------
  void set( const Vec3& _pos, const Vec3& _dir, const Colour& _col ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  enables the spot light
  //----------------------------------------------------------------------------------------------------------------------
  void enable() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the various spot light params
  /// @param[in] _cutoff the spot cutoff value
  /// @param[in] _exponent the spot exponent vlaue
  /// @param[in] _constant constant attenuation value
  /// @param[in] _linear linear attenuation value
  /// @param[in] _quadratic quadratic attenuation value
  //----------------------------------------------------------------------------------------------------------------------
  void setParams(const Real _cutoff, const Real _exponent, const Real _constant, const Real _linear, const Real _quadratic ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the spot cutoff
  /// @param[in] _cutoff this is the spot cos cutoff value, we need to calc the cos(radians(_cutoff))
  //----------------------------------------------------------------------------------------------------------------------
  void setCutoff( const Real &_cutoff ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the spot inner cutoff
  /// @param[in] _cutoff this is the spot cos cutoff value, we need to calc the cos(radians(_cutoff))
  //----------------------------------------------------------------------------------------------------------------------
  void setInnerCutoff( const Real &_cutoff  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  sets the exponent
  /// @param[in] _exponent the spot exponent vlaue
  //----------------------------------------------------------------------------------------------------------------------
  inline void setExponent(const Real &_exp ) noexcept{ m_spotExponent=_exp;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  This function sets the light to aim at the specified point
  /// @param[in]  _pos  -  the aim position
  //----------------------------------------------------------------------------------------------------------------------
  void aim( const Vec4& _pos ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  this method loads the spotlight values to the shader
  /// @param[in]  _uniformName  the uniform base name to load shader values to the struct will be
  ///   _uniformName.position;
  ///   _uniformName.direction;
  ///   _uniformName.ambient;
  ///   _uniformName.diffuse;
  ///   _uniformName.specular;
  ///   _uniformName.spotCosCutoff;
  ///   _uniformName.spotExponent;
  ///   _uniformName.constantAttenuation;
  ///   _uniformName.linearAttenuation;
  ///   _uniformName.quadraticAttenuation;
  //----------------------------------------------------------------------------------------------------------------------

  void loadToShader(std::string _uniformName  )const noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the transform of the light this will be multiplied by the position
  /// Vec4 pos=m_transform*m_position;
  /// @param[in] _t the transform
  //----------------------------------------------------------------------------------------------------------------------
  void setTransform(Mat4 &_t) noexcept;


protected :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the spot inner cutoff angle
  //----------------------------------------------------------------------------------------------------------------------
  Real m_innerCutoffAngle;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the SpotExponent value
  //----------------------------------------------------------------------------------------------------------------------
  Real m_spotExponent;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief where the spot is to be aimed
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_aim;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the spot light direction vector
  //----------------------------------------------------------------------------------------------------------------------
  Vec4 m_dir;

  }; // end of class SpotLight
}// end of namespace
#endif

//----------------------------------------------------------------------------------------------------------------------

