#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "ShaderLib.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitShaderLib(py::module & m)
  {

    py::enum_<ShaderType>(m, "ShaderType")
        .value("VERTEX", ShaderType::VERTEX)
        .value("FRAGMENT", ShaderType::FRAGMENT)
        .value("TESSCONTROL", ShaderType::TESSCONTROL)
        .value("TESSEVAL", ShaderType::TESSEVAL)
        .value("COMPUTE", ShaderType::COMPUTE)
        .value("NONE", ShaderType::NONE)
         ;

    py::enum_<ErrorExit>(m, "ErrorExit")
        .value("ON",ErrorExit::ON )
        .value("OFF",ErrorExit::OFF)
      ;


    py::class_<ShaderLib, std::unique_ptr<ShaderLib, py::nodelete>>(m, "ShaderLib")
        .def_static("instance",&ShaderLib::instance)
        .def("createShaderProgram",&ShaderLib::createShaderProgram)
        .def("attachShader",&ShaderLib::attachShader)
        .def("attachShaderToProgram",&ShaderLib::attachShaderToProgram)
        .def("getProgramID",&ShaderLib::getProgramID)
        .def("compileShader",&ShaderLib::compileShader)
        .def("linkProgramObject",&ShaderLib::linkProgramObject)
        .def("toggleDebug",&ShaderLib::toggleDebug)
        .def("use",&ShaderLib::use)
        .def("bindAttribute",&ShaderLib::bindAttribute)
        .def("bindFragDataLocation",&ShaderLib::bindFragDataLocation)
        .def("__getitem__",(ShaderProgram * (ShaderLib::*)(const std::string &)) &ShaderLib::operator[])
        .def("__getitem__",(ShaderProgram * (ShaderLib::*)(const char *)) &ShaderLib::operator[])

        .def("loadShader",(bool (ShaderLib::*)(const std::string &,const std::string &,
                                               const std::string &,const std::string &,
                                               ngl::ErrorExit )) &ShaderLib::loadShader,
        "load shader",py::arg("_shaderName")="",py::arg("_vert")="",
         py::arg("_frag")="",py::arg("_geo")="",py::arg("_exitOnError")=ngl::ErrorExit::OFF )

        .def("loadShader",(bool (ShaderLib::*)(const std::string &,const std::string &,
                                               const std::string &,ErrorExit )) &ShaderLib::loadShader,
             "load shader",py::arg("_shaderName")="",py::arg("_vert")="",
              py::arg("_frag")="",py::arg("_exitOnError")=ErrorExit::OFF )





        .def("loadFromJson",&ShaderLib::loadFromJson)
        .def("debugOn",&ShaderLib::debugOn)
        .def("debugOff",&ShaderLib::debugOff)
        .def("getNumShaders",&ShaderLib::getNumShaders)
        .def("printProperties",&ShaderLib::printProperties)
        .def("reset",&ShaderLib::reset)
        .def("getAttribLocation",&ShaderLib::getAttribLocation)
        .def("loadShaderSource",&ShaderLib::loadShaderSource)
        .def("loadShaderSourceFromString",&ShaderLib::loadShaderSourceFromString)
        .def("useNullProgram",&ShaderLib::useNullProgram)
        .def("getUniformBlockIndex",&ShaderLib::getUniformBlockIndex)
       // .def("registerUniform",&ShaderLib::registerUniform)
        .def("autoRegisterUniforms",&ShaderLib::autoRegisterUniforms)
        .def("printRegisteredUniforms",&ShaderLib::printRegisteredUniforms)
        .def("setUniform",(void (ShaderLib::*)(const std::string &, Real)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Real,Real)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Real,Real,Real)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Real,Real,Real,Real)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &, GLint)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,GLint,GLint)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,GLint,GLint,GLint)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,GLint,GLint,GLint,GLint)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Vec2)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Vec3)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Vec4)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Mat3)) &ShaderLib::setUniform)
        .def("setUniform",(void (ShaderLib::*)(const std::string &,Mat4)) &ShaderLib::setUniform)
        .def("getShaderID",&ShaderLib::getShaderID)
        .def("getShader",&ShaderLib::getShader)
        .def("setUniformBuffer", (void (ShaderLib::*)(const std::string &_uniformBlockName, size_t _size, void *_data)) &ShaderLib::setUniformBuffer )
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Real &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Real &, Real &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Vec2 &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Real &, Real &, Real &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Vec3 &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Real &, Real &, Real &, Real &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Vec4 &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Mat2 &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Mat3 &)) &ShaderLib::getUniform)
        .def("getUniform",(void (ShaderLib::*)(const std::string &, Mat4 &)) &ShaderLib::getUniform)

        ;



  }

}
