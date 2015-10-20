#ifndef DIFFUSESHADERS_H__
#define DIFFUSESHADERS_H__
// see below for the really cool c++ 11 version of this
const std::string diffuseVertexShader =
R"DELIM(
  #version 150
  out vec3 fragmentNormal;
  in vec3 inVert;
  in vec3 inNormal;
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
 #version 150
 in vec3 fragmentNormal;
 out vec4 fragColour;
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

