#version 330
layout (location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix;
uniform mat4 dirLightViewMatrix;
uniform mat4 dirLightProjMatrix;

void main()
{
    gl_Position = dirLightProjMatrix * dirLightViewMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
}  