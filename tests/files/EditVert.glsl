#version 410 core

uniform vec4 lightPos[@numLights];
void main()
{
  gl_Position=vec4(lightPos[0].xyz,@breakMe);
}
