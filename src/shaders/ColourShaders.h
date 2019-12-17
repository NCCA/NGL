#ifndef COLOURSHADERS_H_
#define COLOURSHADERS_H_
#include <string>

const std::string colourVertexShader =
R"(
#version 330 core

/// @file Colour.vs
/// @brief a basic unshaded solid colour shader used with Colour.fs

/// @brief MVP matrix passed from our app
uniform mat4 MVP;

// first attribute the vertex values from our VAO
layout(location=0) in vec3 inVert;
/// @brief the colour to shade draw with
uniform vec4 Colour;

void main(void)
{

  // calculate the vertex position
  gl_Position = MVP*vec4(inVert, 1.0);

}

)";




const std::string  colourFragmentShader=
R"(
#version 330 core
/// @file Colour.fs
/// @brief a basic unshaded solid colour shader
/// @brief the colour to shade draw with
uniform vec4 Colour;
layout(location=0) out vec4 outColour;

void main ()
{
  outColour = Colour;
}


)";

#endif

