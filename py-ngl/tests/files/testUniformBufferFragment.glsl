#version 410 core

layout (location = 0) out vec4 colour;

in vec4 FragColour;
void main()
{
    colour=FragColour;
}