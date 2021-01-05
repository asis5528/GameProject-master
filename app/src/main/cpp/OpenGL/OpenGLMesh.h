//
// Created by sergio on 7/13/2020.
//

#ifndef MY_APPLICATION_OPENGLMESH_H
#define MY_APPLICATION_OPENGLMESH_H


#include <vector>
#include "../shader_manager.h"
#include "../Mesh/Mesh.h"
class OpenGLMesh {
public:
    void init(std::vector<Vertex> &vertex,std::vector<unsigned  int> &indices,std::vector<VertexBoneData> &bones);
    void init(std::vector<Vertex> &vertex,std::vector<unsigned  int> &indices);
    void initVertices(std::vector<Vertex> &vertices,std::vector<unsigned  int> &indices);
    void initBones(std::vector<VertexBoneData> &bones);
    void Render(Shader &shader);

private:
    unsigned int indicesSize;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;


};


#endif //MY_APPLICATION_OPENGLMESH_H
