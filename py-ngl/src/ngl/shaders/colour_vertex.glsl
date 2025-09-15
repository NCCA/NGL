#version 410 core

uniform mat4 MVP;

layout(location=0) in vec3 inVert;
uniform vec4 Colour;

void main(void)
{
  gl_Position = MVP*vec4(inVert, 1.0);
}
