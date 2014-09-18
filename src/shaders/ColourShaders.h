#ifndef COLOURSHADERS_H__
#define COLOURSHADERS_H__
// see below for the really cool c++ 11 version of this

static const char * colourVertexShader[]={
  "#version 150 \n"
  "uniform mat4 MVP; \n"
  "in vec3 inVert; \n"
  "uniform vec4 Colour; \n"
  "void main(void) \n"
  "{ \n"
  " gl_Position = MVP*vec4(inVert, 1.0); \n"
  "}  \n\0"
};

static const char * colourFragmentShader[]={
  "#version 150 \n"
  "uniform vec4 Colour; \n"
  "out vec4 outColour;  \n"
  "void main () \n"
  "{ \n"
  "  outColour = Colour; \n"
  "}  \n\0"
};
/*
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
*/
#endif

