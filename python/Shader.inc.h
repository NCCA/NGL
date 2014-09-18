#ifndef __SHADER_INC_H__
#define __SHADER_INC_H__
// import the namespace for convenience
using namespace boost::python;



class_<Shader>("Shader")
    /// we have to define an init method for
    /// each possible version available above
  .def(init<std::string,ngl::SHADERTYPE>())
  .def("compile",&Shader::compile)
  .def("load",&Shader::load)
  .def("compile",&Shader::compile)
  .def("toggleDebug",&Shader::toggleDebug)
  .def("getShaderHandle",&Shader::getShaderHandle)
  .def("incrementRefCount",&Shader::incrementRefCount)
  .def("decrementRefCount",&Shader::decrementRefCount)
  .def("getRefCount",&Shader::getRefCount)
 ;


enum_<SHADERTYPE>("SHADERTYPE")
    .value("VERTEX", VERTEX)
    .value("FRAGMENT", FRAGMENT)
    .value("GEOMETRY", GEOMETRY)
    .value("TESSCONTROL", TESSCONTROL)
    .value("TESSEVAL", TESSEVAL)

;


#endif


