#include "ngl/TemplateHelpers.h"

template< typename Ts> 
bool ShaderProgram::setRegisteredUniform(std::string_view _varname ,Ts &&arg ) const noexcept
{
  auto uniform = m_registeredUniforms.find(_varname.data());
  if(uniform != m_registeredUniforms.end())
  {
  
    if constexpr (std::is_same<Ts,float&>::value )
    {
        glUniform1f(uniform->second.loc, arg);
        return true;
    } // end of float
    else if constexpr (std::is_same<Ts,int&>::value || std::is_same<Ts,bool&>::value)
    {
        glUniform1i(uniform->second.loc, arg);
        return true;
    }// end of int / bool
    else if constexpr(std::is_same<Ts,Mat2&>::value)
    {
        glUniformMatrix2fv(uniform->second.loc, 1, GL_FALSE, &arg.m_openGL[0]);
        return true;
    } // end of mat2

    else if constexpr(std::is_same<Ts,Mat3&>::value)
    {
        glUniformMatrix3fv(uniform->second.loc, 1, GL_FALSE, &arg.m_openGL[0]);
        return true;
    } // end of mat3
    else if constexpr(std::is_same<Ts,Mat4&>::value)
    {
        glUniformMatrix4fv(uniform->second.loc, 1, GL_FALSE, &arg.m_openGL[0]);
        return true;
    } // end of mat4
    #ifdef USEGLM
    else if constexpr(std::is_same<Ts,glm::mat2&>::value)
    {
        glUniformMatrix2fv(uniform->second.loc, 1, GL_FALSE, &arg[0][0]);
        return true;
    } // end of glmmat2
    else if constexpr(std::is_same<Ts,glm::mat3&>::value)
    {
        glUniformMatrix3fv(uniform->second.loc, 1, GL_FALSE, &arg[0][0]);
        return true;
    } // end of glmmat3
    else if constexpr(std::is_same<Ts,glm::mat4&>::value)
    {
        glUniformMatrix4fv(uniform->second.loc, 1, GL_FALSE, &arg[0][0]);
        return true;
    } // end of glmmat2
    #endif
    else if constexpr(std::is_same<Ts,Vec2&>::value)
    {
        glUniform2f(uniform->second.loc,arg.m_x,arg.m_y);
        return true;
    }
    else if constexpr(std::is_same<Ts,Vec3&>::value)
    {
        glUniform3f(uniform->second.loc,arg.m_x,arg.m_y,arg.m_z);
        return true;
    }
    else if constexpr(std::is_same<Ts,Vec4&>::value)
    {
        glUniform4f(uniform->second.loc,arg.m_x,arg.m_y,arg.m_z,arg.m_w);
        return true;
    }
    #ifdef USEGLM
    else if constexpr(std::is_same<Ts,glm::vec2&>::value)
    {
        glUniform2f(uniform->second.loc,arg.x,arg.y);
        return true;
    }
    else if constexpr(std::is_same<Ts,glm::vec3&>::value)
    {
        glUniform3f(uniform->second.loc,arg.x,arg.y,arg.z);
        return true;
    }
    else if constexpr(std::is_same<Ts,glm::vec4&>::value)
    {
        glUniform4f(uniform->second.loc,arg.x,arg.y,arg.z,arg.w);
        return true;
    }
    #endif
    // handle arrays as matrix
    else if constexpr(is_std_array<std::decay_t<Ts>>::value || 
                      is_std_vector<std::decay_t<Ts>>::value ||
                      std::is_array<Ts>::value)
    {
      if(arg.size() == 4)
      {
        glUniformMatrix2fv(uniform->second.loc, 1, GL_FALSE, &arg[0]);
        return true;
      }
      else if (arg.size() == 9)
      {
        glUniformMatrix3fv(uniform->second.loc, 1, GL_FALSE, &arg[0]);
        return true;
      }
      else if (arg.size() == 16)
      {
        glUniformMatrix4fv(uniform->second.loc, 1, GL_FALSE, &arg[0]);
        return true;
      }
    }
    
  }
  else
  {
      ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));
      return false;
  }
  return false;
}



template< typename... Ts>
bool ShaderProgram::setRegisteredUniform(std::string_view _varname ,Ts &&...args ) const noexcept
{
  auto uniform = m_registeredUniforms.find(_varname.data());
  // make sure we have a valid shader
  if(uniform != m_registeredUniforms.end())
  {        
    if constexpr (std::conjunction_v<std::is_same<float&, Ts>...>)
    {
        if constexpr (sizeof...(args) == 2)
        {
            auto values =std::forward_as_tuple(args...);        
            glUniform2f(uniform->second.loc,std::get<0>(values),std::get<1>(values));
            return true;
        }
        else if constexpr (sizeof...(args) == 3)
        {
            auto values = std::forward_as_tuple(args...);
            glUniform3f(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values));
            return true;
        }
        else if constexpr (sizeof...(args) == 4)
        {
            auto values = std::forward_as_tuple(args...);
            glUniform4f(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values),std::get<3>(values));
            return true;
        }
        else
        {
            ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));
            return false;
        }
    } // end float values
  else if constexpr (std::conjunction_v<std::is_same<int&, Ts>...>)
  {
  if constexpr (sizeof...(args) == 2)
      {
          auto values =std::forward_as_tuple(args...);        
          glUniform2i(uniform->second.loc,std::get<0>(values),std::get<1>(values));
          return true;
      }
      else if constexpr (sizeof...(args) == 3)
      {
          auto values = std::forward_as_tuple(args...);
          glUniform3i(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values));
          return true;
      }
      else if constexpr (sizeof...(args) == 4)
      {
          auto values = std::forward_as_tuple(args...);
          glUniform4i(uniform->second.loc,std::get<0>(values),std::get<1>(values),std::get<2>(values),std::get<3>(values));
          return true;
      }
      else
      {
          ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));
          return false;
      }
  }
  }
return false;
}


template< typename Ts> 
bool ShaderProgram::getRegisteredUniform(std::string_view _varname ,Ts &o_arg ) const noexcept
{
   // std::cout<<"getRegisteredUniform "<<__PRETTY_FUNCTION__<<'\n';

    auto uniform = m_registeredUniforms.find(_varname.data());
    if(uniform != m_registeredUniforms.end())
    {
      if constexpr (std::is_same<Ts,float>::value )
      {
        glGetUniformfv(m_programID, uniform->second.loc, &o_arg);
        return true;
      } // end of single float

      // ngl mat types
      if constexpr (std::is_same<Ts,ngl::Mat2>::value  || 
                    std::is_same<Ts,ngl::Mat3>::value ||
                    std::is_same<Ts,ngl::Mat4>::value)
      {
        glGetUniformfv(m_programID, uniform->second.loc, &o_arg.m_openGL[0]);
        return true;
      }

      if constexpr (std::is_same<Ts,int>::value )
      {
        glGetUniformiv(m_programID, uniform->second.loc, &o_arg);
        return true;
      } // end of float
      else if constexpr(is_std_array<Ts>::value || is_std_vector<Ts>::value)
      {
        if constexpr (std::is_same<array_value_type<Ts>,float>::value )
        {
          glGetUniformfv(m_programID, uniform->second.loc, o_arg.data());
          
          return true;
        } // end of float array
        else if constexpr (std::is_same<array_value_type<Ts>,int>::value)
        {
          glGetUniformiv(m_programID, uniform->second.loc, o_arg.data());
          return true;
        } // end of int array

      } // end of array
    } // end of uniform found
    else
    {
      ngl::NGLMessage::addWarning(fmt::format("Uniform {0} Not found in Shader {1}", _varname, m_programName));
      return false;
    }
return false;
}

