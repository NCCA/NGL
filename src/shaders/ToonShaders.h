#ifndef TOONSHADERS_H_
#define TOONSHADERS_H_
#include <string>

const std::string toonVertexShader =
R"DELIM(
  #version 150
  in vec3 inVert;
  in vec3 inNormal;
  in vec2 inUV;
  uniform mat4 MVP;
  uniform mat3 normalMatrix;
  out vec3 normalEyeSpace;
  void main()
  {
      normalEyeSpace = normalMatrix * inNormal;
      gl_Position = MVP*vec4(inVert,1.0);
  }
)DELIM";

// shader modified from http://prideout.net/blog/?p=22
  const std::string toonFragmentShader =
  R"DELIM(
  #version 150
  in vec3 normalEyeSpace;
  out vec4 FragColor;
  uniform vec4 ambient;//=vec4(0.1,0.1,0.1,1.0);
  uniform vec4 Colour;//=vec4(1.0,1.0,1.0,1.0);
  uniform vec4 specular;//=vec4(1.0,1.0,1.0,1.0);
  uniform float shininess;//=20;
  uniform vec3 lightPos;//=vec3(1,1,1);


  float stepmix(float edge0, float edge1, float E, float x)
  {
      float T = clamp(0.5 * (x - edge0 + E) / E, 0.0, 1.0);
      return mix(edge0, edge1, T);
  }

  void main()
  {
      vec3 N = normalize(normalEyeSpace);
      vec3 L = normalize(lightPos);
      vec3 Eye = vec3(0, 0, 1);
      vec3 H = normalize(L + Eye);
      float df = max(0.0, dot(N, L));
      float sf = max(0.0, dot(N, H));
      sf = pow(sf, shininess);
      const float A = 0.1;
      const float B = 0.3;
      const float C = 0.6;
      const float D = 1.0;
      float E = fwidth(df);
      if      (df > A - E && df < A + E) df = stepmix(A, B, E, df);
      else if (df > B - E && df < B + E) df = stepmix(B, C, E, df);
      else if (df > C - E && df < C + E) df = stepmix(C, D, E, df);
      else if (df < A) df = 0.0;
      else if (df < B) df = B;
      else if (df < C) df = C;
      else df = D;
      E = fwidth(sf);
      if (sf > 0.5 - E && sf < 0.5 + E)
      {
          sf = smoothstep(0.5 - E, 0.5 + E, sf);
      }
      else
      {
          sf = step(0.5, sf);
      }
      FragColor = ambient + df * Colour + sf * specular;
  }
)DELIM";












#endif

