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

#warning This class is marked for deprecation
#ifndef REMOVEDDEPRECATED

#include "TransformStack.h"
#include "ShaderLib.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file TransformStack.cpp
/// @brief implementation files for TransformStack class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
TransformStack::TransformStack()
{
  m_current.reset();
  m_global.reset();
  m_currentAndGlobal.reset();
  m_stack.resize(MAXNGLTRANSFORMSTACKSIZE,m_current);
  m_index=0.0f;
  m_globalMatrix=1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
TransformStack::TransformStack( const TransformStack& _m  )
{
  m_current=_m.m_current;
  m_global=_m.m_global;
  m_currentAndGlobal=_m.m_currentAndGlobal;
  m_index=_m.m_index;
  m_globalMatrix=_m.m_globalMatrix;
  m_stack.resize(MAXNGLTRANSFORMSTACKSIZE,m_current);
  int stackSize=_m.m_stack.size();
  for(int i=0; i<stackSize; ++i)
  {
    m_stack[i]=_m.m_stack[i];
  }
}

Transformation &TransformStack::getCurrAndGlobal()
{
  m_currentAndGlobal= m_current*m_global;
  return m_currentAndGlobal;
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::pushTransform()
{
  m_globalMatrix*=m_current.getMatrix();

  m_stack[m_index++]=m_current;
  m_current.reset();

}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::pushTransformAndCopy()
{
  m_globalMatrix*=m_current.getMatrix();
  m_stack[m_index++]=m_current;
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::popTransform()
{
  m_current=m_stack[--m_index];
  m_globalMatrix=m_current.getMatrix();
}


void TransformStack::loadMatrixToShader( std::string _param,ACTIVEMATRIX _which )
{
  m_current.loadMatrixToShader(_param,_which);
}

void TransformStack::loadGlobalAndCurrentMatrixToShader( std::string _param, ACTIVEMATRIX _which  )
{
  m_current.loadGlobalAndCurrentMatrixToShader(_param,m_global,_which);
}

void TransformStack::loadGlobalMatrixToShader(std::string _param,  ACTIVEMATRIX _which )
{

  ShaderLib *shader=ShaderLib::instance();
  Mat4 gm=m_globalMatrix*m_current.getMatrix();
  switch (_which)
  {
    case NORMAL :
    {
      shader->setShaderParamFromMat4(_param,gm);
    }
    break;
    case TRANSPOSE :
    {
      gm.transpose();
      shader->setShaderParamFromMat4(_param,gm);
    }
    break;
  case INVERSE : break;

  }
}



//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setPosition(const Vec4 &_pos)
{
	m_current.setPosition(_pos.m_x,_pos.m_y,_pos.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setPosition(const Vec3 &_pos  )
{
	m_current.setPosition(_pos.m_x,_pos.m_y,_pos.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setPosition(Real _x, Real _y,Real _z )
{
	m_current.setPosition(_x,_y,_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::addPosition( const Vec3 &_pos  )
{
	m_current.addPosition(_pos.m_x,_pos.m_y,_pos.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::addPosition( Real _x,   Real _y,  Real _z     )
{
	m_current.addPosition(_x,_y,_z);
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setScale(const Vec4 &_scale )
{
	m_current.setScale(_scale);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setScale(const Vec3 &_scale )
{
	m_current.setScale(_scale.m_x,_scale.m_y,_scale.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setScale(Real _x, Real _y, Real _z )
{
	m_current.setScale(_x,_y,_z);
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::addScale(const Vec3 &_scale  )
{
  m_current.addScale(_scale.m_x,_scale.m_y,_scale.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::addScale( Real _x, Real _y,   Real _z )
{
  m_current.addScale(_x,_y,_z);
}


//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setRotation(const Vec4 &_rot	)
{
	m_current.setRotation(_rot);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setRotation(const Vec3 &_rot )
{
	m_current.setRotation(_rot.m_x,_rot.m_y,_rot.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::setRotation(Real _x,Real _y, Real _z )
{
	m_current.setRotation(_x,_y,_z);
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::addRotation(const Vec3 &_rot )
{
  m_current.addRotation(_rot.m_x,_rot.m_y,_rot.m_z);
}
//----------------------------------------------------------------------------------------------------------------------
void TransformStack::addRotation(Real _x,Real _y,  Real _z )
{
  m_current.addRotation(_x,_y,_z);
}


} // end of namespace ngl
#endif
