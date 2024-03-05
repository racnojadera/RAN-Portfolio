#version 330
layout (location = 0) in vec3 vertexPosition;

uniform mat4 model;
uniform mat4 dirLightViewMatrix;
uniform mat4 dirLightProjMatrix;

void main()
{
    gl_Position = dirLightProjMatrix * dirLightViewMatrix * model * vec4(vertexPosition, 1.0f);
}  