#ifndef TEXTSHADERS_H_
#define TEXTSHADERS_H_
#include <string>

const std::string textVertexShader =
R"DELIM(
#version 150
in vec2 inVert;
in vec2 inUV;
out vec2 vertUV;
uniform vec3 textColour;
uniform float scaleX;
uniform float scaleY;
uniform float xpos;
uniform float ypos;
void main()
{
  vertUV=inUV;
  gl_Position=vec4( ((xpos+inVert.x)*scaleX)-1.0,((ypos+inVert.y)*scaleY)+1.0,0.0,1.0);
}
)DELIM";




const std::string  textFragmentShader=
R"DELIM(
#version 150
uniform sampler2D tex;
in vec2 vertUV;
out vec4 fragColour;
uniform vec3 textColour;
void main()
{
  vec4 text=texture(tex,vertUV.st);
  fragColour.rgb=textColour.rgb;
  fragColour.a=text.a;
}
)DELIM";

#endif

