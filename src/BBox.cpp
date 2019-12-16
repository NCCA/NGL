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
//----------------------------------------------------------------------------------------------------------------------
/// @file BBox.cpp
/// @brief a simple bounding box class
//----------------------------------------------------------------------------------------------------------------------
#include "BBox.h"
#include "VAOFactory.h"
#include "SimpleIndexVAO.h"
#include <iostream>
namespace ngl
{
constexpr GLubyte indices[]=  {
                                0,1,5,0,4,5, // back
                                3,2,6,7,6,3, // front
                                0,1,2,3,2,0, // top
                                4,5,6,7,6,4, // bottom
                                0,3,4,4,7,3,
                                1,5,2,2,6,5
                              };
// indices for line loop
constexpr GLubyte lindices[]=  {
                                  0,3,7,4,0, /// Left
                                  0,1,5,4,0, /// back quad
                                  1,2,6,5,1, // right
                                  0,1,2,3,0,
                                  4,5,6,7,4
                                 };

//----------------------------------------------------------------------------------------------------------------------
BBox::BBox( const Vec3& _center,  Real _width, Real _height, Real _depth  ) noexcept
{
	// Calculate the Vertices based on the w,h,d params passed in the box is asumed
	// to be centered on the _center with equal w / h / d
	// -x +y -z

	m_vert[0].m_x=_center.m_x-(_width/2.0f); m_vert[0].m_y=_center.m_y+(_height/2.0f); m_vert[0].m_z=_center.m_z-(_depth/2.0f);
	// + x -y -z
	m_vert[1].m_x=_center.m_x+(_width/2.0f); m_vert[1].m_y=_center.m_y+(_height/2.0f); m_vert[1].m_z=_center.m_z-(_depth/2.0f);
	m_vert[2].m_x=_center.m_x+(_width/2.0f); m_vert[2].m_y=_center.m_y+(_height/2.0f); m_vert[2].m_z=_center.m_z+(_depth/2.0f);
	m_vert[3].m_x=_center.m_x-(_width/2.0f); m_vert[3].m_y=_center.m_y+(_height/2.0f); m_vert[3].m_z=_center.m_z+(_depth/2.0f);
	m_vert[4].m_x=_center.m_x-(_width/2.0f); m_vert[4].m_y=_center.m_y-(_height/2.0f); m_vert[4].m_z=_center.m_z-(_depth/2.0f);
	m_vert[5].m_x=_center.m_x+(_width/2.0f); m_vert[5].m_y=_center.m_y-(_height/2.0f); m_vert[5].m_z=_center.m_z-(_depth/2.0f);
	m_vert[6].m_x=_center.m_x+(_width/2.0f); m_vert[6].m_y=_center.m_y-(_height/2.0f); m_vert[6].m_z=_center.m_z+(_depth/2.0f);
	m_vert[7].m_x=_center.m_x-(_width/2.0f); m_vert[7].m_y=_center.m_y-(_height/2.0f); m_vert[7].m_z=_center.m_z+(_depth/2.0f);

	//Store the _center
	m_center=_center;
	// Setup the Plane Normals for Collision Detection
	m_norm[0].set(0.0f,1.0f,0.0f);
	m_norm[1].set(0.0f,-1.0f,0.0f);
	m_norm[2].set(1.0f,0.0f,0.0f);
	m_norm[3].set(-1.0f,0.0f,0.0f);
	m_norm[4].set(0.0f,0.0f,1.0f);
	m_norm[5].set(0.0f,0.0f,-1.0f);
	// store width height and depth
	m_width=_width;
	m_height=_height;
	m_depth=_depth;
	#ifdef USINGIOS_
		m_drawMode=GL_LINE_LOOP;
	#else
		m_drawMode=GL_LINE;
	#endif
  m_vao=nullptr;
  setVAO();
}




//----------------------------------------------------------------------------------------------------------------------
BBox::BBox() noexcept
{
  //default constructor creates a unit BBox
  m_center.m_x=m_center.m_y=m_center.m_z=0.0f;
  #ifdef USINGIOS_
    m_drawMode=GL_LINE_LOOP;
  #else
    m_drawMode=GL_LINE;
  #endif
  m_width=2.0f;
  m_height=2.0f;
  m_depth=2.0f;
  m_vao=nullptr;
  m_noGL=false;
  //setVAO();
}

BBox::BBox(bool _noGL) noexcept :  BBox()
{
  m_noGL=_noGL;
}

BBox::BBox(const BBox &_b) noexcept
{
  m_center=_b.m_center;
  m_width=_b.m_width;
  m_height=_b.m_height;
  m_depth=_b.m_depth;
  m_drawMode=_b.m_drawMode;
  m_minX=_b.m_minX;
  m_maxX=_b.m_maxX;
  m_minY=_b.m_minY;
  m_maxY=_b.m_maxY;
  m_minZ=_b.m_minZ;
  m_maxZ=_b.m_maxZ;
  m_vao=nullptr;
  m_noGL=_b.m_noGL;
  recalculate();
}

BBox& BBox::operator=(const BBox &_b)
{

  m_center=_b.m_center;
  m_width=_b.m_width;
  m_height=_b.m_height;
  m_depth=_b.m_depth;
  m_drawMode=_b.m_drawMode;
  m_minX=_b.m_minX;
  m_maxX=_b.m_maxX;
  m_minY=_b.m_minY;
  m_maxY=_b.m_maxY;
  m_minZ=_b.m_minZ;
  m_maxZ=_b.m_maxZ;
  m_vao.reset(_b.m_vao.get());
  m_noGL=_b.m_noGL;
  return *this;
}


//----------------------------------------------------------------------------------------------------------------------
BBox::BBox( Real _minX, Real _maxX,  Real _minY, Real _maxY, Real _minZ, Real _maxZ  ) noexcept
{

	m_minX=_minX;
	m_maxX=_maxX;
	m_minY=_minY;
	m_maxY=_maxY;
	m_minZ=_minZ;
	m_maxZ=_maxZ;


	m_center.set(0,0,0);

	m_vert[0].m_x=_minX; m_vert[0].m_y=_maxY; m_vert[0].m_z=_minZ;
	m_vert[1].m_x=_maxX; m_vert[1].m_y=_maxY; m_vert[1].m_z=_minZ;
	m_vert[2].m_x=_maxX; m_vert[2].m_y=_maxY; m_vert[2].m_z=_maxZ;
	m_vert[3].m_x=_minX; m_vert[3].m_y=_maxY; m_vert[3].m_z=_maxZ;

	m_vert[4].m_x=_minX; m_vert[4].m_y=_minY; m_vert[4].m_z=_minZ;
	m_vert[5].m_x=_maxX; m_vert[5].m_y=_minY; m_vert[5].m_z=_minZ;
	m_vert[6].m_x=_maxX; m_vert[6].m_y=_minY; m_vert[6].m_z=_maxZ;
	m_vert[7].m_x=_minX; m_vert[7].m_y=_minY; m_vert[7].m_z=_maxZ;
	#ifdef USINGIOS_
		m_drawMode=GL_LINE_LOOP;
	#else
		m_drawMode=GL_LINE;
	#endif
	m_width=m_maxX-m_minX;
	m_height=m_maxY-m_minY;
	m_depth=m_maxZ-m_minZ;
  m_vao=nullptr;
	setVAO();

}


void BBox::setExtents( Real _minX, Real _maxX,  Real _minY, Real _maxY, Real _minZ, Real _maxZ  ) noexcept
{

  m_minX=_minX;
  m_maxX=_maxX;
  m_minY=_minY;
  m_maxY=_maxY;
  m_minZ=_minZ;
  m_maxZ=_maxZ;

  m_vert[0].m_x=_minX; m_vert[0].m_y=_maxY; m_vert[0].m_z=_minZ;
  m_vert[1].m_x=_maxX; m_vert[1].m_y=_maxY; m_vert[1].m_z=_minZ;
  m_vert[2].m_x=_maxX; m_vert[2].m_y=_maxY; m_vert[2].m_z=_maxZ;
  m_vert[3].m_x=_minX; m_vert[3].m_y=_maxY; m_vert[3].m_z=_maxZ;

  m_vert[4].m_x=_minX; m_vert[4].m_y=_minY; m_vert[4].m_z=_minZ;
  m_vert[5].m_x=_maxX; m_vert[5].m_y=_minY; m_vert[5].m_z=_minZ;
  m_vert[6].m_x=_maxX; m_vert[6].m_y=_minY; m_vert[6].m_z=_maxZ;
  m_vert[7].m_x=_minX; m_vert[7].m_y=_minY; m_vert[7].m_z=_maxZ;
  #ifdef USINGIOS_
    m_drawMode=GL_LINE_LOOP;
  #else
    m_drawMode=GL_LINE;
  #endif
  m_width=m_maxX-m_minX;
  m_height=m_maxY-m_minY;
  m_depth=m_maxZ-m_minZ;
  setVAO();
}


//----------------------------------------------------------------------------------------------------------------------
void BBox::setDrawMode( GLenum _mode) noexcept
{
  m_drawMode=_mode;
  setVAO();
}

void BBox::setVAO()
{
  if(m_noGL == true) return;
	// if were not doing line drawing then use tris
	#ifdef USINGIOS_
		if(m_drawMode !=GL_LINE_LOOP)
	#else
		if(m_drawMode !=GL_LINE)
	#endif
	{
    m_vao=VAOFactory::createVAO("simpleIndexVAO",GL_TRIANGLES) ;

    // now we have our data add it to the VAO, we need to tell the VAO the following
    // how much (in bytes) data we are copying
    // a pointer to the first element of data (in this case the address of the first element of the
    // std::vector
    m_vao->bind();
    m_vao->setData(SimpleIndexVAO::VertexData(8*sizeof(Vec3),m_vert[0].m_x,sizeof(indices),&indices[0],GL_UNSIGNED_BYTE,GL_STATIC_DRAW));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Vec3),0);

    m_vao->setNumIndices(sizeof(indices));
    // finally we have finished for now so time to unbind the VAO
    m_vao->unbind();
  }
  else // we just need to draw the lines
  {
    m_vao=VAOFactory::createVAO("simpleIndexVAO",GL_LINE_LOOP);

    // now we have our data add it to the VAO, we need to tell the VAO the following
    // how much (in bytes) data we are copying
    // a pointer to the first element of data (in this case the address of the first element of the


    m_vao->bind();
    m_vao->setData( SimpleIndexVAO::VertexData(8*sizeof(Vec3),m_vert[0].m_x,sizeof(lindices),&lindices[0],GL_UNSIGNED_BYTE,GL_STATIC_DRAW));
    m_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Vec3),0);

    m_vao->setNumIndices(sizeof(lindices));
    // finally we have finished for now so time to unbind the VAO
    m_vao->unbind();
  }


}


//----------------------------------------------------------------------------------------------------------------------
void BBox::draw() const noexcept
{
#ifndef USINGIOS_
  glPolygonMode(GL_FRONT_AND_BACK,m_drawMode);
  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
#else
  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();
#endif
}
//----------------------------------------------------------------------------------------------------------------------

void BBox::setCenter(const Vec3 &_center, bool _recalc) noexcept
{
	// Calculate the Vertices based on the w,h,d params passed in the box is asumed
	// to be centered on the _center with equal w / h / d
	// -x +y -z
	m_center=_center;
	m_vert[0].m_x=_center.m_x-(m_width/2.0f); m_vert[0].m_y=_center.m_y+(m_height/2.0f); m_vert[0].m_z=_center.m_z-(m_depth/2.0f);
	// + x -y -z
	m_vert[1].m_x=_center.m_x+(m_width/2.0f); m_vert[1].m_y=_center.m_y+(m_height/2.0f); m_vert[1].m_z=_center.m_z-(m_depth/2.0f);
	m_vert[2].m_x=_center.m_x+(m_width/2.0f); m_vert[2].m_y=_center.m_y+(m_height/2.0f); m_vert[2].m_z=_center.m_z+(m_depth/2.0f);
	m_vert[3].m_x=_center.m_x-(m_width/2.0f); m_vert[3].m_y=_center.m_y+(m_height/2.0f); m_vert[3].m_z=_center.m_z+(m_depth/2.0f);
	m_vert[4].m_x=_center.m_x-(m_width/2.0f); m_vert[4].m_y=_center.m_y-(m_height/2.0f); m_vert[4].m_z=_center.m_z-(m_depth/2.0f);
	m_vert[5].m_x=_center.m_x+(m_width/2.0f); m_vert[5].m_y=_center.m_y-(m_height/2.0f); m_vert[5].m_z=_center.m_z-(m_depth/2.0f);
	m_vert[6].m_x=_center.m_x+(m_width/2.0f); m_vert[6].m_y=_center.m_y-(m_height/2.0f); m_vert[6].m_z=_center.m_z+(m_depth/2.0f);
	m_vert[7].m_x=_center.m_x-(m_width/2.0f); m_vert[7].m_y=_center.m_y-(m_height/2.0f); m_vert[7].m_z=_center.m_z+(m_depth/2.0f);
	if(_recalc)
	{
		recalculate();
	}
}

void BBox::width(Real _w, bool _recalc) noexcept
{
  m_width=_w;
  if(_recalc)
  {
    recalculate();
  }
}

void BBox::height(Real _h, bool _recalc) noexcept
{
  m_height=_h;
  if(_recalc)
  {
    recalculate();
  }
}

void BBox::depth(Real _d, bool _recalc) noexcept
{
  m_depth=_d;
  if(_recalc)
  {
    recalculate();
  }
}

void BBox::recalculate() noexcept
{
  // Calculate the Vertices based on the w,h,d params passed in the box is asumed
  // to be centered on the _center with equal w / h / d
  // -x +y -z
  m_vert[0].m_x=m_center.m_x-(m_width/2.0f); m_vert[0].m_y=m_center.m_y+(m_height/2.0f); m_vert[0].m_z=m_center.m_z-(m_depth/2.0f);
  // + x -y -z
  m_vert[1].m_x=m_center.m_x+(m_width/2.0f); m_vert[1].m_y=m_center.m_y+(m_height/2.0f); m_vert[1].m_z=m_center.m_z-(m_depth/2.0f);
  m_vert[2].m_x=m_center.m_x+(m_width/2.0f); m_vert[2].m_y=m_center.m_y+(m_height/2.0f); m_vert[2].m_z=m_center.m_z+(m_depth/2.0f);
  m_vert[3].m_x=m_center.m_x-(m_width/2.0f); m_vert[3].m_y=m_center.m_y+(m_height/2.0f); m_vert[3].m_z=m_center.m_z+(m_depth/2.0f);
  m_vert[4].m_x=m_center.m_x-(m_width/2.0f); m_vert[4].m_y=m_center.m_y-(m_height/2.0f); m_vert[4].m_z=m_center.m_z-(m_depth/2.0f);
  m_vert[5].m_x=m_center.m_x+(m_width/2.0f); m_vert[5].m_y=m_center.m_y-(m_height/2.0f); m_vert[5].m_z=m_center.m_z-(m_depth/2.0f);
  m_vert[6].m_x=m_center.m_x+(m_width/2.0f); m_vert[6].m_y=m_center.m_y-(m_height/2.0f); m_vert[6].m_z=m_center.m_z+(m_depth/2.0f);
  m_vert[7].m_x=m_center.m_x-(m_width/2.0f); m_vert[7].m_y=m_center.m_y-(m_height/2.0f); m_vert[7].m_z=m_center.m_z+(m_depth/2.0f);
  setVAO();
}

//----------------------------------------------------------------------------------------------------------------------

BBox::~BBox() noexcept
{
  if(m_noGL==true)
    m_vao->removeVAO();
}
//----------------------------------------------------------------------------------------------------------------------

} // end namespace ngl



