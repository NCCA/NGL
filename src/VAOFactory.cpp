#include "VAOFactory.h"



namespace ngl
{
  std::unordered_map<std::string, std::function<AbstractVAO *(GLenum _mode)>> VAOFactory::m_vaoCreators;

  void VAOFactory::registerVAOCreator(const std::string &_type,std::function<AbstractVAO *(GLenum _mode)> _cb)
  {
    m_vaoCreators[_type] = _cb;
  }

  void VAOFactory::unregisterVAOCreator(const std::string &_type)
  {
    m_vaoCreators.erase(_type);
  }

  AbstractVAO *VAOFactory::createVAO(const std::string &_type, GLenum _mode)
  {

    auto it = m_vaoCreators.find(_type);
    if (it != m_vaoCreators.end())
    {
      // call the creation callback to construct this derived type
      return it->second(_mode);
    }
    return nullptr;
  }




}
