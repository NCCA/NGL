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
#include "MultiBufferVAO.h"
#include "ShaderLib.h"
#include "SimpleIndexVAO.h"
#include "SimpleVAO.h"
#include "VAOFactory.h"
#include "VAOPrimitives.h"
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#if defined(LINUX) || defined(_WIN32)
#include <cstdlib>
#endif
/// @file NGLInit.cpp
/// @brief implementation files for NGLInit class

namespace ngl
{

void NGLInit::initialize()
{
  NGLMessage::init();

#if defined(USINGIOS_) || !defined(__APPLE__)
  if(gl3wInit())
  {
    NGLMessage::drawLine(Colours::RED);
    NGLMessage::addError("failed to initialize OpenGL");
    NGLMessage::drawLine(Colours::RED);
    exit(EXIT_FAILURE);
  }
  if(!gl3wIsSupported(4, 1))
  {
    NGLMessage::drawLine(Colours::RED);
    NGLMessage::addError("To run these demos you need a modern OpenGL Version");
    NGLMessage::addError("The lowest level OpenGL we support is 4.1");
    NGLMessage::addError("It could be you don't have the correct drivers installed");
    NGLMessage::addError("Or if linux on a laptop it could be using the intel driver and not the GPU");
    NGLMessage::addError("for more info contact Jon");
    NGLMessage::drawLine(Colours::RED);
    exit(EXIT_FAILURE);
  }
#endif
  NGLMessage::drawLine(Colours::YELLOW);

  NGLMessage::addMessage("NGL configured with ", Colours::NORMAL, TimeFormat::TIME);

  // Nasty hack as new version of fmt doesn't work with glGetString.
  // auto s = format("GLSL version: {}", glGetString(GL_VERSION));
  // should work as per docs but current version not working at present.
  char s[100];
  std::snprintf(s,100, "%s", glGetString(GL_VERSION));

  NGLMessage::addMessage(fmt::format("OpenGL {}", s));
  std::snprintf(s,100, "%s", glGetString(GL_SHADING_LANGUAGE_VERSION));
  NGLMessage::addMessage(fmt::format("GLSL version {}", s));

  NGLMessage::drawLine(Colours::YELLOW);

  VAOFactory::registerVAOCreator(simpleVAO, SimpleVAO::create);
  VAOFactory::registerVAOCreator(multiBufferVAO, MultiBufferVAO::create);
  VAOFactory::registerVAOCreator(simpleIndexVAO, SimpleIndexVAO::create);
  ShaderLib::loadDefaultShaders();
  VAOPrimitives::createDefaultVAOs();
}

NGLInit::NGLInit()
{
#if defined(USINGIOS_) || !defined(__APPLE__)
  if(gl3wInit())
  {
    NGLMessage::drawLine(Colours::RED);
    NGLMessage::addError("failed to initialize OpenGL");
    NGLMessage::drawLine(Colours::RED);
    exit(EXIT_FAILURE);
  }
  if(!gl3wIsSupported(4, 1))
  {
    NGLMessage::drawLine(Colours::RED);
    NGLMessage::addError("To run these demos you need a modern OpenGL Version");
    NGLMessage::addError("The lowest level OpenGL we support is 4.1");
    NGLMessage::addError("It could be you don't have the correct drivers installed");
    NGLMessage::addError("Or if linux on a laptop it could be using the intel driver and not the GPU");
    NGLMessage::addError("for more info contact Jon");
    NGLMessage::drawLine(Colours::RED);
    exit(EXIT_FAILURE);
  }
#endif
  NGLMessage::drawLine(Colours::YELLOW);
  NGLMessage::addMessage("NGL configured with ", Colours::NORMAL, TimeFormat::TIME);
  char s[100];
  std::snprintf(s,100, "%s", glGetString(GL_VERSION));

  NGLMessage::addMessage(fmt::format("OpenGL {}", s));
  std::snprintf(s,100, "%s", glGetString(GL_SHADING_LANGUAGE_VERSION));

  NGLMessage::addMessage(fmt::format("GLSL version {}", s));
  NGLMessage::drawLine(Colours::YELLOW);

  VAOFactory::registerVAOCreator(simpleVAO, SimpleVAO::create);
  VAOFactory::registerVAOCreator(multiBufferVAO, MultiBufferVAO::create);
  VAOFactory::registerVAOCreator(simpleIndexVAO, SimpleIndexVAO::create);
  ShaderLib::loadDefaultShaders();
}

} // namespace ngl
