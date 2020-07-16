#version 300 es
layout (location = 0) in vec3 aPos;
layout(location = 1)in vec3 normals;
layout(location = 2)in vec2 tc;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec2 uv;

void main()
{
    uv = tc;
    gl_Position = projection*view*model*vec4(aPos.x ,aPos.y, aPos.z, 1.0);
}