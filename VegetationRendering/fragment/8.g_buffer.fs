#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

// const float NEAR = 0.1; // 投影矩阵的近平面
// const float FAR = 50.0f; // 投影矩阵的远平面
// float LinearizeDepth(float depth)
// {
//     float z = depth * 2.0 - 1.0; // 回到NDC
//     return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));    
// }

void main()
{
	// store the fragment position vector in the first gbuffer texture
	gPosition = FragPos;
	// gPosition.a = LinearizeDepth(gl_FragCoord.z);
	// also store the per-fragment normals into the gbuffer
	gNormal = normalize(Normal);
	// and the diffuse per-fragment color
	gAlbedoSpec.rgb = texture(texture_diffuse, TexCoords).rgb;
	// // store specular intensity in gAlbedoSpec's alpha component
	gAlbedoSpec.a = texture(texture_specular, TexCoords).r;
	//gAlbedoSpec = vec3(0.95f);
}