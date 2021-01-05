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

struct Mesh{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<VertexBoneData> bones;
    std::vector<BoneInfo> boneInfo;
    glm::vec3 minBounds;
    glm::vec3 maxBounds;
    Mesh(){

    }
    Mesh(std::vector<Vertex> &vertices,std::vector<unsigned int> &indices,std::vector<VertexBoneData> &bones){
        this->vertices = vertices;
        this->indices = indices;
        this->bones = bones;
    }
    void disposeVertices(){
        vertices.clear();
    }
    void disposeAll(){
        vertices.clear();
        indices.clear();
        bones.clear();
        boneInfo.clear();
    }
    void disposeMesh(){
        vertices.clear();
        indices.clear();
    }
    void disposeBone(){
        bones.clear();
        boneInfo.clear();
    }


};


#endif //MY_APPLICATION_MESH_H
