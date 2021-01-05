#version 300 es
precision mediump float;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
out vec2 uv;
uniform vec2 pos;


void main()
{

    uv = aUV;
    gl_Position = vec4(aPos.x+pos.x,aPos.y+pos.y,0.0,1.0);
}

