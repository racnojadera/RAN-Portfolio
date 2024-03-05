#version 330

// Color
in vec3 outColor;

// Normal
in vec3 outNormal;

// Vertex Position 
in vec3 outPosition;

// Shadow Position
in vec4 outPositionShadow;

// Final Color Outputted
out vec4 finalColor;



// Struct for material
struct Material
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

//Struct for Light
struct LightSource
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



uniform sampler2D depthMap;
uniform mat4 viewMatrix;
uniform vec3 camPosition;
uniform LightSource light;
uniform Material material;

void main()
{

	// --- LIGHT ---

    //Ambient
	vec3 ambient = light.ambient * material.diffuse; 

    // Diffuse
    vec3 normalized = normalize(outNormal);
    vec3 lightDirection = normalize(-1 * light.direction);
    float diffMax = max(dot(normalized, lightDirection), 0.0);
    vec3 diffuse = diffMax * material.diffuse * light.diffuse ;
    
    // Specular
    vec3 viewDir = normalize(camPosition - outPosition);
    vec3 reflectDirection = reflect((-1 * lightDirection), normalized);
    float specMax = pow(max(dot(viewDir, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * specMax * material.specular;



    // --- SHADOW ---
    vec3 lightNDC = outPositionShadow.xyz / outPositionShadow.w;
    lightNDC = (lightNDC / 2.0f) + 0.5f;
    float nearestDepth = texture(depthMap, lightNDC.xy).r; 
	float biasValue = max(0.1 * (1- dot(normalized,lightDirection)), 0.01);
    float currentDepth = lightNDC.z - biasValue;
    float shadow = 1.0f;

    if(currentDepth > nearestDepth)
    {
        shadow = 1.0f;
    }
    else
    {
        shadow = 0.0f;
    }

    // --- FINAL ---
    vec3 lightAns = (ambient + ((1.0 - shadow) * (diffuse + specular))) ;
	finalColor = vec4(lightAns, 1.0f) * vec4(outColor,1.0f);
}
                         