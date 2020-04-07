#version 300 es
precision mediump float;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aUV;
out vec2 uv;
out vec3 normal;
out vec3 position;
out vec3 pos;
uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;
void main()
{
    vec3 v = aPos;
    normal =mat3(transpose(inverse(model))) * aNor;
    pos = vec3(model*vec4(v,1.0));
    position = vec3(view*vec4(pos,1.));
    vec4 modelView = proj*vec4(position,1.);
    gl_Position = modelView;


    uv = aUV;}

