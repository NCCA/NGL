#ifndef __ShaderLib_INC_H__
#define __ShaderLib_INC_H__
// import the namespace for convenience
using namespace boost::python;

/// notice no_init and nocopyable as singleton,

class_<ShaderLib, boost::noncopyable>("ShaderLib",no_init)
    /// we have to define an init method for
    /// each possible version available above

    .def("instance", &ShaderLib::instance,
      return_value_policy<reference_existing_object>()).staticmethod("instance")

    .def("loadShader",&ShaderLib::loadShader)
    .def("debugOn",&ShaderLib::debugOn)
    .def("debugOff",&ShaderLib::debugOff)
    .def("getNumShaders",&ShaderLib::getNumShaders)
    .def("setShaderParamFromMat4",&ShaderLib::setShaderParamFromMat4)
    .def("setShaderParamFromVec4",&ShaderLib::setShaderParamFromVec4)
    .def("setShaderParam1i",&ShaderLib::setShaderParam1i)
    .def("setShaderParam1f",&ShaderLib::setShaderParam1f)
    .def("setShaderParam2f",&ShaderLib::setShaderParam2f)
    .def("setShaderParam3f",&ShaderLib::setShaderParam3f)
    .def("setShaderParam4f",&ShaderLib::setShaderParam4f)
    .def("use",&ShaderLib::use)
    .def("createShaderProgram",&ShaderLib::createShaderProgram)

    .def("attachShader",&ShaderLib::attachShader)
    .def("attachShaderToProgram",&ShaderLib::attachShaderToProgram)
    .def("getProgramID",&ShaderLib::getProgramID)
    .def("compileShader",&ShaderLib::compileShader)
    .def("linkProgramObject",&ShaderLib::linkProgramObject)
    .def("use",&ShaderLib::use)
    .def("bindAttribute",&ShaderLib::bindAttribute)
    .def("createShaderProgram",&ShaderLib::createShaderProgram)
    .def("loadShaderSource",&ShaderLib::loadShaderSource)
    .def("reset",&ShaderLib::reset)
    .def("getAttribLocation",&ShaderLib::getAttribLocation)
    .def("getShaderProgram",&ShaderLib::getShaderProgram,return_value_policy<manage_new_object>());
     ;

/*




  ShaderProgram * operator[](const std::string &_programName);
  ShaderProgram * operator[](const char *_programName);



  GLhandleARB operator[](
                         const ShaderLib&
                        );



 */

#endif


