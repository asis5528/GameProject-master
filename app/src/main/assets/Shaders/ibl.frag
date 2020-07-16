#version 300 es
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 modelMatPos;

uniform bool bloom;
uniform bool BloomTexture;

uniform sampler2D DiffuseTexture;
uniform sampler2D glossyTexture;
uniform sampler2D roughnessTexture;
uniform sampler2D GlowTexture;
uniform samplerCube envMap;
uniform samplerCube IrradianceTexture;



uniform vec4 objectColor;
uniform vec3 camPos;
uniform float roughness;
uniform float metalness;









void main()
{


    vec3 N = normalize(normal);
    vec3 V = normalize(camPos-modelMatPos);
    vec3 R = reflect(-V,normalize(N));

    vec4 diffuseTexture = texture(DiffuseTexture,TexCoords);
    float metallic = texture(glossyTexture,TexCoords).r;
    float roughnessVal = texture(roughnessTexture, TexCoords).r;
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(envMap, R,2.).rgb;

    vec3 irradiance = texture(IrradianceTexture, N).rgb;
    vec3 diffuse   = irradiance * diffuseTexture.rgb;
    vec3 finalCol = mix(diffuse,prefilteredColor,metallic);
    FragColor = vec4(texture(DiffuseTexture,TexCoords));

}