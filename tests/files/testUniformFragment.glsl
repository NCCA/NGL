#version 410

uniform float testFloat;
in float outTestFloat;
in vec2 outTestVec2;
in vec3 outTestVec3;
in vec4 outTestVec4;

layout(location=0) out vec4 fragColour;

void main()
{
  fragColour=vec4(outTestFloat);
  fragColour=vec4(outTestVec2,0,0);
  fragColour=vec4(outTestVec3,0);
  fragColour=vec4(outTestVec4);
}
