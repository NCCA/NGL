#ifndef __SHADERPROGRAM_INC_H__
#define __SHADERPROGRAM_INC_H__
// import the namespace for convenience
using namespace boost::python;



class_<ShaderProgram>("ShaderProgram")
    /// we have to define an init method for
    /// each possible version available above
  .def(init<std::string>())
  .def("use",&ShaderProgram::use)
  .def("unbind",&ShaderProgram::unbind)
  .def("attachShader",&ShaderProgram::attachShader)
  //.def("bindAttrib",&ShaderProgram::bindAttrib)
  .def("link",&ShaderProgram::link)
  .def("getID",&ShaderProgram::getID)
  .def("getUniformLocation",&ShaderProgram::getUniformLocation)
  .def("setUniform1f",&ShaderProgram::setUniform1f)
  .def("setUniform2f",&ShaderProgram::setUniform2f)
  .def("setUniform3f",&ShaderProgram::setUniform3f)
  .def("setUniform4f",&ShaderProgram::setUniform4f)
  .def("setUniform1fv",&ShaderProgram::setUniform1fv)
  .def("setUniform2fv",&ShaderProgram::setUniform2fv)
  .def("setUniform3fv",&ShaderProgram::setUniform3fv)
  .def("setUniform4fv",&ShaderProgram::setUniform4fv)
  .def("setUniform1i",&ShaderProgram::setUniform1i)
  .def("setUniform2i",&ShaderProgram::setUniform2i)
  .def("setUniform3i",&ShaderProgram::setUniform3i)
  .def("setUniform4i",&ShaderProgram::setUniform4i)
  .def("setUniform1iv",&ShaderProgram::setUniform1iv)
  .def("setUniform2iv",&ShaderProgram::setUniform1iv)
  .def("setUniform2iv",&ShaderProgram::setUniform1iv)
  .def("setUniform3iv",&ShaderProgram::setUniform1iv)
  .def("setUniform4iv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix2fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix3fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix4fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix2x3fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix2x4fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix2x3fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix3x2fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix3x4fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix4x2fv",&ShaderProgram::setUniform1iv)
  .def("setUniformMatrix4x3fv",&ShaderProgram::setUniform1iv)
  .def("getUniformfv",&ShaderProgram::setUniform1iv)
  .def("getUniformiv",&ShaderProgram::setUniform1iv)
  .def("enableAttribArray",&ShaderProgram::setUniform1iv)
  .def("disableAttribArray",&ShaderProgram::setUniform1iv)
  .def("enableAttribArray",&ShaderProgram::setUniform1iv)
  .def("vertexAttribPointer",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib1f",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib2f",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib2f",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib3f",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib4f",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib1fv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib2fv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib3fv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib4fv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib4iv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib4uiv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib4Niv",&ShaderProgram::setUniform1iv)
  .def("vertexAttrib4Nuiv",&ShaderProgram::setUniform1iv)
;


#endif


