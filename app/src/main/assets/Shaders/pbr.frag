#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
in vec2 uv;
in vec3 normal;
in vec3 position;
in vec3 pos;
uniform samplerCube tex;
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
    vec3 ref = texture(tex,R).rgb;
    col = vec4(0.);

    FragColor = vec4(ref+color.xyz*0.1,1.);
}

