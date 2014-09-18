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
#include "HoudiniGeo.h"
#include <boost/lexical_cast.hpp>
//----------------------------------------------------------------------------------------------------------------------
/// @file HoudiniGeo.cpp
/// @brief implementation files for HoudiniGeo class
//----------------------------------------------------------------------------------------------------------------------

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
bool HoudiniGeo::load(
                      const std::string& _fName,
                      bool _calcBB
                     )
{
  // Open the stream and parse
  std::ifstream fileIn;
  fileIn.open(_fName.c_str());
  if (!fileIn.is_open())
  {
    std::cout <<"File : "<<_fName<<" Not founds "<<std::endl;
    return false;
  }
// first we check the header to see if we have a valid file
// if only OBJ's did this!!

  loadHeader(fileIn);
  // check to see if we need to load any attribs
  if(m_nPointAttrib !=0)
  {
    loadPointAttribDictionary(fileIn);
  }
  loadPoints(fileIn);
  // set the center and BBox
  this->calcDimensions();

  fileIn.close();
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
HoudiniGeo::HoudiniGeo(
                       const std::string& _fName
                      )
{
m_vbo=0;
m_loaded=load(_fName);
}

//----------------------------------------------------------------------------------------------------------------------
HoudiniGeo::HoudiniGeo(
                       const std::string& _fName,
                       const std::string& _texName
                      )
{
m_vbo=0;
m_loaded=load(_fName);
loadTexture(_texName);

}

//----------------------------------------------------------------------------------------------------------------------
/// Load in the header as specified here
/// Magic Number: PGEOMETRY
/// Point/Prim Counts: NPoints # NPrims #
/// Group Counts: NPointGroups # NPrimGroups #
/// Attribute Counts: NPointAttrib # NVertexAttrib # NPrimAttrib # NAttrib #
/// each of these cases, the # represents the number of the element described
bool HoudiniGeo::loadHeader(
                            std::ifstream& _stream
                           )
{
  // set the token index to large value so we can check if they are set
  m_normalTokenIndex=0xffff;
  m_uvTokenIndex=0x0ffff;
  std::string lineBuffer;
  // first check if valid
  getline(_stream,lineBuffer,'\n');
  // now tokenize the line
  boost::char_separator<char> sep(" \t\r\n");
  tokenizer tokens(lineBuffer, sep);
  if(*tokens.begin() != "PGEOMETRY")
  {
    std::cerr<<"Not a valid Houdini geo file first line should be PGEOMETRY version"<<std::endl;
    return false;
  }
  // load in the number of points and prims
  getline(_stream,lineBuffer,'\n');
  tokenizer pointPrimTokens(lineBuffer,sep);
  // ok we will take some liberties here and assume that the file is not corrupted
  // as this is really a dirty pipeline tool and not a solid parser
  // Point/Prim Counts: NPoints # NPrims #
  // first skip the NPoints
  tokenizer::iterator  firstWord = pointPrimTokens.begin();
  ++firstWord;
  // now we have the num points
  m_nVerts=boost::lexical_cast<int>(*firstWord);
  // now the prims
  ++firstWord;
  // skip the NPrims token
  ++firstWord;

  // now we have the num points
  m_nFaces =boost::lexical_cast<int>(*firstWord);
  std::cerr<<"num points "<<m_nVerts<<" prims "<<m_nFaces<<std::endl;
  m_verts.resize(m_nVerts);
  m_face.resize(m_nFaces);

  // skip the next line as we don't support it
   getline(_stream,lineBuffer,'\n');
  // now we need to read the rest of the header and find what attribs if any are attached
  // to the Points and the vertex values
  // At present we are only interested in the Texture and Normal attribs as that is all that
  // is supported in the AbstractBase class
   getline(_stream,lineBuffer,'\n');
   tokenizer attribTokens(lineBuffer,sep);
   // the basic format is as follows NPointAttrib 1 NVertexAttrib 1 NPrimAttrib 0 NAttrib 0
    // first skip the NPointAttrib
  std::cerr<<lineBuffer<<std::endl;
  firstWord = attribTokens.begin();
  ++firstWord;
  // now we have the num points
   m_nPointAttrib=boost::lexical_cast<int>(*firstWord);
  // now the prims
  ++firstWord;
  // skip the NPrims token
  ++firstWord;
  m_nVertAttrib=boost::lexical_cast<int>(*firstWord);
  std::cerr<<"points Attrib "<<m_nPointAttrib<<" Vert Attrib  "<<m_nVertAttrib<<std::endl;
  std::cerr<<"Finished Reading Header"<<std::endl;
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
void HoudiniGeo::loadPoints(
                            std::ifstream& _stream
                           )
{
    /// now we can actually load the Point data into our vert structure
    /// it is going to be formatted in the following way depending upon our dictionary
    /// PointAttrib
    /// Cd 3 float 0 0 0 # Color attrib., 3 floats, default 0 0 0
    /// Alpha 1 float 1 # Alpha attribute, 1 float, default 1
    /// N 3 float 0 0 0 # Normal attribute
    /// uv 2 float 0 0 # Texture coordinate

    /// The data for the point might look like:

    /// 0 0 0 1 (1 0 0 1 0 0 1 .5 .5)
    /// ^^^^^^^ ^^^^^^^^^^^^^^^^^^^^^^^ Position Attributes

    /// The point would have:

    /// Cd = (1, 0, 0)
    /// Alpha = 1
    /// N = (0 0 1)
    /// uv = (.5, .5)
    /// we already know how many points to load and we have re-sized the data to fit so should
    /// the first 4 values are the homogeneous point values
    boost::char_separator<char> sep(" \t\r\n()");
    tokenizer::iterator  firstWord;
    tokenizer::iterator  lastWord;

    std::string lineBuffer;
    for (unsigned int i=0; i<m_nVerts; ++i)
    {
      getline(_stream,lineBuffer,'\n');
      //std::cerr<<lineBuffer<<std::endl;
      tokenizer pointTokens(lineBuffer,sep);
      firstWord=pointTokens.begin();
      lastWord=pointTokens.end();
      // grab the point data
      float x=boost::lexical_cast<float>(*firstWord++);
      float y=boost::lexical_cast<float>(*firstWord++);
      float z=boost::lexical_cast<float>(*firstWord++);
      float w=boost::lexical_cast<float>(*firstWord++);
      m_verts[i].set(x,y,z,w);
      // now we see if we have any other data to load and grab that as well.
      // this can be difficult as we can have either vert data or prim data in the
      // file lets just grab all the data and put it into a vector to make indexing
      // easier
      std::vector <float> values;
      while(firstWord !=lastWord)
      {
        values.push_back(boost::lexical_cast<float>(*firstWord++));
      }
      // now lets load the normals if they exist
      //if()
      {

      }
    }
  }



//----------------------------------------------------------------------------------------------------------------------
void HoudiniGeo::loadPointAttribDictionary(
                                           std::ifstream& _stream
                                          )
{
  std::string lineBuffer;
  std::cerr<<"Loading Attrib Dictionary num attribs"<< m_nPointAttrib<<std::endl;
  getline(_stream,lineBuffer,'\n');
  // the first line of this dictionary should be PointAttrib so check and bomb if wrong
  if(lineBuffer != "PointAttrib")
  {
    std::cerr<< "file not in correct format line should read PointAttrib\n";
    return;
  }
  // our seperator for the tokens including () for the attribs
  boost::char_separator<char> sep(" \t\r\n");
  tokenizer::iterator  firstWord;
  tokenizer::iterator  sizeToken;

  int relIndex=0;
  for(int i=0; i<m_nPointAttrib; ++i)
  {
    getline(_stream,lineBuffer,'\n');
    std::cerr<<"Found "<<lineBuffer<<std::endl;
    tokenizer attribTokens(lineBuffer,sep);
    // first we are going to grab the 2nd element of the dictionary so we can see
    // what size the token is, we then use it to get the relative offset (begining) of
    // the data in the line for the point attrib parsing
    sizeToken=attribTokens.begin();
    ++sizeToken;
    int size=boost::lexical_cast<int>(*sizeToken);
    // relIndex tells us which attribute is the one we want, we basically inc this everytime
    // we find an attrib and if it's one we want we know.
    // imagine we have Cd Alpha N uv then N == 2 uv == 3 so we know we can skip the others
    relIndex++;
    std::cerr<<"relIndex "<<relIndex<<std::endl;
    firstWord=attribTokens.begin();

    // see if we have a normal
    if(*firstWord == "N")
    {
      // increment sizeToken to get the data type
      ++sizeToken;
      m_dictionary["N"]= new HouDictionaryEntry("N",size,*sizeToken,relIndex);
      m_dictionary["N"]->print();

    }
    else if(*firstWord =="uv")
    {
      ++sizeToken;
      m_dictionary["uv"]= new HouDictionaryEntry("uv",size,*sizeToken,relIndex);
      m_dictionary["uv"]->print();

    }

  }

}
//----------------------------------------------------------------------------------------------------------------------
void HoudiniGeo::drawDebugPoints(void)
{
	/// @todo write GL3.x code to do this
#warning add new code to do this
  /*
	glBegin(GL_POINTS);
  glPointSize(4);
  for(unsigned int i=0; i<m_nVerts; ++i)
  {
    m_verts[i].vertex();

  }
  glEnd();
*/
}
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

} // end of ngl namespace
