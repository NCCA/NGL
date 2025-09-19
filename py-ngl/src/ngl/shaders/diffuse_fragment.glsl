#version 410
in vec3 fragmentNormal;
in vec3 fragmentPosition; // Receive fragment position

layout (location =0) out vec4 fragColour;

uniform vec4 Colour;
uniform vec3 lightPos; // Light's position in view space
uniform vec4 lightDiffuse;

void main ()
{
    // Ensure fragment normal is unit length
    vec3 N = normalize(fragmentNormal);
    // Calculate vector from fragment to light
    vec3 L = normalize(lightPos - fragmentPosition);
    // Calculate diffuse factor, ensuring it's not negative
    float diffuse = max(dot(L, N), 0.0);
    // Final colour
    fragColour = Colour * lightDiffuse * diffuse;
}
