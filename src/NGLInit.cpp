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
#include "NGLInit.h"
#include "ShaderLib.h"
#include "VAOPrimitives.h"

#if defined(LINUX) || defined(WIN32)
  #include <cstdlib>
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLInit.cpp
/// @brief implementation files for NGLInit class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------


NGLInit::NGLInit()
{
  // set this first so that new driver features are included.
  glewExperimental = true;
  // now init glew
  GLenum err = glewInit();
  // error check
  if (GLEW_OK != err)
  {
    std::cerr<<"Error: "<<glewGetErrorString(err)<<"\n";
  }
  // now see if NGL can run in this environment
  std::cout<<"Using GLEW "<<glewGetString(GLEW_VERSION)<<"\n";
  if(!glewIsSupported("GL_VERSION_3_2") )
  {
    std::cerr<<"To run these demos you need a modern OpenGL Version\n";
    std::cerr<<"The lowest level OpenGL we support is 3.2\n";
    std::cerr<<"It could be you don't have the correct drivers installed\n";
    std::cerr<<"Or if linux on a laptop it could be using the intel driver and not the GPU\n";
    std::cerr<<"for more info contact Jon\n";

	}
	int majorVersion,minorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	#ifdef NGL_DEBUG
		std::cerr <<"ngl:: configured with GL version "<<majorVersion<<"."<<minorVersion<<"\n";
	#endif


}

//----------------------------------------------------------------------------------------------------------------------
NGLInit::~NGLInit()
{
}

void NGLInit::NGLQuit()
{
//  VAOPrimitives *prim=VAOPrimitives::instance();
//  prim->clear();
//  ShaderLib *shader=ShaderLib::instance();
//  shader->reset();

}
} // end of ngl namespace




