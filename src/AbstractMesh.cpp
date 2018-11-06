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

#include "AbstractMesh.h"
#include "Util.h"
#include <list>
#include "NGLStream.h"
#include "VAOFactory.h"
#include "SimpleVAO.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file AbstractMesh.cpp
/// @brief a series of classes used to define an abstract 3D mesh of Faces, Vertex Normals and TexCords
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
  //----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::drawBBox() const noexcept
{
  m_ext->draw();
}

void AbstractMesh::scale(Real _sx, Real _sy, Real _sz ) noexcept
{
  m_center=0;
  // do lambda here
  for (auto &v : m_verts)
  {
    v.m_x*=_sx;
    v.m_y*=_sy;
    v.m_z*=_sz;
    m_center+=v;
  }
// calculate the center
  m_center/=m_verts.size();
  calcDimensions();
}



//----------------------------------------------------------------------------------------------------------------------
AbstractMesh::~AbstractMesh() noexcept
{
  if(m_loaded == true)
  {
    m_verts.erase(m_verts.begin(),m_verts.end());
    m_norm.erase(m_norm.begin(),m_norm.end());
    m_uv.erase(m_uv.begin(),m_uv.end());
    m_face.erase(m_face.begin(),m_face.end());

    if(m_vbo)
    {
      glDeleteBuffers(1,&m_vboBuffers);
    }
  }
}


//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::loadTexture(const std::string &_fName  ) noexcept
{
  if(m_textureID !=0)
  {
    glDeleteTextures(1,&m_textureID);
  }
	// load in the texture
  Texture t(_fName);
  m_textureID=t.setTextureGL();
  m_texture=true;
}

/// @todo correct the rib exporter and  add Normal information to  the export
/// @verbatim
/// The following code is adapted from an MSc project by
/// Authors: Elaine Kieran, Gavin Harrison, Luke Openshaw
/// Write the obj as a SubdivisionMesh package to the rib file
/// Renderman specification: SubdivisionMesh scheme nverts vertids tags nargs intargs floatargs parameterlist
/// @endverbatim

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::writeToRibSubdiv(RibExport& _ribFile )const noexcept
{
	// Declare the variables
	std::list< int > lVertLink;
	std::list< int >::iterator vertLinkItr;
	std::vector< float > vVerts;
	std::vector< float >::iterator vertsItr;

  // Check if the rib exists
  if( _ribFile.isOpen() != 0 )
  {
    _ribFile.comment( "OBJ AbstractMeshect" );
  // Start printing the SubdivisionPolygons tag to the rib
    _ribFile.getStream() << "SubdivisionMesh \"catmull-clark\" [ ";

		// Loop through all the Polygons
    for (unsigned long  int I=0; I<m_verts.size(); ++I)
		{
		// Print the count of vertices for the current polygon to the rib
		_ribFile.getStream() << m_face[I].m_numVerts << " ";
		// Start building the vertids and parameterlist
		for (unsigned long int i = 0; i < m_face[I].m_numVerts; ++i)
		{
			// Set the verts vector size and testing variables
      size_t iVecSize = vVerts.size();
			bool bTest = false;
			int counter = 0;
			// Loop through the expanding vector checking whether
			// the current vertice exists
      for (unsigned int j = 0; j < iVecSize; j = j + 3)
			{
				// If the vertice if found in the vector, set the test
				// flag and exit the loop. Else keep going.
				if( ( FCompare(m_verts[i].m_x ,vVerts[j]) ) &&
					( FCompare(m_verts[i].m_y,vVerts[j + 1]) ) &&
					( FCompare(m_verts[i].m_y,vVerts[j + 2]) )
					 )
				{
					bTest = true;
					break;
				}
				else
				{
					counter++;
				}
			} //end for

			// Add the vertice to the vector if it is not found
			if( bTest == false )
			{
				vVerts.push_back( m_verts[m_face[I].m_vert[i]].m_x );
				vVerts.push_back( m_verts[m_face[I].m_vert[i]].m_y );
				vVerts.push_back( m_verts[m_face[I].m_vert[i]].m_z );
				lVertLink.push_back( counter );
			}
			else
			{
				lVertLink.push_back( counter );
			}

		}// end outer for

	}// end if

	_ribFile.getStream() << "] [ ";

	// Print the vertids to the rib
	std::list< int >::iterator vertLinkEnd=lVertLink.end();
	for (vertLinkItr = lVertLink.begin(); vertLinkItr != vertLinkEnd; ++vertLinkItr)
	{
		_ribFile.getStream() << *vertLinkItr << " ";
	}

	_ribFile.getStream() << "] [\"interpolateboundary\"] [0 0] [] [] \"P\" [ ";
	// Print the parameterlist to the rib
	std::vector< float >::iterator vVertEnd=vVerts.end();
	for (vertsItr = vVerts.begin(); vertsItr != vVertEnd; ++vertsItr)
	{
		_ribFile.getStream() << *vertsItr << " ";
	}

	// Print new lines to the rib
	_ribFile.getStream() << "]\n\n";
	}

}

//----------------------------------------------------------------------------------------------------------------------
bool AbstractMesh::isTriangular() noexcept
{ 
	for(auto f : m_face)
	{
		if (f.m_numVerts >3)
		{
			return false;
		}
	}
	return true;
}

// a simple structure to hold our vertex data
// had to move this outside the method as g++ complains about it
// clang doesn't have a problem tho
struct VertData
{
  GLfloat x; // position from obj
  GLfloat y;
  GLfloat z;
  GLfloat nx; // normal from obj mesh
  GLfloat ny;
  GLfloat nz;
  GLfloat u; // tex cords
  GLfloat v; // tex cords
};


void AbstractMesh::createVAO() noexcept
{
	// if we have already created a VBO just return.
	if(m_vao == true)
	{
    msg->addWarning("VAO exist so returning");
		return;
	}
// else allocate space as build our VAO
	m_dataPackType=0;
	if(isTriangular())
	{
		m_dataPackType=GL_TRIANGLES;
	}
	// data is mixed of > quad so exit error
	if(m_dataPackType == 0)
	{
    msg->addError("Can only create VBO from all Triangle or ALL Quad data at present");
		exit(EXIT_FAILURE);
	}

  // now we are going to process and pack the mesh into an ngl::VertexArrayObject
  std::vector <VertData> vboMesh;
  VertData d;


	// loop for each of the faces
  for(unsigned int i=0;i<m_face.size();++i)
	{
		// now for each triangle in the face (remember we ensured tri above)
    for(unsigned int j=0;j<3;++j)
		{

			// pack in the vertex data first
			d.x=m_verts[m_face[i].m_vert[j]].m_x;
			d.y=m_verts[m_face[i].m_vert[j]].m_y;
			d.z=m_verts[m_face[i].m_vert[j]].m_z;
			// now if we have norms of tex (possibly could not) pack them as well
      if(m_norm.size() >0 && m_uv.size() > 0)
			{
        d.nx=m_norm[m_face[i].m_norm[j]].m_x;
        d.ny=m_norm[m_face[i].m_norm[j]].m_y;
        d.nz=m_norm[m_face[i].m_norm[j]].m_z;

        d.u=m_uv[m_face[i].m_uv[j]].m_x;
        d.v=m_uv[m_face[i].m_uv[j]].m_y;
      }
      // now if neither are present (only verts like Zbrush models)
      else if(m_norm.size() ==0 && m_uv.size()==0)
      {
        d.nx=0;
        d.ny=0;
        d.nz=0;
        d.u=0;
        d.v=0;
      }
      // here we've got norms but not tex
      else if(m_norm.size() >0 && m_uv.size()==0)
      {
        d.nx=m_norm[m_face[i].m_norm[j]].m_x;
        d.ny=m_norm[m_face[i].m_norm[j]].m_y;
        d.nz=m_norm[m_face[i].m_norm[j]].m_z;
        d.u=0;
        d.v=0;
      }
      // here we've got tex but not norm least common
      else if(m_norm.size() ==0 && m_uv.size()>0)
      {
        d.nx=0;
        d.ny=0;
        d.nz=0;
        d.u=m_uv[m_face[i].m_uv[j]].m_x;
        d.v=m_uv[m_face[i].m_uv[j]].m_y;
      }
    vboMesh.push_back(d);
    }
  }

  // first we grab an instance of our VOA
  m_vaoMesh= ngl::VAOFactory::createVAO(simpleVAO,m_dataPackType);
  // next we bind it so it's active for setting data
  m_vaoMesh->bind();
  m_meshSize=vboMesh.size();

	// now we have our data add it to the VAO, we need to tell the VAO the following
	// how much (in bytes) data we are copying
	// a pointer to the first element of data (in this case the address of the first element of the
	// std::vector
  //m_vaoMesh->setData(m_meshSize*sizeof(VertData),vboMesh[0].u);
  m_vaoMesh->setData(SimpleVAO::VertexData(m_meshSize*sizeof(VertData),vboMesh[0].x));
  // in this case we have packed our data in interleaved format as follows
  // x,y,z,nx,ny,nz,u,v
	// If you look at the shader we have the following attributes being used
	// attribute vec3 inVert; attribute 0
  // attribute vec3 inNormal; attribure 1
  // attribute vec2 inUV; attribute 2
  // so we need to set the vertexAttributePointer so the correct size and type as follows
  m_vaoMesh->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(VertData),0);
	// uv same as above but starts at 0 and is attrib 1 and only u,v so 2
  m_vaoMesh->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(VertData),3);
	// normal same as vertex only starts at position 2 (u,v)-> nx
  m_vaoMesh->setVertexAttributePointer(2,2,GL_FLOAT,sizeof(VertData),6);


	// now we have set the vertex attributes we tell the VAO class how many indices to draw when
	// glDrawArrays is called, in this case we use buffSize (but if we wished less of the sphere to be drawn we could
	// specify less (in steps of 3))
	m_vaoMesh->setNumIndices(m_meshSize);
	// finally we have finished for now so time to unbind the VAO
	m_vaoMesh->unbind();

	// indicate we have a vao now
	m_vao=true;
  m_vbo=true;
  // create a new bbox based on the new object size
  m_ext.reset(new BBox(m_minX,m_maxX,m_minY,m_maxY,m_minZ,m_maxZ));


}

void AbstractMesh::bindVAO() const noexcept
{
  m_vaoMesh->bind();

}

void AbstractMesh::unbindVAO() const noexcept
{
  m_vaoMesh->unbind();
}
//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::draw() const noexcept
{
  if(m_vao == true)
  {
    if(m_texture == true)
    {
      glBindTexture(GL_TEXTURE_2D,m_textureID);
    }
    m_vaoMesh->bind();
    m_vaoMesh->draw();
    m_vaoMesh->unbind();
  }

}


//----------------------------------------------------------------------------------------------------------------------
Real * AbstractMesh::mapVAOVerts() noexcept
{

  Real* ptr=nullptr;

	// bind our VBO data
//
  m_vaoMesh->bind();
  //NGLCheckGLError("Abstract Mesh",__LINE__);
  glBindBuffer(GL_ARRAY_BUFFER, m_vaoMesh->getBufferID(0));
  //NGLCheckGLError("Abstract Mesh",__LINE__);
#ifndef USINGIOS_
  ptr = static_cast<Real *>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
#else
  //ptr = (float*)glMapBufferOES(GL_ARRAY_BUFFER,GL_READ_WRITE_OES);
#endif
  //NGLCheckGLError("Abstract Mesh",__LINE__);
  m_vboMapped=true;
  return ptr;
}

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::unMapVAO() noexcept
{

	if(m_vboMapped==true)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER); // unmap it after use
		m_vboMapped=false;
		m_vaoMesh->unbind();
	}

}
//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::calcDimensions() noexcept
{
  // Calculate the center of the object.
  m_center=0.0;
  for(auto v : m_verts)
  {
    m_center+=v;
  }
  m_center/=m_verts.size();
  // calculate the extents
  m_maxX=m_minX=m_center.m_x;
  m_maxY=m_minY=m_center.m_y;
  m_maxZ=m_minZ=m_center.m_z;

  for(auto v : m_verts)
  {
    if     (v.m_x >m_maxX) { m_maxX=v.m_x; }
    else if(v.m_x <m_minX) { m_minX=v.m_x; }
    if     (v.m_y >m_maxY) { m_maxY=v.m_y; }
    else if(v.m_y <m_minY) { m_minY=v.m_y; }
    if     (v.m_z >m_maxZ) { m_maxZ=v.m_z; }
    else if(v.m_z <m_minZ) { m_minZ=v.m_z; }
  }




}

void AbstractMesh::saveNCCABinaryMesh(const std::string &_fname  ) noexcept
{
// so basically we need to save all the state data from the abstract mesh
// then map the vbo on the gpu and dump that in one go, this means we have to
// call CreateVBO first the Save
  std::fstream file;
  file.open(_fname.data(),std::ios::out | std::ios::binary);
  if (!file.is_open())
  {
    msg->addError(fmt::format("problems Opening File {0} for reading",_fname.data()));
    return;
  }
  // lets write out our own Magic Number file ID
  const std::string header("ngl::bin");
  file.write(header.c_str(),header.length());
  /// The number of vertices in the object
  file.write(reinterpret_cast <char *>(m_verts.size()),sizeof(unsigned long int));
  /// The number of normals in the object
  file.write(reinterpret_cast <char *>(m_norm.size()),sizeof(unsigned long int));

  /// the number of texture co-ordinates in the object
  file.write(reinterpret_cast <char *>(m_uv.size()),sizeof(unsigned long int));

  /// the number of faces in the object
  file.write(reinterpret_cast <char *>(m_face.size()),sizeof(unsigned long int));
  file.write(reinterpret_cast <char *>(&m_center.m_x),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_center.m_y),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_center.m_z),sizeof(Real));

  file.write(reinterpret_cast <char *>(&m_texture),sizeof(bool));

  file.write(reinterpret_cast <char *>(&m_maxX),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_maxY),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_maxZ),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_minX),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_minY),sizeof(Real));
  file.write(reinterpret_cast <char *>(&m_minZ),sizeof(Real));

  file.write(reinterpret_cast <char *>(&  m_dataPackType),sizeof(GLuint));
  file.write(reinterpret_cast <char *>(&  m_indexSize),sizeof(unsigned int));
  file.write(reinterpret_cast <char *>(&  m_bufferPackSize),sizeof(unsigned int));
  /// now we can dump the data from the vbo
  auto size=m_indexSize*m_bufferPackSize*sizeof(GLfloat);
  file.write(reinterpret_cast <char *>(&size),sizeof(unsigned int));


  Real *vboMem=this->mapVAOVerts();
  file.write(reinterpret_cast<char *>(vboMem),size);


  file.close();
  this->unMapVAO();

}

/// modified from example in Rick Parent book
/// Computer Animation Algorithms and Techniques
/// Morgan Korfman Appendix B
void AbstractMesh::calcBoundingSphere() noexcept
{
auto size=m_verts.size();
if( size <=0 )
{
  msg->addError("no vertices loaded ");
	m_sphereCenter=0;
	m_sphereRadius=0;
	return;

}
// find minimal and maximal extents and indexs into
// into vert array
size_t minXI=0; size_t minYI=0; size_t minZI=0;
size_t maxXI=0; size_t maxYI=0; size_t maxZI=0;
Real minX=m_verts[0].m_x; Real maxX=m_verts[0].m_x;
Real minY=m_verts[0].m_y; Real maxY=m_verts[0].m_y;
Real minZ=m_verts[0].m_z; Real maxZ=m_verts[0].m_z;

for(size_t i=0; i<size; ++i)
{
  if(m_verts[i].m_x < minX) { minXI=i; minX=m_verts[i].m_x; }
  if(m_verts[i].m_x > maxX) { maxXI=i; maxX=m_verts[i].m_x; }
  if(m_verts[i].m_y < minY) { minYI=i; minY=m_verts[i].m_y; }
  if(m_verts[i].m_y > maxY) { maxYI=i; maxY=m_verts[i].m_y; }
  if(m_verts[i].m_z < minZ) { minZI=i; minZ=m_verts[i].m_z; }
  if(m_verts[i].m_z > maxZ) { maxZI=i; maxZ=m_verts[i].m_z; }
}
// now we find maximally seperated points from the 3 pairs
// we will use this to initialise the spheres
Real dx=m_verts[minXI].m_x-m_verts[maxXI].m_x;
Real dy=m_verts[minXI].m_y-m_verts[maxXI].m_y;
Real dz=m_verts[minXI].m_z-m_verts[maxXI].m_z;
Real diam2x=dx*dx+dy*dy+dz*dz;

dx=m_verts[minYI].m_x-m_verts[maxYI].m_x;
dy=m_verts[minYI].m_y-m_verts[maxYI].m_y;
dz=m_verts[minYI].m_z-m_verts[maxYI].m_z;
Real diam2y=dx*dx+dy*dy+dz*dz;

dx=m_verts[minZI].m_x-m_verts[maxZI].m_x;
dy=m_verts[minZI].m_y-m_verts[maxZI].m_y;
dz=m_verts[minZI].m_z-m_verts[maxZI].m_z;
Real diam2z=dx*dx+dy*dy+dz*dz;

Real diamTwo=diam2x;
int p1i=minXI;
int p2i=maxXI;
if(diam2y>diamTwo){ diamTwo=diam2y; p1i=minYI; p2i=maxYI;}
if(diam2z>diamTwo){ diamTwo=diam2z; p1i=minZI; p2i=maxZI;}
// now we can get the center of the sphere as the average
// of the two points
m_sphereCenter=(m_verts[p1i]+m_verts[p2i])/2.0;
// now calculate radius and radius^2 of the initial sphere
Real radTwo=diamTwo/4.0;
Real rad=sqrt(radTwo);
// now check and adjust for outlying points
Vec3 newCenter;
Real newRad2;
Real newRad;
Real dist2;
Real dist;
Real delta;

for (auto v : m_verts)
{
  dx=v.m_x-m_sphereCenter.m_x;
  dy=v.m_y-m_sphereCenter.m_y;
  dz=v.m_z-m_sphereCenter.m_z;
  // distance squared of old center to current point
  dist2=dx*dx+dy*dy+dz*dz;
  // need to update the sphere if this point is outside the radius
  if(dist2 > radTwo)
  {
    dist=sqrt(dist2);
    newRad=(rad+dist)/2.0;
    newRad2=newRad*newRad;
    delta=dist-newRad;
    // now compute new center using the weights above
    newCenter.m_x=(newRad*m_sphereCenter.m_x+delta*v.m_x)/dist;
    newCenter.m_y=(newRad*m_sphereCenter.m_y+delta*v.m_y)/dist;
    newCenter.m_z=(newRad*m_sphereCenter.m_z+delta*v.m_z)/dist;
    // now test to see if we have a fit
    dx=v.m_x-newCenter.m_x;
    dy=v.m_y-newCenter.m_y;
    dz=v.m_z-newCenter.m_z;
    dist2=dx*dx+dy*dy+dz*dz;
    if(dist2 > newRad2)
    {
      msg->addWarning(fmt::format("something wrong here error margin {0}",dist2-newRad2));
    }
    m_sphereCenter=newCenter;
    rad=newRad;
    radTwo=rad*rad;
  } // end if dist2>rad2
  m_sphereRadius=rad;

}

m_sphereRadius=rad;
}
/// end of citation


} //end ngl namespace


