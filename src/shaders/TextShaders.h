#ifndef TEXTSHADERS_H_
#define TEXTSHADERS_H_
#include <string>

const std::string textVertexShader =
R"(
#version 330
layout (location = 0) in vec4 inVert; // <vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform vec3 textColour;
uniform mat4 projection;

void main()
{
  gl_Position = projection * vec4(inVert.xy, 0.0, 1.0);
  TexCoords = inVert.zw;

}
)";




const std::string  textFragmentShader=
R"(
#version 330 core
in vec2 TexCoords;
out vec4 fragColour;

uniform sampler2D text;
uniform vec3 textColour;

void main()
{    
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
  fragColour = vec4(textColour, 1.0) * sampled;
}  
)";

#endif

