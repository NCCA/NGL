#version 410
out vec3 fragmentNormal;
out vec3 fragmentPosition;

layout(location=0) in vec3 inVert;
layout(location=1) in vec3 inNormal;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 normalMatrix;

void main()
{
  // Transform normal into view space but DO NOT normalize it here.
  // The interpolation and per-fragment normalization is key to smooth shading.
  fragmentNormal = normalMatrix * inNormal;

  // Transform vertex position into view space
  vec4 viewPosition = MV * vec4(inVert, 1.0);
  fragmentPosition = viewPosition.xyz;

  // Transform vertex to clip space
  gl_Position = MVP * vec4(inVert, 1.0);
}
