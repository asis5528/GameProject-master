//
// Created by sergio on 7/14/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "../OpenGL/OpenGLMesh.h"
#include <glm/glm.hpp>
#define PI 3.1415926535
void Object::init(unsigned int primitiveIndex, std::string nam,Material &material) {
    primitiveID = primitiveIndex;
    name = nam;
    mat = material;

}

void Object::Render(OpenGLMesh &mesh){
    mat.shad->use();
    glm::mat4 modelMatrix(1.0);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position[0], position[1], position[2]));
    modelMatrix = glm::rotate(modelMatrix, (float)(rotation[2] * (PI / 180)), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, (float)(rotation[1] * (PI / 180)), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix,(float)(rotation[0] *(PI / 180)), glm::vec3(1, 0, 0));


    modelMatrix = glm::scale(modelMatrix, scale);
    mat.shad->setMat4("model",modelMatrix);
    mesh.Render(*mat.shad);
}

