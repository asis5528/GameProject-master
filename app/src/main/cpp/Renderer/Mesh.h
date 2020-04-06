//
// Created by sergio on 3/23/2020.
//

#ifndef MY_APPLICATION_MESH_H
#define MY_APPLICATION_MESH_H


using namespace std;
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;

};
class Mesh{
public:
    vector<Vertex> vertices;
    vector<GLushort> indices;
    unsigned int VAO;
    Mesh(vector<Vertex> vertices,vector<GLushort> indices){
        this->vertices = vertices;
        this->indices = indices;
        setupMesh();
    }
    Mesh(){

    }
    void draw(Shader shader){
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,0);

    }

private:
    unsigned int VBO,EBO;
    void setupMesh(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, model.size()*sizeof(objl::Vertex), &model[0], GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*loader.LoadedIndices.size(), &loader.LoadedIndices[0], GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*indices.size(),&indices[0],GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6* sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}

};




#endif //MY_APPLICATION_MESH_H
