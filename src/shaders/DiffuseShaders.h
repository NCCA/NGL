#ifndef DIFFUSESHADERS_H_
#define DIFFUSESHADERS_H_
// see below for the really cool c++ 11 version of this
#include <string>

const std::string diffuseVertexShader =
R"DELIM(
  #version 410
  out vec3 fragmentNormal;
  layout(location=0) in vec3 inVert;
  layout(location=1) in vec3 inNormal;
  uniform mat4 MVP;
  uniform mat3 normalMatrix;
  void main()
  {
  fragmentNormal = (normalMatrix*inNormal);
  gl_Position = MVP*vec4(inVert,1.0);
  }
)DELIM";

const std::string diffuseFragmentShader =
R"DELIM(
 #version 410
 in vec3 fragmentNormal;
 layout (location =0) out vec4 fragColour;
 uniform vec4 Colour;
 uniform vec3 lightPos;
 uniform vec4 lightDiffuse;
 void main ()
 {
 fragColour= vec4(0.);
 vec3 N = normalize(fragmentNormal);
 vec3 L = normalize(lightPos);
 fragColour += Colour*lightDiffuse *dot(L, N);
 }
)DELIM";



#endif

