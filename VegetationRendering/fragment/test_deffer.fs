#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpec;
uniform sampler2D ssao;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 lightSpcaeMatrix;     

float ShadowCalculation(vec4 fragPosLightSpace, vec3 Normal, vec3 FragPos)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // Check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{   
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gColorSpec, TexCoords).rgb;
    float Specular = texture(gColorSpec, TexCoords).a;
    float AmbientOcclusion = texture(ssao, TexCoords).r;

    // than calculate lighting as usual
    vec3 lightColor = vec3(0.8f);
    // Ambient
    vec3 ambient = vec3(0.3 * Diffuse * AmbientOcclusion);
    // Diffuse
    // vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * Diffuse * lightColor;
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor * Specular;
    // simple attenuation
    // float max_distance = 1.5f;
    // float distance = length(lightPos - fs_in.FragPos);  
    // float attenuation = 1.0 / (distance * distance);

    // diffuse *= attenuation;
    // specular *= attenuation; 
    // Calculate shadow
    vec4 FragPosLightSpace = lightSpcaeMatrix * vec4(FragPos, 1.0f);// 
    float shadow = ShadowCalculation(FragPosLightSpace, normal, FragPos);              
    shadow = min(shadow, 0.75); // reduce shadow strength a little: allow some diffuse/specular light in shadowed regions
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    
    
    // lighting = pow(lighting, vec3(1.0f/2.2f));
    vec3 test = texture(ssao,TexCoords).rgb;
    FragColor = vec4(lighting, 1.0f);
}