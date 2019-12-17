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
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#if defined(LINUX) || defined(_WIN32)
  #include <cstdlib>
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLInit.cpp
/// @brief implementation files for NGLInit class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------

void NGLInit::setCommunicationMode(ngl::CommunicationMode _mode)
{
  switch (_mode)
  {
    case CommunicationMode::STDERR : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::STDERR)); break;
    case CommunicationMode::STDOUT : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::STDOUT)); break;
    case CommunicationMode::NULLCONSUMER : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::NULLCONSUMER)); break;
    case CommunicationMode::FILE : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::FILE)); break;
   }
}

void NGLInit::initMessageSystem()
{
  msg=std::make_unique<NGLMessage>(NGLMessage(NGLMessage::Mode::CLIENTSERVER,CommunicationMode::STDERR));
  msg->startMessageConsumer();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

}
NGLInit::NGLInit()
{

#if defined(USINGIOS_) || !defined(__APPLE__)
  if (gl3wInit())
  {
    msg->drawLine(Colours::RED);
    msg->addError("failed to initialize OpenGL");
    msg->drawLine(Colours::RED);
    exit(EXIT_FAILURE);
  }
  if (!gl3wIsSupported(4, 1))
  {
    msg->drawLine(Colours::RED);
    msg->addError("To run these demos you need a modern OpenGL Version");
    msg->addError("The lowest level OpenGL we support is 4.1");
    msg->addError("It could be you don't have the correct drivers installed");
    msg->addError("Or if linux on a laptop it could be using the intel driver and not the GPU");
    msg->addError("for more info contact Jon");
    msg->drawLine(Colours::RED);
    exit(EXIT_FAILURE);
  }
#endif
  initMessageSystem();
  msg->drawLine(Colours::YELLOW);
  msg->addMessage("NGL configured with ",Colours::NORMAL,TimeFormat::TIME);
  msg->addMessage(fmt::format("OpenGL {0}",glGetString(GL_VERSION)));
  msg->addMessage(fmt::format("GLSL version {0}",glGetString(GL_SHADING_LANGUAGE_VERSION)));
  msg->drawLine(Colours::YELLOW);

  VAOFactory::registerVAOCreator(simpleVAO,SimpleVAO::create);
  VAOFactory::registerVAOCreator(multiBufferVAO,MultiBufferVAO::create);
  VAOFactory::registerVAOCreator(simpleIndexVAO,SimpleIndexVAO::create);
}
//----------------------------------------------------------------------------------------------------------------------
NGLInit::~NGLInit()
{
  msg->stopMessageConsumer();
}


} // end of ngl namespace




