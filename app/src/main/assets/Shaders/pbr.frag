#version 300 es
#define GLOSSY_MIP_COUNT 6

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
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform vec3 cameraPos;
uniform float timer;
uniform float metalness;
uniform float roughness;
uniform vec3 diffuse;
void main()
{


    float l = texture(tex2,uv).x;

    float lightIntensity = 1.5;

    normalColor.rgb = normal;
    positionColor.rgb = pos;

    vec3 mask = texture(tex1,uv).xyz;
    mask.g =mask.r;
    mask.b = mask.r;
    col=vec4(mask,1.)*2.0;
    //if(length(mask))
    vec3 P = vec3(position);
    vec3 N =  normalize(normal);
    vec3 V = normalize(-P);

    vec3 I = normalize(pos - cameraPos);
    vec3 lightPos = vec3(5.0,0.4,0.0);
    vec3 lightDir = normalize(lightPos - pos);


    vec3 reflectDir = reflect(-lightDir, N);
    vec3 directDiffuse = vec3(clamp(dot(N,lightPos),0.,1.));
    directDiffuse+=1.;
    directDiffuse*=lightIntensity;
    vec3 albedo = mix(vec3(0.0),texture(tex3,uv).rgb+diffuse,1.-metalness);
    vec3 indirectDiffuse = textureLod(tex0,N,5.0).rgb;
    vec3 diffuse =albedo* (indirectDiffuse);
    float spec = pow(max(dot(I, reflectDir), 0.0), 532.);
    //spec*=metalness;

    vec3 color =  (pow(smoothstep(0.0, 2.0,  dot(I, N)+1.), 1.25))*vec3(1.0)+0.5;

    float k = dot(I, N);
    k+=1.;

    k = clamp(k,0.,1.);
    vec3 R = reflect(-I,N);
   // R.y=-1.-R.y;

   //diffu
   // diffuse+=mask;

   // mask = 1.0;




    vec3 indirectSpecular;

    if(mask.x<0.1){
        indirectSpecular  = textureLod(tex0,R,roughness*6.0).rgb*metalness;
    }
    if(roughness>0.5){
        FragColor.rgb = mix(color,textureLod(tex0,R,4.0).rgb*(1.-mask.x),0.5)+mask;
        return;
    }

    vec3 finalCol = color*(diffuse+indirectSpecular)*vec3(1.,1.,0.);




//vec3 finalCol = (color.xyz)*ref*1.+mask;

//col*=0.;

    //finalCol = mix(vec3(0.0),finalCol,0.5);
    if((mask.x+mask.y+mask.z)>0.1){
        finalCol *=0.0;
    }
    FragColor = vec4(finalCol+mask,1.);
  //  FragColor = vec4(indirectDiffuse,1.);
}

