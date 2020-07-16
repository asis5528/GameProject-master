#version 300 es


precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
layout (location = 2) out vec4 positionColor;
layout (location = 3) out vec4 normalColor;
in vec2 uv;
in vec3 normal;
in vec3 position;
in vec3 pos;
uniform samplerCube tex0;
uniform sampler2D tex1;
uniform vec3 cameraPos;
uniform float timer;
uniform float metalness;
uniform float roughness;
uniform vec3 diffuse;
void main()
{
    normalColor.rgb = normal;
    positionColor.rgb = position;
    col=vec4( 0.0);
    vec3 I = normalize(pos - cameraPos);
    vec3 N =  normalize(normal);

    vec3 lightPos = vec3(5.0,0.4,5.0);
    vec3 lightDir = normalize(lightPos - pos);


    vec3 reflectDir = reflect(-lightDir, N);
    vec3 directDiffuse = vec3(clamp(dot(N,lightPos),0.,1.))+0.3;
    vec3 albedo = mix(vec3(0.0),texture(tex1,uv).rgb+diffuse,1.-metalness);

    vec3 indirectDiffuse = textureLod(tex0,N,25.0).rgb;

    vec3 diff =albedo* (indirectDiffuse);

    vec3 color =  (pow(smoothstep(0.0, 2.0,  dot(I, N)+1.), 1.25))*vec3(1.0)+0.5;

    vec3 R = reflect(-I,N);

    vec3 indirectSpecular;

    indirectSpecular  = textureLod(tex0,R,roughness*6.0).rgb*metalness;

    vec3 finalCol = diff+indirectSpecular;
    if(metalness<0.2){
        FragColor = vec4(color*albedo,1.);
       // FragColor = vec4(0.0);
    }
   else{
        float line = smoothstep(0.5,0.8,fract(pos.x)*2.);
        vec3 cco = finalCol;

       FragColor = vec4(cco,1.);
       // FragColor = vec4(textureLod(tex0,N,5.0).rgb,1.);
    }
}

