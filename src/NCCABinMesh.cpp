/*
  Copyright (C) 2010 Jon Macey

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

#include <cstring>
#include "NCCABinMesh.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file NCCABinMesh.cpp
/// @brief implementation files for NCCABinMesh class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
bool NCCABinMesh::load(const std::string &_fname,bool _calcBB) noexcept
{

  // open a file stream for ip in binary mode
  std::fstream file;
  file.open(_fname.c_str(),std::ios::in | std::ios::binary);
  // see if it worked
  if (!file.is_open())
  {
    std::cerr<<"problems Opening File "<<_fname<<std::endl;
    return false;
  }
  // lets read in the header and see if the file is valid
  char header[9];
  file.read(header,8*sizeof(char));
  header[8]=0; // for strcmp we need \n
  // basically I used the magick string ngl::bin (I presume unique in files!) and
  // we test against it.
  if(strcmp(header,"ngl::bin"))
  {
    // best close the file and exit
    file.close();
    std::cout<<"this is not an ngl::bin file "<<std::endl;
    return false;
  }

  /// The number of vertices in the object
  file.read(reinterpret_cast <char *> (&m_nVerts),sizeof(unsigned long int));
  /// The number of normals in the object
  file.read(reinterpret_cast <char *>(&m_nNorm),sizeof(unsigned long int));
  /// the number of texture co-ordinates in the object
  file.read(reinterpret_cast <char *>(&m_nTex),sizeof(unsigned long int));
  /// the number of faces in the object
  file.read(reinterpret_cast <char *>(&m_nFaces),sizeof(unsigned long int));
  // now the x,y,z for the center could re-calc but why bother
  file.read(reinterpret_cast <char *>(&m_center.m_x),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_center.m_y),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_center.m_z),sizeof(Real));
  // now if texture is active
  file.read(reinterpret_cast <char *>(&m_texture),sizeof(bool));
  // the dimensions of the Bounding box
  file.read(reinterpret_cast <char *>(&m_maxX),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_maxY),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_maxZ),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_minX),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_minY),sizeof(Real));
  file.read(reinterpret_cast <char *>(&m_minZ),sizeof(Real));
  // now how our data is packed for the VBO
  file.read(reinterpret_cast <char *>(&  m_dataPackType),sizeof(GLuint));
  file.read(reinterpret_cast <char *>(&  m_indexSize),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&  m_bufferPackSize),sizeof(unsigned int));
  /// now we read how big the actual vbo data is
  int size;
  file.read(reinterpret_cast <char *>(&size),sizeof(unsigned int));
  // allocate some memory to read into
  Real *vboMem = new Real[size];
  // then read into this buffer
  file.read(reinterpret_cast<char *>(vboMem),size);
  // now we need the index arrays so first find how big
  file.read(reinterpret_cast <char *>(&size),sizeof(unsigned int));
  // now re-size our std::vector so add the data
  m_outIndices.resize(size);
  // then loop and copy the values in from the file.
  for( int i=0; i<size; ++i)
  {
    file.read(reinterpret_cast <char *>(&m_outIndices[i]),sizeof(unsigned int));
  }

  // now were done with the file lets close it

  file.close();
  // and now allocate this as a vbo
  glGenBuffers(1, &m_vboBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboBuffers);

  // resize buffer
  glBufferData(GL_ARRAY_BUFFER, m_indexSize*m_bufferPackSize*sizeof(GLfloat), vboMem, GL_DYNAMIC_DRAW);
  // create the BBox for the obj
  if(_calcBB)
  {
    m_ext=new BBox(m_minX,m_maxX,m_minY,m_maxY,m_minZ,m_maxZ);
  }
  m_vbo=true;
  // delete the vboData
  delete [] vboMem;
  // now return true to indicate success.
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
NCCABinMesh::NCCABinMesh(const std::string& _fname )  noexcept:AbstractMesh()
{
  m_vbo=false;
  m_ext=0;
  m_texture = false;
  load(_fname);
 }

//----------------------------------------------------------------------------------------------------------------------
NCCABinMesh::NCCABinMesh(const std::string& _fname,const std::string& _texName   ) noexcept:AbstractMesh()
{
  m_vbo=false;
  m_ext=0;
  load(_fname);
  // load texture
  loadTexture(_texName);
  m_texture = true;

}

//----------------------------------------------------------------------------------------------------------------------
void NCCABinMesh::save( const std::string& _fname) noexcept
{
  AbstractMesh::saveNCCABinaryMesh(_fname);
}



} //end ngl namespace


