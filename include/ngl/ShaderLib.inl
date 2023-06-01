

template< typename Ts>
bool ShaderLib::setUniform(std::string_view _varname ,Ts &&arg )  noexcept
{
    return  m_shaderPrograms[m_currentShader]->setRegisteredUniform(_varname,arg);
}

template<typename ... Ts>
bool ShaderLib::setUniform(std::string_view _varname ,Ts &&...args)    noexcept
{
//     std::cout<<"set Uniform variadic "<<__PRETTY_FUNCTION__<<" "<<sizeof...(Ts)<<"\n";
    return m_shaderPrograms[m_currentShader]->setRegisteredUniform(_varname,args...);
}

template< typename Ts>
bool ShaderLib::getUniform(std::string_view _paramName, Ts &&o_arg) noexcept
{

    if constexpr (std::is_same<Ts,float&>::value  || 
                  std::is_same<Ts,int&>::value || 
                  is_ngl_matrix<Ts>::value  )
    {
        return m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), o_arg);
    }
    else if constexpr (std::is_same<Ts,ngl::Vec2 &>::value ) //|| std::is_same<Ts,ngl::Vec3 &>::value || std::is_same<Ts,ngl::Vec4 &>::value)
    {
        std::array<float,2> data;   
        auto ret = m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), data);
        o_arg.m_openGL = data;
        
        return ret;
    }
    else if constexpr (std::is_same<Ts,ngl::Vec3 &>::value ) //|| std::is_same<Ts,ngl::Vec3 &>::value || std::is_same<Ts,ngl::Vec4 &>::value)
    {
        std::array<float,3> data;   
        auto ret = m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), data);
        o_arg.m_openGL = data;
        
        return ret;
    }
    else if constexpr (std::is_same<Ts,ngl::Vec4 &>::value ) //|| std::is_same<Ts,ngl::Vec3 &>::value || std::is_same<Ts,ngl::Vec4 &>::value)
    {
        std::array<float,4 > data;   
        auto ret = m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), data);
        o_arg.m_openGL = data;
        
        return ret;
    }
    
    return false;
}



template <typename... Ts>
bool ShaderLib::getUniform(std::string_view _paramName, Ts &&...o_args) noexcept
{
    //auto values = std::forward_as_tuple(std::forward<Ts>(o_args)...);
    std::array<std::common_type_t<Ts...>, sizeof...(Ts)> data;
    auto ret = m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), data);
    std::size_t i = 0;
    // fold expression to copy data to o_args
    ((o_args = data[i++]), ...);
    // for(auto &a : data)
    // {
    //     std::cout<<"data "<<a<<"\n";
    // }
    // print_args(o_args...);
    return ret;
}

/*

template<typename ... Ts>
bool ShaderLib::setUniform(std::string_view _varname ,Ts &&...args)    noexcept
{
    // uses variadic templates to forward a variable number of arguments to a function. 
    // The function std::forward_as_tuple takes the arguments and returns a tuple of references to the arguments. 
    // The code then extracts the first argument from the tuple using std::get<0>(values) and assigns it to a variable v. 
    // Finally, the code uses a static assertion to check that all the arguments passed to the function are of the same type Ts. 
    // If the assertion fails, it will print an error message.
    
    // extract the arugments and get first type
    auto values = std::forward_as_tuple(args...);
    auto v=std::get<0>(values);
    // now ensure we have all the same type (this is a compile time check)
    static_assert(std::conjunction_v<std::is_same<decltype(v), Ts>...> ,
    "setUniform must have values of all the same types");
    static_assert(sizeof...(args) <= 4, "setUniform can only handle upto 4 values");

    // now we can just expand based on the size of args
    // we only have 4 types so it's simple.
    if constexpr (sizeof...(args) == 2)
    {
        auto values =std::forward_as_tuple(args...);        
        m_shaderPrograms[m_currentShader]->setRegisteredUniform(_varname,static_cast<decltype(v)>(std::get<0>(values)),
                                                                            static_cast<decltype(v)>(std::get<1>(values)));
        return true;
    }
    else if constexpr (sizeof...(args) == 3)
    {
        auto values =std::forward_as_tuple(args...);        
        m_shaderPrograms[m_currentShader]->setRegisteredUniform(_varname,static_cast<decltype(v)>(std::get<0>(values)),
                                                                            static_cast<decltype(v)>(std::get<1>(values)),
                                                                            static_cast<decltype(v)>(std::get<2>(values)));
        return true;
    }
    else if constexpr (sizeof...(args) == 4)
    {
        auto values =std::forward_as_tuple(args...);        
        m_shaderPrograms[m_currentShader]->setRegisteredUniform(_varname,static_cast<decltype(v)>(std::get<0>(values)),
                                                                            static_cast<decltype(v)>(std::get<1>(values)),
                                                                            static_cast<decltype(v)>(std::get<2>(values)),
                                                                            static_cast<decltype(v)>(std::get<3>(values)));
        return true;
    }
    return false;
}


  template< typename Ts>
  bool ShaderLib::getUniform(std::string_view _paramName, Ts &&o_arg) noexcept
  {
      return m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), o_arg);

  }


  template< typename ... Ts>
  bool ShaderLib::getUniform(std::string_view _paramName, Ts &&...o_args) noexcept
  {
    auto values = std::forward_as_tuple(o_args...);
    auto v=std::get<0>(values);

        std::array<decltype(v),sizeof...(o_args)> data;
        auto ret=m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(),data);
        size_t i=0;
        std::apply([data,&i](auto&&... args) {((args=data[i++] ), ...);}, values);

        // for(size_t i=0; i<sizeof...(o_args); ++i)
        // {
        //     std::get<i>(values)=data[i];
        // }
        return ret;
  }
*/