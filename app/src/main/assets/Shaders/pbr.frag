#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
in vec2 uv;
in vec3 normal;
in vec3 position;
in vec3 pos;
uniform samplerCube tex0;
uniform sampler2D tex1;
uniform vec3 cameraPos;
void main()
{
    vec3 P = vec3(position);
    vec3 V = normalize(-P);
    vec3 I = normalize(pos - cameraPos);
    vec3 N =  normalize(normal);
    vec4 color = pow(smoothstep(0.0, 1.0, 1.0 - dot(N, V)), 1.25)*vec4(0.5);
    float k = 1.-dot(N, V);
    vec3 R = reflect(I,N);
    float mask = texture(tex1,uv).x;

    vec3 ref;

    if(mask<0.1){
        ref = texture(tex0,R,4.).rgb;
    }else{
        ref = texture(tex0,R,0.0).rgb;
    }
    vec3 finalCol = ref+color.xyz*0.1;
    finalCol = clamp(finalCol,0.,1.);
    ///finalCol*=0.8;
    if((finalCol.x+finalCol.y+finalCol.z)/3.>0.9){
        col = vec4(finalCol,1.);
    }else{
        col = vec4(0.);
    }

    FragColor = vec4(finalCol,1.);
}

