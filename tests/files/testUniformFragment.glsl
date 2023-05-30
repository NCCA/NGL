#version 410

uniform float testFloat;
in float outTestFloat;
in vec2 outTestVec2;
in vec3 outTestVec3;
in vec4 outTestVec4;

flat in int outTestInt;

layout(location=0) out vec4 fragColour;

void main()
{
  // this nvidia compiler will optimise out values not used so we need to use them.
  vec4 total=vec4(outTestFloat)+vec4(outTestVec2,0,0)+
             vec4(outTestVec3,0)+outTestVec4;
  fragColour=total+vec4(outTestInt);
}
