#include <pybind11/pybind11.h>

#include "Shader.h"
namespace py = pybind11;
namespace ngl
{

  void pyInitShader(py::module & m)
  {
    py::class_<Shader>(m, "Shader")
        .def(py::init<std::string ,  ShaderType >())
        .def("compile",&Shader::compile)
        .def("load",&Shader::load)
        .def("loadFromString",&Shader::loadFromString)
        .def("toggleDebug",&Shader::toggleDebug)
        .def("getShaderHandle",&Shader::getShaderHandle)
        .def("incrementRefCount",&Shader::incrementRefCount)
        .def("decrementRefCount",&Shader::decrementRefCount)
        .def("getRefCount",&Shader::getRefCount)
        .def("getShaderSource",&Shader::getShaderSource)

        ;

  }
}
