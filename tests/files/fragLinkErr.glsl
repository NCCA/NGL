#version 410 core

layout(location=0) out vec4 fragColour;
// interesting note here, mac will not cast a vec3 to a vec4 but nvidia will
// in this case we try to set a vec4 out to a vec2 in which will fail on both platforms
in vec2 colour;
void main()
{
  fragColour.rg=colour;
}
