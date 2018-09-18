#version 410 core

layout(location=0) out vec4 fragColour;

uniform vec4 lightPos[@numLights];

void main()
{
  fragColour=vec4(lightPos[1]);
}
