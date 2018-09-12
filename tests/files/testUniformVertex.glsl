#version 410

uniform float testFloat;
out float outTestFloat;

uniform vec2 testVec2;
out vec2 outTestVec2;

uniform vec3 testVec3;
out vec3 outTestVec3;

uniform vec4 testVec4;
out vec4 outTestVec4;

void main()
{
  outTestFloat=testFloat;
  outTestVec2=testVec2;
  outTestVec3=testVec3;
  outTestVec4=testVec4;
  gl_Position=vec4(1);

}
