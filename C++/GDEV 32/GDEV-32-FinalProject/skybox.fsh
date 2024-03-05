#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube skybox;
uniform float dayNightCycle;

void main()
{    
    FragColor = texture(skybox, texCoords) * dayNightCycle;
}