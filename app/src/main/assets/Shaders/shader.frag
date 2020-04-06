#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 uv;
in vec3 normal;
in vec3 pos;
uniform float time;

void main()
{

    FragColor = vec4(normal,1.0);
}

