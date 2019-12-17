#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "ShaderProgram.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitShaderProgram(py::module & m)
  {
    py::class_<ShaderProgram>(m, "ShaderProgram")
        .def(py::init<std::string >())
        .def("use",&ShaderProgram::use)
        .def("unbind",&ShaderProgram::unbind)
        .def("attachShader",&ShaderProgram::attachShader)
        .def("bindAttribute",&ShaderProgram::bindAttribute)
    //    .def("bindFragDataLocation",(void(ShaderProgram::*)(GLuint,const std::string &)) &ShaderProgram::bindFragDataLocation)
        .def("link",&ShaderProgram::link)
        .def("getID",&ShaderProgram::getID)
        .def("getUniformLocation",&ShaderProgram::getUniformLocation)
        .def("printActiveUniforms",&ShaderProgram::printActiveUniforms)
        .def("printActiveAttributes",&ShaderProgram::printActiveAttributes)
        .def("printProperties",&ShaderProgram::printProperties)
        .def("setRegisteredUniform1f",&ShaderProgram::setRegisteredUniform1f)
        .def("setRegisteredUniform2f",&ShaderProgram::setRegisteredUniform2f)
        .def("setRegisteredUniform3f",&ShaderProgram::setRegisteredUniform3f)
        .def("setRegisteredUniform4f",&ShaderProgram::setRegisteredUniform4f)
        .def("setRegisteredUniform1i",&ShaderProgram::setRegisteredUniform1i)
        .def("setRegisteredUniform2i",&ShaderProgram::setRegisteredUniform2i)
        .def("setRegisteredUniform3i",&ShaderProgram::setRegisteredUniform3i)
        .def("setRegisteredUniform4i",&ShaderProgram::setRegisteredUniform4i)
        .def("setRegisteredUniformMatrix3fv",&ShaderProgram::setRegisteredUniformMatrix3fv)
        .def("setRegisteredUniformMatrix4fv",&ShaderProgram::setRegisteredUniformMatrix4fv)
        .def("getUniformfv",&ShaderProgram::getUniformfv)
        .def("getUniformiv",&ShaderProgram::getUniformiv)
        .def("enableAttribArray",&ShaderProgram::enableAttribArray)
        .def("disableAttribArray",&ShaderProgram::disableAttribArray)
        .def("autoRegisterUniforms",&ShaderProgram::autoRegisterUniforms)
        .def("printRegisteredUniforms",&ShaderProgram::printRegisteredUniforms)
        .def("bindFragDataLocation", py::overload_cast<GLuint,const char *>(&ShaderProgram::bindFragDataLocation))
        .def("getUniformBlockIndex",&ShaderProgram::getUniformBlockIndex)
        ;

  }


}
