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
#include "VAOFactory.h"
#include "SimpleVAO.h"
#include "MultiBufferVAO.h"
#include "SimpleIndexVAO.h"

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
#ifndef USINGIOS_

  if (gl3wInit())
  {
     std::cerr<<"failed to initialize OpenGL\n";
     exit(EXIT_FAILURE);
  }
  if (!gl3wIsSupported(3, 2))
  {
    std::cerr<<"To run these demos you need a modern OpenGL Version\n";
    std::cerr<<"The lowest level OpenGL we support is 3.2\n";
    std::cerr<<"It could be you don't have the correct drivers installed\n";
    std::cerr<<"Or if linux on a laptop it could be using the intel driver and not the GPU\n";
    std::cerr<<"for more info contact Jon\n";
    exit(EXIT_FAILURE);
  }
  std::cerr<<"NGL configured with \n";
  std::cerr<<"OpenGL " << glGetString(GL_VERSION);
  std::cerr<<" GLSL version "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<'\n';


  VAOFactory::registerVAOCreator(simpleVAO,SimpleVAO::create);
  VAOFactory::registerVAOCreator(multiBufferVAO,MultiBufferVAO::create);
  VAOFactory::registerVAOCreator(simpleIndexVAO,SimpleIndexVAO::create);
#endif
}

//----------------------------------------------------------------------------------------------------------------------
NGLInit::~NGLInit()
{
}


} // end of ngl namespace




