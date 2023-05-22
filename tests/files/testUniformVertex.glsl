#version 410

uniform float testFloat;
out float outTestFloat;

uniform vec2 testVec2;
out vec2 outTestVec2;

uniform vec3 testVec3;
out vec3 outTestVec3;

uniform vec4 testVec4;
out vec4 outTestVec4;

uniform mat2 testMat2;
uniform mat3 testMat3;
uniform mat4 testMat4;

uniform vec3 testArray[3];
void main()
{
  outTestFloat=testFloat;
  outTestVec2=testMat2*testVec2;
  outTestVec3=testMat3*testVec3;
  outTestVec4=testMat4*testVec4;
  outTestVec3+=testArray[0];
  outTestVec3+=testArray[1];
  outTestVec3+=testArray[2];

  gl_Position=vec4(1);

}
