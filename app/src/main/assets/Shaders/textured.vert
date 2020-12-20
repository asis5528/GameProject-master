#version 300 es
layout (location = 0) in vec3 aPos;
layout(location = 1)in vec3 normals;
layout(location = 2)in vec2 tc;
layout (location = 3) in ivec4 boneID;
layout (location = 4) in vec4 boneWeight;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 boneMat[100];
uniform bool hasAnimation;
out vec2 uv;
out vec4 weight;

void main()
{

    weight = vec4(boneWeight);
    uv = tc;
    vec4 PosL;
    PosL =vec4(aPos, 1.0);
    if(hasAnimation){

        mat4 BoneTransform = boneMat[boneID[0]] * boneWeight[0];
        BoneTransform += boneMat[boneID[1]] * boneWeight[1];
        BoneTransform += boneMat[boneID[2]] * boneWeight[2];
        BoneTransform += boneMat[boneID[3]] * boneWeight[3];
        PosL =BoneTransform* vec4(aPos, 1.0);
    }else{
        PosL =vec4(aPos, 1.0);
    }
    gl_Position = projection*view*model*PosL;
}