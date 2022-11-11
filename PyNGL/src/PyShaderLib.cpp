#include "PyBindIncludes.h"

#include "ShaderLib.h"

namespace py = pybind11;
namespace ngl
{
void pyInitShaderLib(py::module &m)
{

  py::enum_< ShaderType >(m, "ShaderType")
    .value("VERTEX", ShaderType::VERTEX)
    .value("FRAGMENT", ShaderType::FRAGMENT)
    .value("TESSCONTROL", ShaderType::TESSCONTROL)
    .value("TESSEVAL", ShaderType::TESSEVAL)
    .value("COMPUTE", ShaderType::COMPUTE)
    .value("NONE", ShaderType::NONE);

  py::enum_< ErrorExit >(m, "ErrorExit")
    .value("ON", ErrorExit::ON)
    .value("OFF", ErrorExit::OFF);

  py::class_< ShaderLib, std::unique_ptr< ShaderLib, py::nodelete > >(m, "ShaderLib")
    .def_static("createShaderProgram", &ShaderLib::createShaderProgram)
    .def_static("attachShader", &ShaderLib::attachShader)
    .def_static("attachShaderToProgram", &ShaderLib::attachShaderToProgram)
    .def_static("getProgramID", &ShaderLib::getProgramID)
    .def_static("compileShader", &ShaderLib::compileShader)
    .def_static("linkProgramObject", &ShaderLib::linkProgramObject)
    .def_static("toggleDebug", &ShaderLib::toggleDebug)
    .def_static("use", &ShaderLib::use)
    .def_static("bindAttribute", &ShaderLib::bindAttribute)
    .def_static("bindFragDataLocation", &ShaderLib::bindFragDataLocation)

    .def_static("loadShader", py::overload_cast< std::string_view, std::string_view, std::string_view, std::string_view, ngl::ErrorExit >(&ShaderLib::loadShader), "load shader", py::arg("_shaderName") = "", py::arg("_vert") = "", py::arg("_frag") = "", py::arg("_geo") = "", py::arg("_exitOnError") = ngl::ErrorExit::OFF)

    .def_static("loadShader", py::overload_cast< std::string_view, std::string_view, std::string_view, ErrorExit >(&ShaderLib::loadShader), "load shader", py::arg("_shaderName") = "", py::arg("_vert") = "", py::arg("_frag") = "", py::arg("_exitOnError") = ErrorExit::OFF)

    .def_static("loadFromJson", &ShaderLib::loadFromJson)
    .def_static("debugOn", &ShaderLib::debugOn)
    .def_static("debugOff", &ShaderLib::debugOff)
    .def_static("getNumShaders", &ShaderLib::getNumShaders)
    .def_static("printProperties", &ShaderLib::printProperties)
    .def_static("reset", &ShaderLib::reset)
    .def_static("getAttribLocation", &ShaderLib::getAttribLocation)
    .def_static("loadShaderSource", &ShaderLib::loadShaderSource)
    .def_static("loadShaderSourceFromString", &ShaderLib::loadShaderSourceFromString)
    .def_static("useNullProgram", &ShaderLib::useNullProgram)
    .def_static("getUniformBlockIndex", &ShaderLib::getUniformBlockIndex)
    .def_static("editShader", &ShaderLib::editShader)
    .def_static("resetEdits", &ShaderLib::resetEdits)
    // .def_static("registerUniform",&ShaderLib::registerUniform)
    .def_static("autoRegisterUniforms", &ShaderLib::autoRegisterUniforms)
    .def_static("printRegisteredUniforms", &ShaderLib::printRegisteredUniforms)
    .def_static("setUniform", py::overload_cast< std::string_view, Real >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Real, Real >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Real, Real, Real >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Real, Real, Real, Real >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, GLint >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, GLint, GLint >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, GLint, GLint, GLint >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, GLint, GLint, GLint, GLint >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Vec2 >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Vec3 >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Vec4 >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Mat2 >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Mat3 >(&ShaderLib::setUniform))
    .def_static("setUniform", py::overload_cast< std::string_view, Mat4 >(&ShaderLib::setUniform))
    .def_static("getShaderID", &ShaderLib::getShaderID)
    .def_static("getShader", &ShaderLib::getShader)
    .def_static("setUniformBuffer", py::overload_cast< std::string_view, size_t, void * >(&ShaderLib::setUniformBuffer))
    // Note that NGL uses pass by reference, for python we have a different API
    .def_static("getUniform1f", [](std::string_view _name)
                {
             Real v;
             ShaderLib::getUniform(_name, v);
             return v; })
    .def_static("getUniformVec2", [](std::string_view _name)
                {
             Vec2 v;
             ShaderLib::getUniform(_name, v);
             return v; })

    .def_static("getUniform2f", [](std::string_view _name)
                {
             Vec2 v;
             ShaderLib::getUniform(_name, v);
             return py::make_tuple(v.m_x,v.m_y); })

    .def_static("getUniform3f", [](std::string_view _name)
                {
             Vec3 v;
             ShaderLib::getUniform(_name, v);
             return py::make_tuple(v.m_x,v.m_y,v.m_z); })
    .def_static("getUniformVec3", [](std::string_view _name)
                {
             Vec3 v;
             ShaderLib::getUniform(_name, v);
             return v; })
    .def_static("getUniform4f", [](std::string_view _name)
                {
             Vec4 v;
             ShaderLib::getUniform(_name, v);
             return py::make_tuple(v.m_x,v.m_y,v.m_z,v.m_w); })
    .def_static("getUniformVec4", [](std::string_view _name)
                {
             Vec4 v;
             ShaderLib::getUniform(_name, v);
             return v; })

    .def_static("getUniformMat2", [](std::string_view _name)
                {
             Mat2 v;
             ShaderLib::getUniform(_name, v);
             return v; })
    .def_static("getUniformMat3", [](std::string_view _name)
                {
             Mat3 v;
             ShaderLib::getUniform(_name, v);
             return v; })
    .def_static("getUniformMat4", [](std::string_view _name)
                {
             Mat4 v;
             ShaderLib::getUniform(_name, v);
             return v; })

    .def_static("getCurrentShaderName", &ShaderLib::getCurrentShaderName);
}

} // namespace ngl
