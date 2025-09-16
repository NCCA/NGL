#version 410
layout (location = 0) in vec4 inVert; // <vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform vec3 textColour;
uniform mat4 projection;

void main()
{
  gl_Position = projection * vec4(inVert.xy, 0.0, 1.0);
  TexCoords = inVert.zw;
}
