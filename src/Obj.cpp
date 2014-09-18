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
#include "boost/bind.hpp"

#include "boost/spirit.hpp"
/// @todo re-write this at some stage to use boost::spirit::qi

#include <boost/foreach.hpp>
#include "Obj.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file Obj.cpp
/// @brief implementation files for Obj class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{

// make a namespace for our parser to save writing boost::spirit:: all the time
namespace spt=boost::spirit;

// syntactic sugar for specifying our grammar
typedef spt::rule<spt::phrase_scanner_t> srule;


//----------------------------------------------------------------------------------------------------------------------
// parse a vertex
void Obj::parseVertex( const char *_begin )
{
  std::vector<Real> values;
  // here is the parse rule to load the data into a vector (above)
  srule vertex = "v" >> spt::real_p[spt::append(values)] >>
                        spt::real_p[spt::append(values)] >>
                        spt::real_p[spt::append(values)];
  // now parse the data
  spt::parse_info<> result = spt::parse(_begin, vertex, spt::space_p);
  // should check this at some stage
  NGL_UNUSED(result);
  // and add it to our vert list in abstact mesh parent
  m_verts.push_back(Vec3(values[0],values[1],values[2]));
}


//----------------------------------------------------------------------------------------------------------------------
// parse a texture coordinate
void Obj::parseTextureCoordinate(const char * _begin )
{
  std::vector<Real> values;
  // generate our parse rule for a tex cord,
  // this can be either a 2 or 3 d text so the *rule looks for an additional one
  srule texcord = "vt" >> spt::real_p[spt::append(values)] >>
                          spt::real_p[spt::append(values)] >>
                          *(spt::real_p[spt::append(values)]);
  spt::parse_info<> result = spt::parse(_begin, texcord, spt::space_p);
  // should check the return values at some stage
  NGL_UNUSED(result);

  // build tex cord
  // if we have a value use it other wise set to 0
  Real vt3 = values.size() == 3 ? values[2] : 0.0f;
  m_tex.push_back(Vec3(values[0],values[1],vt3));
}

//----------------------------------------------------------------------------------------------------------------------
// parse a normal
void Obj::parseNormal( const char *_begin )
{
  std::vector<Real> values;
  // here is our rule for normals
  srule norm = "vn" >> spt::real_p[spt::append(values)] >>
                       spt::real_p[spt::append(values)] >>
                       spt::real_p[spt::append(values)];
  // parse and push back to the list
  spt::parse_info<> result = spt::parse(_begin, norm, spt::space_p);
  // should check the return values at some stage
  NGL_UNUSED(result);
  m_norm.push_back(Vec3(values[0],values[1],values[2]));
}

//----------------------------------------------------------------------------------------------------------------------
// parse face
void Obj::parseFace(const char * _begin   )
{
  // ok this one is quite complex first create some lists for our face data
  // list to hold the vertex data indices
  std::vector<int> vec;
  // list to hold the tex cord indices
  std::vector<int> tvec;
  // list to hold the normal indices
  std::vector<int> nvec;

  // create the parse rule for a face entry V/T/N
  // so our entry can be always a vert, followed by optional t and norm seperated by /
  // also it is possible to have just a V value with no / so the rule should do all this
  srule entry = spt::int_p[spt::append(vec)] >>
    (
      ("/" >> (spt::int_p[spt::append(tvec)] | spt::epsilon_p) >>
       "/" >> (spt::int_p[spt::append(nvec)] | spt::epsilon_p)
      )
      | spt::epsilon_p
    );
  // a face has at least 3 of the above entries plus many optional ones
  srule face = "f"  >> entry >> entry >> entry >> *(entry);
  // now we've done this we can parse
 spt::parse(_begin, face, spt::space_p);

  int numVerts=vec.size();
  // so now build a face structure.
  Face f;
  // verts are -1 the size
  f.m_numVerts=numVerts-1;
  f.m_textureCoord=false;
  f.m_normals=false;
  // copy the vertex indices into our face data structure index in obj start from 1
  // so we need to do -1 for our array index
  BOOST_FOREACH(int i, vec)
  {
    f.m_vert.push_back(i-1);
  }

  // merge in texture coordinates and normals, if present
  // OBJ format requires an encoding for faces which uses one of the vertex/texture/normal specifications
  // consistently across the entire face.  eg. we can have all v/vt/vn, or all v//vn, or all v, but not
  // v//vn then v/vt/vn ...
  if(!nvec.empty())
  {
    if(nvec.size() != vec.size())
    {
     std::cerr <<"Something wrong with the face data will continue but may not be correct\n";
    }

    // copy in these references to normal vectors to the mesh's normal vector
    BOOST_FOREACH(int i, nvec)
    {
      f.m_norm.push_back(i-1);
    }
    f.m_normals=true;

  }

  //
  // merge in texture coordinates, if present
  //
  if(!tvec.empty())
  {
    if(tvec.size() != vec.size())
    {
     std::cerr <<"Something wrong with the face data will continue but may not be correct\n";
    }

    // copy in these references to normal vectors to the mesh's normal vector
    BOOST_FOREACH(int i, tvec)
    {
      f.m_tex.push_back(i-1);
    }

    f.m_textureCoord=true;

  }
// finally save the face into our face list
  m_face.push_back(f);
}

//----------------------------------------------------------------------------------------------------------------------
bool Obj::load(const std::string &_fname,bool _calcBB )
{
 // here we build up our ebnf rules for parsing
  // so first we have a comment
  srule comment = spt::comment_p("#");

  // see below for the rest of the obj spec and other good format data
  // http://local.wasp.uwa.edu.au/~pbourke/dataformats/obj/

  // vertices rule v is a parse of 3 reals and we run the parseVertex function
  srule vertex= ("v"  >> spt::real_p >> spt::real_p >> spt::real_p) [bind(&Obj::parseVertex,boost::ref(*this), _1)];
  /// our tex rule and binding of the parse function
  srule tex= ("vt" >> spt::real_p >> spt::real_p) [bind(&Obj::parseTextureCoordinate, boost::ref(*this), _1)];
  // the normal rule and parsing function
  srule norm= ("vn" >> spt::real_p >> spt::real_p >> spt::real_p) [bind(&Obj::parseNormal,boost::ref(*this), _1)];

  // our vertex data can be any of the above values
  srule vertex_type = vertex | tex | norm;

  // the rule for the face and parser
  srule  face = (spt::ch_p('f') >> *(spt::anychar_p))[bind(&Obj::parseFace, boost::ref(*this), _1)];
  // open the file to parse
  std::ifstream in(_fname.c_str());
  if (in.is_open() != true)
  {
    std::cout<<"FILE NOT FOUND !!!! "<<_fname.c_str()<<"\n";
    return false;

  }
  std::string str;
  // loop grabbing a line and then pass it to our parsing framework
  while(getline(in, str))
  {
    spt::parse(str.c_str(), vertex_type  | face | comment, spt::space_p);
  }
  // now we are done close the file
  in.close();

  // grab the sizes used for drawing later
  m_nVerts=m_verts.size();
  m_nNorm=m_norm.size();
  m_nTex=m_tex.size();
  m_nFaces=m_face.size();


  // Calculate the center of the object.
  if(_calcBB == true)
  {
    this->calcDimensions();
  }
  return true;

//	fileIn.close(); // close the file.
}

//----------------------------------------------------------------------------------------------------------------------
Obj::Obj( const std::string& _fname  ) :AbstractMesh()
{
    m_vbo=false;
    m_ext=0;
    // set default values
    m_nVerts=m_nNorm=m_nTex=m_nFaces=0;
    //set the default extents to 0
    m_maxX=0.0f; m_maxY=0.0f; m_maxZ=0.0f;
    m_minX=0.0f; m_minY=0.0f; m_minZ=0.0f;
    m_nNorm=m_nTex=0;

    // load the file in
    m_loaded=load(_fname);

    m_texture = false;
}

//----------------------------------------------------------------------------------------------------------------------
Obj::Obj( const std::string& _fname,const std::string& _texName   ):AbstractMesh()
{
    m_vbo=false;
    m_vao=false;
    m_ext=0;
    // set default values
    m_nVerts=m_nNorm=m_nTex=m_nFaces=0;
    //set the default extents to 0
    m_maxX=0.0f; m_maxY=0.0f; m_maxZ=0.0f;
    m_minX=0.0f; m_minY=0.0f; m_minZ=0.0f;
    m_nNorm=m_nTex=0;
    // load the file in
    m_loaded=load(_fname);

    // load texture
    loadTexture(_texName);
    m_texture = true;
}

//----------------------------------------------------------------------------------------------------------------------
void Obj::save(const std::string& _fname)const
{
  // Open the stream and parse
  std::fstream fileOut;
  fileOut.open(_fname.c_str(),std::ios::out);
  if (!fileOut.is_open())
  {
    std::cout <<"File : "<<_fname<<" Not founds "<<std::endl;
    return;
  }
  // write out some comments
  fileOut<<"# This file was created by ngl Obj exporter "<<_fname.c_str()<<std::endl;
  // was c++ 11  for(Vec3 v : m_norm) for all of these
  // write out the verts
  BOOST_FOREACH(Vec3 v , m_verts)
  {
    fileOut<<"v "<<v.m_x<<" "<<v.m_y<<" "<<v.m_z<<std::endl;
  }

  // write out the tex cords
  BOOST_FOREACH(Vec3 v , m_tex)
  {
    fileOut<<"vt "<<v.m_x<<" "<<v.m_y<<std::endl;
  }
  // write out the normals

  BOOST_FOREACH(Vec3 v , m_norm)
  {
    fileOut<<"vn "<<v.m_x<<" "<<v.m_y<<" "<<v.m_z<<std::endl;
  }

  // finally the faces
  BOOST_FOREACH(Face f , m_face)
  {
  fileOut<<"f ";
  // we now have V/T/N for each to write out
  for(unsigned int i=0; i<=f.m_numVerts; ++i)
  {
    // don't forget that obj indices start from 1 not 0 (i did originally !)
    fileOut<<f.m_vert[i]+1;
    fileOut<<"/";
    fileOut<<f.m_tex[i]+1;
    fileOut<<"/";

    fileOut<<f.m_norm[i]+1;
    fileOut<<" ";
  }
  fileOut<<std::endl;
  }
}

} //end ngl namespace
//----------------------------------------------------------------------------------------------------------------------



