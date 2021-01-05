#version 300 es
precision mediump float;
layout (location = 0) out vec4 FragColor;

in vec2 uv;
uniform vec4 color;
uniform sampler2D tex;
void main()
{
    FragColor = texture(tex,uv);
    FragColor = vec4(1.,0.,0.,1.);
}

