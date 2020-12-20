#version 300 es
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 modelMatPos;
in vec4 weight;
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
    metallic = metalness;
    float roughnessVal = texture(roughnessTexture, TexCoords).r;
    roughnessVal = roughness;
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(envMap, R,roughnessVal).rgb;

    vec3 irradiance = texture(IrradianceTexture, N).rgb;
    vec3 spec = texture(IrradianceTexture, R).rgb;
    vec3 diffuse   = irradiance * diffuseTexture.rgb;
    vec3 finalCol = mix(diffuse+spec*0.4,prefilteredColor,metallic);
  //  FragColor = vec4(texture(DiffuseTexture,TexCoords));
    FragColor = vec4(finalCol,1.);
FragColor=weight;
}