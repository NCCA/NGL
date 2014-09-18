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

#include "Light.h"
#include "ShaderLib.h"
#include <boost/format.hpp>

//----------------------------------------------------------------------------------------------------------------------
/// @file Light.cpp
/// @brief implementation files for Light class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Light::Light(const Vec3 &_pos,const Colour& _col, LIGHTMODES _lightMode )
{
  // zero now means un-assigned
  m_position.set(_pos);
  m_diffuse.set(_col);
  m_specular.set(_col);
  m_lightMode = _lightMode;
  m_constantAtten=1.0;
  m_linearAtten=0.0;
  m_quadraticAtten=0.0;
  m_active=true;
  // set the w for our light modes
  m_position.m_w=static_cast<Real>(m_lightMode);
  // as per the orange book we use this value along with pos.m_w to determine the light
  // type.
  m_cutoffAngle=180;
}

Light::Light(const Light &_l)
{
  m_position=_l.m_position;
  m_diffuse=_l.m_diffuse;
  m_specular=_l.m_specular;
  m_lightMode = _l.m_lightMode;
  m_constantAtten=_l.m_constantAtten;
  m_linearAtten=_l.m_linearAtten;
  m_quadraticAtten=_l.m_quadraticAtten;
  m_active=_l.m_active;
  // set the w for our light modes
  m_position.m_w=static_cast<Real>(_l.m_lightMode);
  // as per the orange book we use this value along with pos.m_w to determine the light
  // type.
  m_cutoffAngle=_l.m_cutoffAngle;
}

//----------------------------------------------------------------------------------------------------------------------
Light::Light(const Vec3 &_pos,const Colour& _col, const Colour& _specColour,LIGHTMODES _lightMode  )
{
  // zero now means un-assigned
  m_position.set(_pos);
  m_diffuse.set(_col);
  m_specular.set(_specColour);
  m_lightMode=_lightMode;
  m_constantAtten=1.0;
  m_linearAtten=0.0;
  m_quadraticAtten=0.0;
  m_active=true;
  // set the w for our light modes
  m_position.m_w=static_cast<Real>(m_lightMode);
  m_cutoffAngle=180;


}

//----------------------------------------------------------------------------------------------------------------------
void Light::show()
{
  ///@todo write code to show the light as some stage

}

//----------------------------------------------------------------------------------------------------------------------
void Light::enable()
{
  m_active=true;
}

//----------------------------------------------------------------------------------------------------------------------
void Light::disable()
{
  m_active=false;
}

//----------------------------------------------------------------------------------------------------------------------
void Light::setAttenuation(Real _constant, Real _linear,  Real _quadratic  )
{
	m_constantAtten=_constant;
	m_linearAtten=_linear;
	m_quadraticAtten=_quadratic;
}



void Light::loadToShader(std::string _uniformName )const
{

  ShaderLib *shader=ShaderLib::instance();
/*
/// struct Lights
/// {
///   vec3 position;
///   vec4 ambient;
///   vec4 diffuse;
///   vec4 specular;
/// };
  */
  if(m_active==true)
  {
    Vec4 pos=m_transform*m_position;
    shader->setShaderParam4f(_uniformName+".position",pos.m_x,pos.m_y,pos.m_z,Real(m_lightMode));
    shader->setShaderParam4f(_uniformName+".ambient",m_ambient.m_r,m_ambient.m_g,m_ambient.m_b,m_ambient.m_a);
    shader->setShaderParam4f(_uniformName+".diffuse",m_diffuse.m_r,m_diffuse.m_g,m_diffuse.m_b,m_diffuse.m_a);
    shader->setShaderParam4f(_uniformName+".specular",m_specular.m_r,m_specular.m_g,m_specular.m_b,m_specular.m_a);
    shader->setShaderParam1f(_uniformName+".constantAttenuation",m_constantAtten);
    shader->setShaderParam1f(_uniformName+".linearAttenuation",m_linearAtten);
    shader->setShaderParam1f(_uniformName+".quadraticAttenuation",m_quadraticAtten);
    shader->setShaderParam1f(_uniformName+".spotCosCutoff",m_cutoffAngle);

  }
  else
  {
    // turn light off by setting 0 values
    shader->setShaderParam4f(_uniformName+".position",0,0,0,Real(m_lightMode));
    shader->setShaderParam4f(_uniformName+".ambient",0,0,0,0);
    shader->setShaderParam4f(_uniformName+".diffuse",0,0,0,0);
    shader->setShaderParam4f(_uniformName+".specular",0,0,0,0);
  }
}

void Light::setTransform(Mat4 &_t)
{
  m_transform=_t;
}

} // end ngl namespacee
