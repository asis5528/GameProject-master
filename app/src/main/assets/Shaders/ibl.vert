#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec4 boneID;
layout (location = 4) in vec4 boneWeight;

out vec2 TexCoords;
out vec3 normal;
out vec3 modelMatPos;
out vec4 weight;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    weight = boneWeight;
    normal = mat3(model) *aNormal;
    TexCoords = aTexCoords;
    modelMatPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
