#version 300 es
precision mediump float;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aUV;
out vec2 uv;
out vec3 normal;

uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;
void main()
{
    vec3 v = aPos;
    vec4 modelView = proj*view*model*vec4(v,1.0)*2.;
    gl_Position = modelView;
    normal = aNor;
    uv = aUV;}

