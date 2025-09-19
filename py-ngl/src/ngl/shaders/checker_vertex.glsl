#version 410 core


/// @brief the vertex passed in
layout (location = 0) in vec3 inVert;
/// @brief the normal passed in
layout (location = 1) in vec3 inNormal;
/// @brief the in uv
layout (location = 2) in vec2 inUV;
out vec3 fragmentNormal;
out vec2 uv;
uniform mat4 MVP;
uniform mat3 normalMatrix;
void main()
{
  fragmentNormal = (normalMatrix*inNormal);
  uv=inUV;
  gl_Position = MVP*vec4(inVert,1.0);
}
