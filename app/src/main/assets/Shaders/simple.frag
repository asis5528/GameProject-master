#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 col;
in vec2 uv;
in vec3 normal;
in vec3 position;
uniform sampler2D tex;
void main()
{
    col = vec4(0.);
    FragColor = texture(tex,uv);
}

