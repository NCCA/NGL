#version 410 core


layout(std140) uniform TransformUBO
{
  mat4 MVP;
  mat4 normalMatrix;
  mat4 M;
}transforms;

out vec4 FragColour;

void main()
{
    FragColour = vec4(1.0, 0.0, 0.0, 1.0);
    gl_Position = transforms.MVP*transforms.M*transforms.normalMatrix*vec4(0.0, 0.0, 0.0, 1.0);
}
