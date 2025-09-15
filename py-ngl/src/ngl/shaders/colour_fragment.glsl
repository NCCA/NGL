#version 410 core
uniform vec4 Colour;
layout(location=0) out vec4 outColour;

void main ()
{
  outColour = Colour;
}
