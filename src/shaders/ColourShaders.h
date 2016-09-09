#ifndef COLOURSHADERS_H_
#define COLOURSHADERS_H_
#include <string>

const std::string colourVertexShader =
R"DELIM(
#version 150

/// @file Colour.vs
/// @brief a basic unshaded solid colour shader used with Colour.fs

/// @brief MVP matrix passed from our app
uniform mat4 MVP;

// first attribute the vertex values from our VAO
in vec3 inVert;
/// @brief the colour to shade draw with
uniform vec4 Colour;

void main(void)
{

  // calculate the vertex position
  gl_Position = MVP*vec4(inVert, 1.0);

}

)DELIM";




const std::string  colourFragmentShader=
R"DELIM(
#version 150
/// @file Colour.fs
/// @brief a basic unshaded solid colour shader
/// @brief the colour to shade draw with
uniform vec4 Colour;
out vec4 outColour;

void main ()
{
  outColour = Colour;
}


)DELIM";

#endif

