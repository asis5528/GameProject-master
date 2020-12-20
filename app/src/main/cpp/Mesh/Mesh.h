//
// Created by sergio on 7/13/2020.
//

#ifndef MY_APPLICATION_MESH_H
#define MY_APPLICATION_MESH_H
#include <GLES3/gl3.h>
#include "../glm/glm/glm.hpp"
#include "../../../../../../../Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/c++/v1/vector"
#include <vector>


struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normals;
    glm::vec3 TextureCoordinates;
};
struct BoneInfo{
    std::string name;
    glm::mat4 BoneOffset;
};
struct VertexBoneData
{
    unsigned int IDs[4] = { 0,0,0,0 };
    float Weights[4] = { 0.0,0.0,0.0,0.0 };

};
struct Texture{
    std::string name;
    unsigned int id;
    GLenum type = GL_TEXTURE_2D;
    unsigned int width;
    unsigned int height;
    GLenum format = GL_RGBA;
};
struct Mesh{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<VertexBoneData> bones;
    std::vector<BoneInfo> boneInfo;
    Mesh(){

    }
    Mesh(std::vector<Vertex> &vertices,std::vector<unsigned int> &indices,std::vector<VertexBoneData> &bones){
        this->vertices = vertices;
        this->indices = indices;
        this->bones = bones;
    }



};


#endif //MY_APPLICATION_MESH_H
