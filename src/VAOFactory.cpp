#include "VAOFactory.h"
#include <iostream>


namespace ngl
{
  std::unordered_map<std::string, std::function<std::unique_ptr<AbstractVAO>(GLenum _mode)>> VAOFactory::m_vaoCreators;

  void VAOFactory::registerVAOCreator(const std::string &_type,std::function<std::unique_ptr<AbstractVAO>(GLenum _mode)> _cb)
  {
    m_vaoCreators[_type] = _cb;
  }

  void VAOFactory::unregisterVAOCreator(const std::string &_type)
  {
    m_vaoCreators.erase(_type);
  }

  std::unique_ptr<AbstractVAO> VAOFactory::createVAO(const std::string &_type, GLenum _mode)
  {

    auto it = m_vaoCreators.find(_type);
    if (it != m_vaoCreators.end())
    {
      // call the creation callback to construct this derived type
      return std::move(it->second(_mode));
    }
    return nullptr;
  }


  void VAOFactory::listCreators()
  {
    std::cout<<"******************************\n";
    std::cout<<"VAOFactory Creators List \n";
    std::cout<<"******************************\n";
    for(auto c : m_vaoCreators)
    {
      std::cout<<"Creator "<<c.first<<" registered \n";
    }
    std::cout<<"******************************\n";
  }

}
