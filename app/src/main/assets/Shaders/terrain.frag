#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
in vec2 uv;
in vec3 normal;
uniform sampler2D tex;

void main()
{
    vec2 st = uv-0.5;
    float k= smoothstep(0.2,0.18,length(st));
    k-=smoothstep(0.19,0.17,length(st));
    k = clamp(k,0.,1.);
    col = vec4(k);
    FragColor = vec4(1.,0.,0.,1.);
}

