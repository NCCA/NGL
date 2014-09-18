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

#include "NCCAPointBake.h"
#include "rapidxml/rapidxml.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <cstring>
//----------------------------------------------------------------------------------------------------------------------
/// @file NCCAPointBake.cpp
/// @brief implementation files for NCCAPointBake class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

//----------------------------------------------------------------------------------------------------------------------
NCCAPointBake::NCCAPointBake()
{
	m_numFrames=0;
	m_currFrame=0;
	m_nVerts=0;
	m_startFrame=0;
	m_endFrame=0;
	m_mesh=0;
	m_binFile=false;
}

bool NCCAPointBake::loadPointBake(const std::string &_fileName  )
{
	m_numFrames=0;
	m_currFrame=0;
	m_nVerts=0;
	m_startFrame=0;
	m_endFrame=0;
	m_mesh=0;
	m_binFile=false;
	rapidxml::xml_node<> * rootNode;
	// Read the xml file into a vector
	std::ifstream xmlFile (_fileName.c_str() );
	if(!xmlFile.is_open())
	{
		std::cerr<<"Could not open file\n";
		return false;
	}
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	rapidxml::xml_document<> doc;

	doc.parse<rapidxml::parse_trim_whitespace>(&buffer[0]);
	rootNode=doc.first_node();
	if(rootNode->name() !=std::string("NCCAPointBake"))
	{
		std::cerr<<"this is not a pointbake file \n";
		return false;
	}

  rapidxml::xml_node<> * child=rootNode->first_node("MeshName");
  m_meshName=child->value();
  std::cerr<<"found mesh "<<m_meshName<<"\n";


  child=rootNode->first_node("NumVerts");
  m_nVerts=boost::lexical_cast< int>(child->value());
  std::cerr<<"NumVerts "<<m_nVerts<<"\n";
  child=rootNode->first_node("StartFrame");
  m_startFrame=boost::lexical_cast< int>(child->value());
  std::cerr<<"StartFrame"<<m_startFrame<<"\n";
  child=rootNode->first_node("EndFrame");
  m_endFrame=boost::lexical_cast< int>(child->value());
  std::cerr<<"EndFrame"<<m_endFrame<<"\n";
  child=rootNode->first_node("NumFrames");
  m_numFrames=boost::lexical_cast< int>(child->value());
  std::cerr<<"EndFrame  "<<m_numFrames<<"\n";
  //first allocate base pointer [vertex]
  m_data.resize(m_numFrames);
  //cout <<"Size is now"<<m_data.size()<<endl;
  //now for each of these we need to allocate more space
  for(unsigned int i=0; i<m_numFrames; ++i)
  {
    m_data[i].resize(m_nVerts);
  }
  unsigned int CurrentFrame=0;
  // this is the line we wish to parse
  std::string lineBuffer;
  // say which separators should be used in this
  // case Spaces, Tabs and return \ new line
  boost::char_separator<char> sep(" \t\r\n");
  // now traverse each frame and grab the data
  for(child=rootNode->first_node("Frame"); child; child=child->next_sibling())
  {
    std::cerr<<"doing frame "<<child->first_attribute("number")->value()<<"\n";
    CurrentFrame=boost::lexical_cast< int>(child->first_attribute("number")->value());
    CurrentFrame-=m_startFrame;
    std::flush(std::cerr);

    for(rapidxml::xml_node<> * vertex=child->first_node("Vertex"); vertex; vertex=vertex->next_sibling())
    {
      int index=boost::lexical_cast< int>(vertex->first_attribute("number")->value());
      lineBuffer=vertex->value();
      tokenizer tokens(lineBuffer, sep);
      tokenizer::iterator  firstWord = tokens.begin();
      Real x=boost::lexical_cast<Real>(*firstWord++);
      Real y=boost::lexical_cast<Real>(*firstWord++);
      Real z=boost::lexical_cast<Real>(*firstWord++);
      m_data[CurrentFrame][index].set(x,y,z);

    }

  }
  return true;
}




//----------------------------------------------------------------------------------------------------------------------
NCCAPointBake::~NCCAPointBake()
{

}
//----------------------------------------------------------------------------------------------------------------------
NCCAPointBake::NCCAPointBake( const std::string &_fileName )
{

  loadPointBake(_fileName);
}
//----------------------------------------------------------------------------------------------------------------------
void NCCAPointBake::setFrame( const unsigned int _frame  )
{
 m_currFrame=_frame;
}

bool NCCAPointBake::loadBinaryPointBake( const std::string &_fileName )
{
  // open a file stream for ip in binary mode
  std::fstream file;
  file.open(_fileName.c_str(),std::ios::in | std::ios::binary);
  // see if it worked
  if (!file.is_open())
  {
    std::cerr<<"problems Opening File "<<_fileName<<std::endl;
    return false;
  }
  // lets read in the header and see if the file is valid
  char header[11];
  file.read(header,10*sizeof(char));
  header[10]=0; // for strcmp we need \n
  // basically I used the magick string ngl::bin (I presume unique in files!) and
  // we test against it.
  if(strcmp(header,"ngl::binpb"))
  {
    // best close the file and exit
    file.close();
    std::cout<<"this is not an ngl::binpb file "<<std::endl;
    return false;
  }

  /// The number of vertices in the object
  //file.read(reinterpret_cast <char *> (&m_nVerts),sizeof(unsigned long int));

  file.read(reinterpret_cast <char *>(&m_numFrames),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_currFrame),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_nVerts),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_startFrame),sizeof(unsigned int));
  file.read(reinterpret_cast <char *>(&m_binFile),sizeof(bool));
  std::cout <<"Loaded header\n";
  std::cout<<m_numFrames<<"\n";
  std::cout<<m_currFrame<<"\n";
  std::cout<<m_nVerts<<"\n";
  std::cout<<m_startFrame<<"\n";
  std::cout<<m_binFile<<"\n";

  m_data.resize(m_numFrames);
  for(unsigned int frame =0; frame<m_numFrames; ++frame)
  {
    m_data[frame].resize(m_nVerts);
    for(unsigned int v=0; v< m_nVerts; ++v)
    {
     file.read( reinterpret_cast <char *>(&m_data[frame][v].m_x),sizeof(Real));
     file.read( reinterpret_cast <char *>(&m_data[frame][v].m_y),sizeof(Real));
     file.read( reinterpret_cast <char *>(&m_data[frame][v].m_z),sizeof(Real));
   }
  }
  std::cout<<"done m_data\n";



  std::cout<<"finished\n";
  return true;
}






bool NCCAPointBake::saveBinaryPointBake( const std::string &_fileName )
{
  // so basically we need to save all the state data from the abstract mesh
  // then map the vbo on the gpu and dump that in one go, this means we have to
  // call CreateVBO first the Save
    std::fstream file;
    file.open(_fileName.c_str(),std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
      std::cerr<<"problems Opening File "<<_fileName<<std::endl;
      return false;
    }

    // lets write out our own Magic Number file ID
    const std::string header("ngl::binpb");
    file.write(header.c_str(),header.length());
    m_binFile=true;
    file.write(reinterpret_cast <char *>(&m_numFrames),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_currFrame),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_nVerts),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_startFrame),sizeof(unsigned int));
    file.write(reinterpret_cast <char *>(&m_binFile),sizeof(bool));
    std::cout<<m_numFrames<<"\n";
    std::cout<<m_currFrame<<"\n";
    std::cout<<m_nVerts<<"\n";
    std::cout<<m_startFrame<<"\n";
    std::cout<<m_binFile<<"\n";

    // now write out data
    for(unsigned int frame =0; frame<m_numFrames; ++frame)
    {
      for(unsigned int v=0; v< m_nVerts; ++v)
      {
       file.write( reinterpret_cast <char *>(&m_data[frame][v].m_x),sizeof(Real));
       file.write( reinterpret_cast <char *>(&m_data[frame][v].m_y),sizeof(Real));
       file.write( reinterpret_cast <char *>(&m_data[frame][v].m_z),sizeof(Real));
     }
    }

    file.close();
    return true;
}

void NCCAPointBake::setMeshToFrame(  const unsigned int _frame  )
  {
    // map the m_obj's vbo dat
    Real *ptr=m_mesh->mapVAOVerts();
    std::vector <Face> faces=m_mesh->getFaceList();
    unsigned int nFaces=faces.size();
    // loop for each of the faces
    unsigned int step=0;
    for(unsigned int i=0;i<nFaces;++i)
    {
      // now for each triangle in the face (remember we ensured tri above)
      // loop for all the verts and set the new vert value
      // the data is packed uv, nx,ny,nz then x,y,z
      // as we only want to change x,y,z, we need to skip over
      // stuff

      for(int j=0;j<3;++j)
      {
        ptr[step+5]=m_data[_frame][faces[i].m_vert[j]].m_x;
        ptr[step+6]=m_data[_frame][faces[i].m_vert[j]].m_y;
        ptr[step+7]=m_data[_frame][faces[i].m_vert[j]].m_z;
        step+=8;
      }

    }

    // unmap the vbo as we have finished updating
    m_mesh->unMapVAO();
    m_currFrame=_frame;
 }




//----------------------------------------------------------------------------------------------------------------------
bool NCCAPointBake::attachMesh(AbstractMesh *_mesh)
{
  std::cout<<"doing attach mesh\n";
  if(_mesh->m_nVerts != m_nVerts)
  {
    std::cerr <<" Mesh can't be attached to this data as vert count does not match\n";
    std::cerr<<"mesh verts "<<_mesh->m_nVerts<<" file verts "<<m_nVerts<<"\n";
    return false;
  }

  else
  {
    m_mesh=_mesh;
    return true;
  }

}


//----------------------------------------------------------------------------------------------------------------------
std::vector<Vec3> & NCCAPointBake::getRawDataPointerAtFrame(unsigned int _f)
{
	NGL_ASSERT(_f<=m_numFrames);
	return m_data[_f];

}



} // end ngl namespace
//----------------------------------------------------------------------------------------------------------------------
