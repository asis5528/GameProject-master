//
// Created by sergio on 7/13/2020.
//

#include "OpenGLMesh.h"



void OpenGLMesh::initVertices(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //We only have vertex position,normals and texture coordinate in Vertex Structure
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLMesh::initBones(std::vector<VertexBoneData> &bones) {
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, bones.size() * sizeof(VertexBoneData), &bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 4, GL_UNSIGNED_INT, sizeof(VertexBoneData), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (void*)16);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLMesh::init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices,std::vector<VertexBoneData> &bones) {
    indicesSize = indices.size();
    glGenVertexArrays(1, &VAO);
    initVertices(vertices,indices);
    //checking if any bones is there,if we will allocate vertex buffer for bone data
    if(bones.size()>0){
        initBones(bones);
    }
    //unbinding vao
    glBindVertexArray(0);
}
void OpenGLMesh::init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) {
    indicesSize = indices.size();
    glGenVertexArrays(1, &VAO);
    initVertices(vertices,indices);
    //unbinding vao
    glBindVertexArray(0);
}
void OpenGLMesh::Render(Shader &shader) {

    // draw our first triangle
    //  glUseProgram(shaderProgram);
    shader.use();
    glBindVertexArray(VAO); //seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

}