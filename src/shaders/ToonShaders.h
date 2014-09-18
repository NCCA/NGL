#ifndef TOONSHADERS_H__
#define TOONSHADERS_H__
// see below for the really cool c++ 11 version of this

static const char * toonVertexShader[]={
  "#version 150 \n"
  "in vec3 inVert; \n"
  "in vec3 inNormal; \n"
  "in vec2 inUV; \n"
  "uniform mat4 MVP; \n"
  "uniform mat3 normalMatrix; \n"
  "out vec3 normalEyeSpace; \n"
  "void main() \n"
  "{ \n"
  "		normalEyeSpace = normalMatrix * inNormal; \n"
  "		gl_Position = MVP*vec4(inVert,1.0); \n"
  "} \n\0"

};

// shader modified from http://prideout.net/blog/?p=22

static const char * toonFragmentShader[]={
  "#version 150 \n"
  "in vec3 normalEyeSpace; \n"
  "out vec4 FragColor; \n"
  "uniform vec4 ambient;//=vec4(0.1,0.1,0.1,1.0); \n"
  "uniform vec4 Colour;//=vec4(1.0,1.0,1.0,1.0); \n"
  "uniform vec4 specular;//=vec4(1.0,1.0,1.0,1.0); \n"
  "uniform float shininess;//=20; \n"
  "uniform vec3 lightPos;//=vec3(1,1,1); \n"


  "float stepmix(float edge0, float edge1, float E, float x) \n"
  "{ \n"
  "		float T = clamp(0.5 * (x - edge0 + E) / E, 0.0, 1.0); \n"
  "		return mix(edge0, edge1, T); \n"
  "} \n"

  "void main() \n"
  "{ \n"
  "		vec3 N = normalize(normalEyeSpace); \n"
  "		vec3 L = normalize(lightPos); \n"
  "		vec3 Eye = vec3(0, 0, 1); \n"
  "		vec3 H = normalize(L + Eye); \n"
  "		float df = max(0.0, dot(N, L)); \n"
  "		float sf = max(0.0, dot(N, H)); \n"
  "		sf = pow(sf, shininess); \n"
  "		const float A = 0.1; \n"
  "		const float B = 0.3; \n"
  "		const float C = 0.6; \n"
  "		const float D = 1.0; \n"
  "		float E = fwidth(df); \n"
  "		if      (df > A - E && df < A + E) df = stepmix(A, B, E, df); \n"
  "		else if (df > B - E && df < B + E) df = stepmix(B, C, E, df); \n"
  "		else if (df > C - E && df < C + E) df = stepmix(C, D, E, df); \n"
  "		else if (df < A) df = 0.0; \n"
  "		else if (df < B) df = B; \n"
  "		else if (df < C) df = C; \n"
  "		else df = D; \n"
  "		E = fwidth(sf); \n"
  "		if (sf > 0.5 - E && sf < 0.5 + E) \n"
  "		{ \n"
  "				sf = smoothstep(0.5 - E, 0.5 + E, sf); \n"
  "		} \n"
  "		else \n"
  "		{ \n"
  "				sf = step(0.5, sf); \n"
  "		} \n"
  "		FragColor = ambient + df * Colour + sf * specular; \n"
  "} \n\0"
};











#endif

