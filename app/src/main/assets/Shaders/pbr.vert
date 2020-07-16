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

    pos = mat3(model)*aPos;
    position = mat3(model)*mat3(view)*aPos;
    gl_Position = proj*view*model*vec4(aPos,1.);


    uv = aUV;
    normal =normalize(mat3(transpose(inverse(model))) * aNor);}

