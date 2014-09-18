namespace ngl
{


ShaderProgram *ShaderLib::getShaderProgram(
																								const std::string &_programName
																							 )
{
  std::map <std::string, ShaderProgram * >::const_iterator program=m_shaderPrograms.find(_programName);
  // make sure we have a valid  program
	if(program!=m_shaderPrograms.end() )
  {
    return  program->second;
  }
  else
  {
    std::cerr<<"Warning Program not know in [] "<<_programName.c_str();
    std::cerr<<"returning a null program and hoping for the best\n";
    return m_nullProgram;
  }
}

}
