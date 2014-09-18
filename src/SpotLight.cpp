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
//---------------------------------------------------------------------------
#include "SpotLight.h"
#include "ShaderLib.h"
#include <boost/format.hpp>
//----------------------------------------------------------------------------------------------------------------------
/// @file SpotLight.cpp
/// @brief implementation files for SpotLight class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
SpotLight::SpotLight(const Vec3& _pos, const Vec3& _aim, const Colour& _col  ):
            Light( _pos, _col,SPOTLIGHT )
{
  // set up m_direction and default values
  m_dir=_aim-_pos;
  m_dir.normalize();
  m_dir[3]=0;

  // set some good default values
  m_cutoffAngle = 45.0f;
  m_innerCutoffAngle=25.0f;
  m_spotExponent = 2.0f;

  m_constantAtten = 1.5f;
  m_linearAtten = 0.0f;
  m_quadraticAtten = 0.0f;
  m_position=_pos;
  m_aim=_aim;
  m_transform.identity();
m_lightMode=SPOTLIGHT;
}

SpotLight::SpotLight(const SpotLight &_l) : Light(_l)
{
  m_aim=_l.m_aim;
  m_transform.identity();
  m_lightMode=SPOTLIGHT;

}


//----------------------------------------------------------------------------------------------------------------------
void SpotLight::set(const Vec3 &_pos, const Vec3 &_dir,const Colour& _col )
{
  // set up m_direction and default values
  m_dir = _dir;
  m_dir.normalize();
  m_dir[3]=0;
  m_diffuse=_col;
  m_position=_pos;
  m_position[3]=1;
  // set some good default values
  m_cutoffAngle    = 45.0f;
  m_spotExponent   = 0.0f;
  m_constantAtten  = 1.5f;
  m_linearAtten    = 0.0f;
  m_quadraticAtten = 0.0f;
  m_transform.identity();
  m_lightMode=SPOTLIGHT;


}

//----------------------------------------------------------------------------------------------------------------------
void SpotLight::show()
{
  // call superclass show method
  Light::show();
  this->enable();
  /// @todo add some visualisation code at some stage
}

//----------------------------------------------------------------------------------------------------------------------
void SpotLight::aim( const Vec4& _pos )
{
  Vec4 dir= _pos-m_position;
  // this is a vector so set 0 component
  dir[3]=0;
  dir.normalize();
  m_aim=_pos;
  m_dir=dir;
}



//----------------------------------------------------------------------------------------------------------------------
void SpotLight::enable()
{
  m_active=true;
}

//----------------------------------------------------------------------------------------------------------------------
void SpotLight::setParams( const Real _cutoff,const Real _exponent, const Real _constant, const Real _linear, const Real _quadratic  )
{
  // we need to convert this to the correct values
  m_cutoffAngle=cos(radians(_cutoff));
  m_spotExponent=_exponent;
  m_constantAtten=_constant;
  m_linearAtten=_linear;
  m_quadraticAtten=_quadratic;
}

void SpotLight::setCutoff(const Real &_cutoff  )
{
  m_cutoffAngle=cos(radians(_cutoff));
}
void SpotLight::setInnerCutoff(const Real &_cutoff )
{
  m_innerCutoffAngle=cos(radians(_cutoff));
}
void SpotLight::loadToShader( std::string _uniformName)const
{

  ShaderLib *shader=ShaderLib::instance();
  /// struct Lights
  /// {
  ///   vec4 position;
  ///   vec3 direction;
  ///   vec4 ambient;
  ///   vec4 diffuse;
  ///   vec4 specular;
  ///   float spotCosCutoff;
  ///   float constantAttenuation;
  ///   float linearAttenuation;
  ///   float quadraticAttenuation;
  /// };
  if(m_active==true)
  {
    Vec4 pos=m_transform*m_position;
    Vec4 dir=m_transform*m_dir;
    shader->setShaderParam4f(_uniformName+".position",pos.m_x,pos.m_y,pos.m_z,float(m_lightMode));
    shader->setShaderParam3f(_uniformName+".direction",dir.m_x,dir.m_y,dir.m_z);
    shader->setShaderParam4f(_uniformName+".ambient",m_ambient.m_r,m_ambient.m_g,m_ambient.m_b,m_ambient.m_a);
    shader->setShaderParam4f(_uniformName+".diffuse",m_diffuse.m_r,m_diffuse.m_g,m_diffuse.m_b,m_diffuse.m_a);
    shader->setShaderParam4f(_uniformName+".specular",m_specular.m_r,m_specular.m_g,m_specular.m_b,m_specular.m_a);
    shader->setShaderParam1f(_uniformName+".spotCosCutoff",m_cutoffAngle);
    shader->setShaderParam1f(_uniformName+".spotCosInnerCutoff",m_innerCutoffAngle);
    shader->setShaderParam1f(_uniformName+".spotExponent",m_spotExponent);
    shader->setShaderParam1f(_uniformName+".constantAttenuation",m_constantAtten);
    shader->setShaderParam1f(_uniformName+".linearAttenuation",m_linearAtten);
    shader->setShaderParam1f(_uniformName+".quadraticAttenuation",m_quadraticAtten);
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
void SpotLight::setTransform(Mat4 &_t)
{
  m_transform=_t;
}

void SpotLight::writeXML(rapidxml::xml_document<> &_doc, std::string _tag) const
{
//  char *nodeName = _doc.allocate_string(_tag.c_str());        // Allocate string and copy name into it

//  rapidxml::xml_node<>* root = _doc.allocate_node(rapidxml::node_element, nodeName);
//  _doc.append_node(root);

//  m_position.writeXML(_doc,root,"position");
//  m_diffuse.writeXML(_doc,root,"colour");
//  m_specular.writeXML(_doc,root,"specColour");
//  char *value = _doc.allocate_string(boost::str( boost::format(" %f") % m_constantAtten).c_str());
//  rapidxml::xml_node<>* child = _doc.allocate_node(rapidxml::node_element, "constantAtten",value);
//  root->append_node(child);

//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_linearAtten).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "linearAtten",value);
//  root->append_node(child);

//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_quadraticAtten).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "quadraticAtten",value);
//  root->append_node(child);
//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_innerCutoffAngle).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "innerCutoff",value);
//  root->append_node(child);

//  value = _doc.allocate_string(boost::str( boost::format(" %f") % m_spotExponent).c_str());
//  child = _doc.allocate_node(rapidxml::node_element, "exponent",value);
//  root->append_node(child);
//  m_position.writeXML(_doc,root,"position");
//  m_aim.writeXML(_doc,root,"aim");
//  m_dir.writeXML(_doc,root,"dir");





  }


} // end ngl namespace

//----------------------------------------------------------------------------------------------------------------------
