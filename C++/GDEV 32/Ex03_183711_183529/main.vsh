#version 330

// Vertex position
layout(location = 0) in vec3 vertexPosition;

// Vertex color
layout(location = 1) in vec3 vertexColor;

// Vertex normal coordinate
layout(location = 2) in vec3 vertexNormal;



// Color (will be passed to the fragment shader)
out vec3 outColor;

// Normal (will be passed to the fragment shader)
out vec3 outNormal;

// Vertex Position (will be passed to the fragment shader)
out vec3 outPosition;

// Shadow Position (will be passed to the fragment shader)
out vec4 outPositionShadow;


uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 lightSrcMatrix;

void main()
{
	vec4 unmodifiedPosition = vec4(vertexPosition, 1.0f);
    gl_Position = projMatrix * viewMatrix * modelMatrix * unmodifiedPosition;

    outPosition = vec3(modelMatrix * unmodifiedPosition);
    outNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
	outColor = vertexColor;
    outPositionShadow = lightSrcMatrix * vec4(outPosition, 1.0f);
}