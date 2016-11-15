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
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "VAOPrimitives.h"
#include "Util.h"
#include <iostream>
#include "VAOFactory.h"
#include "SimpleVAO.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file VAOPrimitives.cpp
/// @brief implementation files for VAOPrimitives class
//----------------------------------------------------------------------------------------------------------------------
namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
VAOPrimitives::VAOPrimitives() noexcept
{
    createDefaultVAOs();
}


//----------------------------------------------------------------------------------------------------------------------

void VAOPrimitives::draw( const std::string &_name ) noexcept
{
  // get an iterator to the VertexArrayObjects
  auto VAO=m_createdVAOs.find(_name);
  // make sure we have a valid shader
  if(VAO!=m_createdVAOs.end())
  {
    // grab the pointer to the shader and call compile
    VAO->second->bind();
    VAO->second->draw();
    VAO->second->unbind();
  }
  else {std::cerr<<"Warning VAO not know in Primitive list "<<_name.c_str()<<"\n";}

}

void VAOPrimitives::draw( const std::string &_name, GLenum _mode ) noexcept
{
  // get an iterator to the VertexArrayObjects
  auto vao=m_createdVAOs.find(_name);
  // make sure we have a valid shader
  if(vao!=m_createdVAOs.end())
  {
    // grab the pointer to the shader and call compile
    vao->second->bind();
    vao->second->setMode(_mode);
    vao->second->draw();
    vao->second->unbind();
  }
  else {std::cerr<<"Warning VAO not know in Primitive list "<<_name.c_str()<<"\n";}

}

void VAOPrimitives::createVAOFromHeader(const std::string &_name, const Real *_data,  unsigned int _size ) noexcept
{
    AbstractVAO *vao = VAOFactory::createVAO("simpleVAO",GL_TRIANGLES);
;
    // next we bind it so it's active for setting data
    vao->bind();
    // now we have our data add it to the VAO, we need to tell the VAO the following
    // how much (in bytes) data we are copying
    // a pointer to the first element of data (in this case the address of the first element of the
    // std::vector
    vao->setData( SimpleVAO::VertexData(_size*sizeof(Real),_data[0]));
    // in this case we have packed our data in interleaved format as follows
    // u,v,nx,ny,nz,x,y,z
    // If you look at the shader we have the following attributes being used
    // attribute vec3 inVert; attribute 0
    // attribute vec2 inUV; attribute 1
    // attribute vec3 inNormal; attribute 2
    // so we need to set the vertexAttributePointer so the correct size and type as follows
    // vertex is attribute 0 with x,y,z(3) parts of type GL_FLOAT, our complete packed data is
    // sizeof(vertData) and the offset into the data structure for the first x component is 5 (u,v,nx,ny,nz)..x
    vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),5);
    // uv same as above but starts at 0 and is attrib 1 and only u,v so 2
    vao->setVertexAttributePointer(1,2,GL_FLOAT,sizeof(vertData),0);
    // normal same as vertex only starts at position 2 (u,v)-> nx
    vao->setVertexAttributePointer(2,3,GL_FLOAT,sizeof(vertData),2);
    // now we have set the vertex attributes we tell the VAO class how many indices to draw when
    // glDrawArrays is called, in this case we use buffSize (but if we wished less of the sphere to be drawn we could
    // specify less (in steps of 3))
    // In this case each Generic Vertex attribute is 8 elements so we use _size / 8
    vao->setNumIndices(_size/8);
    // finally we have finished for now so time to unbind the VAO
    vao->unbind();
    m_createdVAOs[_name]=vao;
   // std::cout<<_name<<" Num Triangles "<<data.size()/3<<"\n";

}

void VAOPrimitives::createLineGrid( const std::string &_name, Real _width,  Real _depth, int _steps ) noexcept
{
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData vert;
    // claculate the step size for each grid value
  Real wstep=_width/static_cast<Real>(_steps);
  // pre-calc the offset for speed
  Real ws2=_width/2.0f;
  // assign v as our value to change each vertex pair
  Real v1=-ws2;

    // claculate the step size for each grid value
  Real dstep=_depth/static_cast<Real>(_steps);
  // pre-calc the offset for speed
  Real ds2=_depth/2.0f;
  // assign v as our value to change each vertex pair
  Real v2=-ds2;

    for(int i=0; i<=_steps; ++i)
    {
      // vertex 1 x,y,z
      vert.x=-ws2; // x
      vert.z=v1; // y
      vert.y=0.0; // z
      data.push_back(vert);
      // vertex 2 x,y,z
      vert.x=ws2; // x
      vert.z=v1; // y
      data.push_back(vert);


      // vertex 1 x,y,z
      vert.x=v2; // x
      vert.z=ds2; // y
      data.push_back(vert);
      // vertex 2 x,y,z
      vert.x=v2; // x
      vert.z=-ds2; // y
      data.push_back(vert);



      // now change our step value
      v1+=wstep;
      v2+=dstep;
    }

  createVAO(_name,data,GL_LINES);

}

void VAOPrimitives::createSphere( const std::string &_name, Real _radius, int _precision ) noexcept
{
    //  Sphere code based on a function Written by Paul Bourke.
    //  http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
    // the next part of the code calculates the P,N,UV of the sphere for tri_strips

    Real theta1 = 0.0f;
    Real theta2 = 0.0f;
    Real theta3 = 0.0f;

    // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
        // Disallow a negative number for radius.

  if( _radius < 0.0f )
    {
        _radius = -_radius;
    }
    // Disallow a negative number for _precision.
    if( _precision < 4 )
    {
        _precision = 4;
    }
  // now fill in a vertData structure and add to the data list for our sphere
  vertData d;
  for( int i = 0; i < _precision/2; ++i )
  {
    theta1 = i * TWO_PI / _precision - PI2;
    theta2 = (i + 1) * TWO_PI / _precision - PI2;

    for( int j = 0; j <= _precision; ++j )
    {
        theta3 = j * TWO_PI / _precision;

        d.nx = cosf(theta2) * cosf(theta3);
        d.ny = sinf(theta2);
        d.nz = cosf(theta2) * sinf(theta3);
        d.x = _radius * d.nx;
        d.y = _radius * d.ny;
        d.z = _radius * d.nz;

        d.u  = (j/static_cast<Real>(_precision));
        d.v  = 2*(i+1)/static_cast<Real>(_precision);

        data.push_back(d);

        d.nx = cosf(theta1) * cosf(theta3);
        d.ny = sinf(theta1);
        d.nz = cosf(theta1) * sinf(theta3);
        d.x = _radius * d.nx;
        d.y = _radius * d.ny;
        d.z = _radius * d.nz;

        d.u  = (j/static_cast<Real>(_precision));
        d.v  = 2*i/static_cast<Real>(_precision);
        data.push_back(d);
      } // end inner loop
  }// end outer loop

  createVAO(_name,data,GL_TRIANGLE_STRIP);

}


void VAOPrimitives::createCapsule( const std::string &_name,  const Real _radius, const Real _height,  const int _precision ) noexcept

{
  // based on code from here
  // https://code.google.com/p/rgine/source/browse/trunk/RGine/opengl/src/RGLShapes.cpp
  /// @todo add UV's at some stage
  std::vector <vertData> data;
   vertData d;
   Real h = _height / 2;
   Real s, c, s1, c1, o;
   Real sb, cb, sb1, cb1;
   Real ang = (1.0f / _precision) * static_cast<Real>(M_PI);
   for (int i = 0; i < 2 * _precision; ++i)
   {

     c = _radius * cosf(ang * i);
     c1= _radius * cosf(ang * (i + 1));
     s = _radius * sinf(ang * i);
     s1 =_radius * sinf(ang * (i + 1));
     //side top
     d.x = c1;
     d.y = h;
     d.z = s1;

     d.nx=c1;
     d.ny= 0.0;
     d.nz=s1;
     data.push_back(d);
     d.x = c;
     d.z = s;
     d.nx=c;
     d.nz=s;
     data.push_back(d);
     d.y = -h;
     data.push_back(d);

     //side bot
     data.push_back(d);
     d.x = c1;
     d.z = s1;
     d.nx= c1;
     d.nz=s1;
     data.push_back(d);
     d.x = c1;
     d.y = h;
     d.z = s1;
     d.nx=c1;
     d.nz=s1;
     data.push_back(d);

     for (int j = 0; j <=_precision; ++j)
     {
       if (j < _precision / 2)
       {
         o = h;
       }
       else
       {
         o = -h;
       }
       //longitude
       s = -sinf(ang * i);
       s1 = -sinf(ang * (i + 1));
       c = cosf(ang * i);
       c1 = cosf(ang * (i + 1));
       //latitude
       sb = _radius * sinf(ang * j);
       sb1 = _radius * sinf(ang * (j + 1));
       cb = _radius * cosf(ang * j);
       cb1 = _radius * cosf(ang * (j + 1));
       if (j != _precision - 1)
       {
         d.nx=d.x = sb * c;
         d.ny=d.y = cb + o;
         d.nz=d.z = sb * s;
         data.push_back(d);
         d.nx=d.x = sb1 * c;
         d.ny=d.y = cb1 + o;
         d.nz=d.z = sb1 * s;
         data.push_back(d);
         d.nx=d.x = sb1 * c1;
         d.ny=d.y = cb1 + o;
         d.nz=d.z = sb1 * s1;
         data.push_back(d);
       }
       if (j != 0)
       {
         d.nx=d.x = sb * c;
         d.ny=d.y = cb + o;
         d.nz=d.z = sb * s;
         data.push_back(d);
         d.nx=d.x = sb1 * c1;
         d.ny=d.y = cb1 + o;
         d.nz=d.z = sb1 * s1;
         data.push_back(d);
         d.nx=d.x = sb * c1;
         d.ny=d.y = cb + o;
         d.nz=d.z = sb * s1;
         data.push_back(d);
       }
     }
   }
  createVAO(_name,data,GL_TRIANGLES);
// end citation

}

void VAOPrimitives::createVAO(const std::string &_name,const std::vector<vertData> &_data,	const GLenum _mode) noexcept
{

  AbstractVAO *vao = VAOFactory::createVAO("simpleVAO",_mode);
  // next we bind it so it's active for setting data
  vao->bind();

  // now we have our data add it to the VAO, we need to tell the VAO the following
  // how much (in bytes) data we are copying
  // a pointer to the first element of data (in this case the address of the first element of the
  // std::vector
  vao->setData(SimpleVAO::VertexData(_data.size()*sizeof(vertData),_data[0].u));
  // in this case we have packed our data in interleaved format as follows
  // u,v,nx,ny,nz,x,y,z
  // If you look at the shader we have the following attributes being used
  // attribute vec3 inVert; attribute 0
  // attribute vec2 inUV; attribute 1
  // attribute vec3 inNormal; attribure 2
  // so we need to set the vertexAttributePointer so the correct size and type as follows
  // vertex is attribute 0 with x,y,z(3) parts of type GL_FLOAT, our complete packed data is
  // sizeof(vertData) and the offset into the data structure for the first x component is 5 (u,v,nx,ny,nz)..x
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),5);
  // uv same as above but starts at 0 and is attrib 1 and only u,v so 2
  vao->setVertexAttributePointer(1,2,GL_FLOAT,sizeof(vertData),0);
  // normal same as vertex only starts at position 2 (u,v)-> nx
  vao->setVertexAttributePointer(2,3,GL_FLOAT,sizeof(vertData),2);
  // now we have set the vertex attributes we tell the VAO class how many indices to draw when
  // glDrawArrays is called, in this case we use buffSize (but if we wished less of the sphere to be drawn we could
  // specify less (in steps of 3))
  vao->setNumIndices(_data.size());
  // finally we have finished for now so time to unbind the VAO
  vao->unbind();
  m_createdVAOs[_name]=vao;
 // std::cout<<_name<<" Num Triangles "<<_data.size()/3<<"\n";

}

/*----------------------------------------------------------------------------------------------------------------------
 * Compute lookup table of cos and sin values forming a cirle
 * borrowed from free glut implimentation of primitive drawing
 *
 * Notes:
 *    It is the responsibility of the caller to free these tables
 *    The size of the table is (n+1) to form a connected loop
 *    The last entry is exactly the same as the first
 *    The sign of n can be flipped to get the reverse loop
 */
//----------------------------------------------------------------------------------------------------------------------


void VAOPrimitives::fghCircleTable(std::unique_ptr<Real []> &io_sint, std::unique_ptr<Real []> &io_cost,  int _n  ) noexcept
{
  unsigned int i;
  /* Determine the angle between samples */
  const Real angle = 2*PI/( ( _n == 0 ) ? 1 : _n );
  /* Table size, the sign of n flips the circle direction */
  int size = abs(_n);

  /* Allocate memory for n samples, plus duplicate of first entry at the end */
  io_sint.reset( new Real[size+1]);
  io_cost.reset( new Real[size+1]);
  /* Compute cos and sin around the circle */
  io_sint[0] = 0.0;
  io_cost[0] = 1.0;

  for (i=1; i<static_cast<unsigned int>(size); ++i)
  {
    io_sint[i] = sinf(angle*i);
    io_cost[i] = cosf(angle*i);
  }
  /* Last sample is duplicate of the first */
  io_sint[static_cast<unsigned int>(size)] = io_sint[0];
  io_cost[static_cast<unsigned int>(size)] = io_cost[0];
}

//----------------------------------------------------------------------------------------------------------------------
void VAOPrimitives::createCylinder(const std::string &_name,  Real _radius,const Real _height,unsigned int _slices,unsigned int _stacks ) noexcept
{
  /* Step in z and radius as stacks are drawn. */

  Real z0,z1;
  const Real zStep = _height / ( ( _stacks > 0 ) ? _stacks : 1 );

  /* Pre-computed circle */
  std::unique_ptr<Real []> sint;
  std::unique_ptr<Real []> cost;


  fghCircleTable(sint,cost,static_cast<int>(-_slices));

  /* Do the stacks */
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData d;
  z0 = 0.0;
  z1 = zStep;
  // texture co-ords start at 0,0
  // texture steps
  Real du=1.0f/_stacks;
  Real dv=1.0f/_slices;
  /* Cover each stack with a quad strip, except the top stack */
  Real u=0.0;
  Real v=0.0;

  for(unsigned int i=1; i<=_stacks+1; ++i )
  {
    if(i==_stacks)
    {
        z1 = _height;
    }
    for(unsigned int j=0; j<=_slices-1; ++j)
    {
      // vert 1;
      d.u=u;
      d.v=v;
      d.nx=sint[j];
      d.ny=cost[j];
      d.nz=0;
      d.x=sint[j]*_radius;
      d.y=cost[j]*_radius;
      d.z=-z0/2.0f;
      data.push_back(d);
      // vert 2
      d.u=u;
      d.v=v+dv;
      d.z=-z1/2.0f;
      data.push_back(d);
      // vert 3
      d.u=u+du;
      d.v=v;
      d.nx=sint[j+1];
      d.ny=cost[j+1];
      d.x=sint[j+1]*_radius;
      d.y=cost[j+1]*_radius;
      d.z=-z0/2.0f;
      data.push_back(d);


      // vert 1;
      d.u=u+du;
      d.v=v;
      d.nx=sint[j+1];
      d.ny=cost[j+1];
      d.nz=0;
      d.x=sint[j+1]*_radius;
      d.y=cost[j+1]*_radius;
      d.z=-z0/2.0f;
      data.push_back(d);

      // vert 1;
      d.u=u;
      d.v=v+dv;
      d.nx=sint[j];
      d.ny=cost[j];
      d.nz=0;
      d.x=sint[j]*_radius;
      d.y=cost[j]*_radius;
      d.z=-z1/2.0f;
      data.push_back(d);

      // vert 1;
      d.u=u+du;
      d.v=v+dv;
      d.nx=sint[j+1];
      d.ny=cost[j+1];
      d.nz=0;
      d.x=sint[j+1]*_radius;
      d.y=cost[j+1]*_radius;
      d.z=-z1/2.0f;
      data.push_back(d);

      u+=du;
    }
    v+=dv;
    u=0.0f;
    z0 = z1; z1 += zStep;
   }
    // create VAO
  createVAO(_name,data,GL_TRIANGLES);

}

//----------------------------------------------------------------------------------------------------------------------
void VAOPrimitives::createCone(const std::string &_name, Real _base, Real _height, unsigned int _slices,unsigned int _stacks  ) noexcept
{
  /* Step in z and radius as stacks are drawn. */
  Real z0,z1;
  Real r0,r1;

  const Real zStep = _height / ( ( _stacks > 0 ) ? _stacks : 1 );
  const Real rStep = _base / ( ( _stacks > 0 ) ? _stacks : 1 );

  /* Scaling factors for vertex normals */

  const Real cosn = ( _height / sqrtf ( _height * _height + _base * _base ));
  const Real sinn = ( _base   / sqrtf ( _height * _height + _base * _base ));

  /* Pre-computed circle */
  std::unique_ptr<Real []> sint;
  std::unique_ptr<Real []> cost;
  fghCircleTable(sint,cost,static_cast<int>(-_slices));

  z0 = 0.0f;
  z1 = zStep;

  r0 = _base;
  r1 = r0 - rStep;
  // texture co-ords start at 0,0
  // texture steps
  Real du=1.0f/_stacks;
  Real dv=1.0f/_slices;
  /* Cover each stack with a quad strip, except the top stack */
  Real u=1.0f;
  Real v=1.0f;
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData d;
  for(unsigned int i=0; i<_stacks; i++ )
  {
    for(unsigned int j=0; j<=_slices; j++)
    {
      d.u=u;
      d.v=v;
      d.nx = cost[j]*cosn; //ctheta;
      d.ny = sint[j] * sinn ;//-stheta;
      d.nz = sinn;// sphi;

      d.x=cost[j]*r0;
      d.y=sint[j]*r0;
      d.z=z0;
      data.push_back(d);
      // now for the next verts
      d.u=u;
      d.v=v-dv;

      d.x=cost[j]*r1;
      d.y=sint[j]*r1;
      d.z=z1;
      data.push_back(d);
      u-=du;
    }
    v-=dv;
    u=1.0;
    z0 = z1; z1 += zStep;
    r0 = r1; r1 -= rStep;

  }
  // create VAO
  createVAO(_name,data,GL_TRIANGLE_STRIP);
}

//----------------------------------------------------------------------------------------------------------------------
void VAOPrimitives::createDisk(const std::string &_name, const Real _radius, unsigned int _slices ) noexcept
{
  /* Pre-computed circle */
  std::unique_ptr<Real []> sint;
  std::unique_ptr<Real []> cost;
  fghCircleTable(sint,cost,static_cast<int>(-_slices));
  // as were using a triangle fan its  vert at the centere then
  //

  // texture co-ords start at 0,0
  // texture steps
  Real du=1.0f/_slices;

  Real u=0.0f;
  Real v=0.0f;
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData d;
  // as we are doing a tri fan this is the center
  d.u=u;
  d.v=v;
  d.nx=0.0f;
  d.ny=0.0f;
  d.nz=-1.0f;
  d.x=0;
  d.y=0;
  d.z=0;
  data.push_back(d);
  v=1.0;

  for (unsigned int j=0; j<=_slices; ++j)
  {
    d.u=u;
    d.v=v;
    // normals set above
    d.x=cost[j]*_radius;
    d.y=sint[j]*_radius;
    // z set above
    data.push_back(d);
    u+=du;
  }
  // create VBO
  createVAO(_name,data,GL_TRIANGLE_FAN);
}


//----------------------------------------------------------------------------------------------------------------------
void VAOPrimitives::createTorus(const std::string &_name, Real _minorRadius, Real _majorRadius,unsigned int _nSides, unsigned int _nRings, bool _flipTX ) noexcept
{
    Real  iradius = _minorRadius, oradius = _majorRadius, phi, psi, dpsi, dphi;

    Real spsi, cpsi, sphi, cphi ;

    if ( _nSides < 1 ) { _nSides = 1; }
    if ( _nRings < 1 ) { _nRings = 1; }

    /* Increment the number of sides and rings to allow for one more point than surface */
    _nSides ++ ;
    _nRings ++ ;
    // should use vec3 / 2 for these at some stage
    std::unique_ptr<Real []>vertex( new Real[3 * _nSides * _nRings]);
    std::unique_ptr<Real []>normal( new Real[3 * _nSides * _nRings]);
    std::unique_ptr<Real []>uv( new Real[2*_nSides*_nRings*2]);

    dpsi =  2.0f * static_cast<Real>(M_PI) / (_nRings - 1) ;
    dphi = -2.0f * static_cast<Real>(M_PI) / (_nSides - 1) ;
    psi  = 0.0f;
    Real uStep=1.0f/_nRings;
    Real vStep=1.0f/_nSides;
    Real tu=0.0f;
    Real tv=0.0f;
    // pre compute the values for the torus
    for(unsigned int j=0; j<_nRings; ++j )
    {
      cpsi = cosf ( psi ) ;
      spsi = sinf ( psi ) ;
      phi = 0.0;
      for(unsigned int i=0; i<_nSides; ++i )
      {
        unsigned int offset = 3 * ( j * _nSides + i ) ;
        cphi = cosf( phi ) ;
        sphi = sinf( phi ) ;
        vertex[offset] = cpsi * ( oradius + cphi * iradius ) ;
        vertex[offset+1] = spsi * ( oradius + cphi * iradius ) ;
        vertex[offset+2] = sphi * iradius  ;
        normal[offset] = cpsi * cphi ;
        normal[offset+1] = spsi * cphi ;
        normal[offset+2] =        sphi ;
        if (_flipTX)
        {
          uv[offset]=tv;
          uv[offset+1]=tu;
        }
        else
        {
          uv[offset]=tu;
          uv[offset+1]=tv;
        }
        tu+=uStep;
        phi += dphi;
        } // end of _nSides loop
        tu=0.0f;
        tv+=vStep;
        psi += dpsi;
      }  // end of _nRings loop

    // a std::vector to store our verts, remember vector packs contiguously so we can use it
    std::vector <vertData> data;
    vertData d;
    for(unsigned int i=0; i<_nSides-1; ++i )
    {
        for(unsigned int j=0; j<_nRings-1; ++j )
        {
            unsigned int offset = 3 * ( j * _nSides + i ) ;
           // n=normal[offset];
           // v=vertex[offset];
           // t=uv[offset];
            d.u=uv[offset];
            d.v=uv[offset+1];
            d.nx=normal[offset];
            d.ny=normal[offset+1];
            d.nz=normal[offset+2];
            d.x=vertex[offset];
            d.y=vertex[offset+1];
            d.z=vertex[offset+2];
      //V1
            data.push_back(d);
            // vert
            //n=normal+offset+3;
            //v=vertex+offset+3;
            //t=uv+offset+3;
            d.u=uv[offset+3];
            d.v=uv[offset+4];
            d.nx=normal[offset+3];
            d.ny=normal[offset+4];
            d.nz=normal[offset+5];
            d.x=vertex[offset+3];
            d.y=vertex[offset+4];
            d.z=vertex[offset+5];
      //V2
            data.push_back(d);

            //n=normal + offset + 3 * _nSides + 3;
            //v=vertex + offset + 3 * _nSides + 3;
            //t=uv+ offset+3*_nSides+3;
            // next vert
            d.u=uv[(offset+3*_nSides+3)];
            d.v=uv[(offset+3*_nSides+3)+1];
            d.nx=normal[(offset + 3 * _nSides + 3)];
            d.ny=normal[(offset + 3 * _nSides + 3)+1];
            d.nz=normal[(offset + 3 * _nSides + 3)+2];
            d.x=vertex[(offset + 3 * _nSides + 3)];
            d.y=vertex[(offset + 3 * _nSides + 3)+1];
            d.z=vertex[(offset + 3 * _nSides + 3)+2];
      //V3
            data.push_back(d);


//      n=normal+offset;
//      v=vertex+offset;
//      t=uv+offset;
      d.u=uv[offset];
      d.v=uv[offset+1];
      d.nx=normal[offset];
      d.ny=normal[offset+1];
      d.nz=normal[offset+2];
      d.x=vertex[offset];
      d.y=vertex[offset+1];
      d.z=vertex[offset+2];
      //V1
      data.push_back(d);


      //n=normal[(offset + 3 * _nSides + 3)];
      //v=vertex[(offset + 3 * _nSides + 3)];
      //t=uv[(offset+3*_nSides+3)];
      // next vert
      d.u=uv[(offset+3*_nSides+3)];
      d.v=uv[(offset+3*_nSides+3)+1];
      d.nx=normal[(offset + 3 * _nSides + 3)];
      d.ny=normal[(offset + 3 * _nSides + 3)+1];
      d.nz=normal[(offset + 3 * _nSides + 3)+2];
      d.x=vertex[(offset + 3 * _nSides + 3)];
      d.y=vertex[(offset + 3 * _nSides + 3)+1];
      d.z=vertex[(offset + 3 * _nSides + 3)+2];
      //V3
      data.push_back(d);

     // n=normal[ (offset + 3 * _nSides)];
     // v= vertex[(offset + 3 * _nSides)];
     // t= uv[(offset+3*_nSides)];
      // next vert
      d.u=uv[(offset+3*_nSides)];
      d.v=uv[(offset+3*_nSides)+1];
      d.nx=normal[ (offset + 3 * _nSides)];
      d.ny=normal[ (offset + 3 * _nSides)+1];
      d.nz=normal[ (offset + 3 * _nSides)+2];
      d.x=vertex[(offset + 3 * _nSides)];
      d.y=vertex[(offset + 3 * _nSides)+1];
      d.z=vertex[(offset + 3 * _nSides)+2];
      data.push_back(d);

        } // end _nRings
    } // end _nSides

    // now create the VBO

  createVAO(_name,data,GL_TRIANGLES);
}

//----------------------------------------------------------------------------------------------------------------------
void VAOPrimitives::createTrianglePlane(const std::string &_name,const Real _width,const Real _depth,const int _wP,const int _dP,const Vec3 &_vN) noexcept
{
  // calculate the VBO size basically we have 2 tris per quad based on the width and depth
  // _precision.

  // as our plane is centered on 0.0 we range from Width/2.0 and Depth/2.0
  Real w2=_width/2.0f;
  Real d2=_depth/2.0f;
  // calculate the steps for each quad / tri
  Real wStep=_width/_wP;
  Real dStep=_depth/_dP;
  // texture co-ords start at 0,0
  // texture steps
  Real du=0.9f/_wP;
  Real dv=0.9f/_dP;

  Real u=0.0f;
  Real v=0.0f;

  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData vert;

  for(Real d=-d2; d<d2; d+=dStep)
  {
    for(Real w=-w2; w<w2; w+=wStep)
    {
      /* tri 1
      // counter clock wise
      3
      | \
      |  \
      |   \
      1____2
      */
      // the normals are always the same so set them for d first
      vert.nx=_vN.m_x;
      vert.ny=_vN.m_y;
      vert.nz=_vN.m_z;
      // y is always 0 as in a plane
      vert.y=0.0f;
      // now for the per vert stuff
      vert.u=u; vert.v=v+dv;  vert.x=w;  vert.z=d+dStep;
      data.push_back(vert);
      // 2
      vert.u=u+du; vert.v=v+dv; vert.x=w+wStep;  vert.z=d+dStep;
      data.push_back(vert);
      // 3
      vert.u=u; vert.v=v; vert.x=w;  vert.z=d;
      data.push_back(vert);


      /* tri 2 w,0,d
      // counter clock wise
      3_____2
      \    |
      \  |
      \ |
      \|
      1

      */
      vert.u=u+du; vert.v=v+dv;  vert.x=w+wStep;  vert.z=d+dStep;
      data.push_back(vert);
      // 2
      vert.u=u+du; vert.v=v;   vert.x=w+wStep;  vert.z=d;
      data.push_back(vert);
      // 3
      vert.u=u; vert.v=v;  vert.x=w;   vert.z=d;
      data.push_back(vert);
      u+=du;
    } // end w loop
  u=0.0f;
  v+=du;
  } // end d loop
  // now create the VBO
  createVAO(_name,data,GL_TRIANGLES);
}


//----------------------------------------------------------------------------------------------------------------------
void VAOPrimitives::clear() noexcept
{

  std::cerr<<"clearing VAOs\n";

  // loop through the map and delete the VBO's allocated
  // note glDeleteBuffers needs a const GLUint * so we need to de-reference the map object
  for(auto &v : m_createdVAOs)
  {
    //GLuint address=v.second->getID();
    //glDeleteVertexArrays(1,&address);
    v.second->removeVAO();
  }

    m_createdVAOs.erase(m_createdVAOs.begin(),m_createdVAOs.end());
}

AbstractVAO * VAOPrimitives::getVAOFromName(const std::string &_name)
{
  // get an iterator to the VertexArrayObjects
  auto VAO=m_createdVAOs.find(_name);
  // make sure we have a valid shader
  if(VAO!=m_createdVAOs.end())
  {
    return VAO->second;
  }
  else return nullptr;
}

} // end ngl namespace
