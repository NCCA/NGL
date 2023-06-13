
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
    else if constexpr (is_ngl_vec<Ts>::value) 
    {
        std::vector<float> data(o_arg.m_openGL.size());   
        auto sucess = m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), data);
        //o_arg.m_openGL = data;
        std::copy_n(std::begin(data), data.size(), std::begin(o_arg.m_openGL));
        return sucess;
    }
    
    return false;
}



template <typename... Ts>
bool ShaderLib::getUniform(std::string_view _paramName, Ts &&...o_args) noexcept
{
    std::array<std::common_type_t<Ts...>, sizeof...(Ts)> data;
    auto sucess = m_shaderPrograms[m_currentShader]->getRegisteredUniform(_paramName.data(), data);
    std::size_t i = 0;
    // fold expression to copy data to o_args
    ((o_args = data[i++]), ...);
    return sucess;
}

