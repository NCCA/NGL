#include "VAOFactory.h"
#include <iostream>

namespace ngl
{
std::unordered_map< std::string, std::function< std::unique_ptr< AbstractVAO >(GLenum _mode) > > VAOFactory::m_vaoCreators;

void VAOFactory::registerVAOCreator(const std::string &_type, std::function< std::unique_ptr< AbstractVAO >(GLenum _mode) > _cb)
{
  m_vaoCreators[_type.data()] = _cb;
}

void VAOFactory::unregisterVAOCreator(const std::string &_type)
{
  m_vaoCreators.erase(_type.data());
}

std::unique_ptr< AbstractVAO > VAOFactory::createVAO(const std::string &_type, GLenum _mode)
{

  auto it = m_vaoCreators.find(_type.data());
  if(it != m_vaoCreators.end())
  {
    // call the creation callback to construct this derived type
    return it->second(_mode);
  }
  return nullptr;
}

void VAOFactory::listCreators()
{
  NGLMessage::addMessage("******************************\n", Colours::WHITE, TimeFormat::NONE);
  NGLMessage::addMessage("VAOFactory Creators List ", Colours::WHITE, TimeFormat::NONE);
  NGLMessage::addMessage("******************************", Colours::WHITE, TimeFormat::NONE);
  for(auto c : m_vaoCreators)
  {
    NGLMessage::addMessage(fmt::format("Creator {0} created", c.first), Colours::WHITE, TimeFormat::NONE);
  }
  NGLMessage::addMessage("******************************", Colours::WHITE, TimeFormat::NONE);
}

} // namespace ngl
