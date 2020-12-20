//
// Created by sergio on 7/14/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "../OpenGL/OpenGLMesh.h"
#include "../Animation/Animation.h"
#include <glm/glm.hpp>
#define PI 3.1415926535
void Object::init(unsigned int primitiveIndex, std::string nam,Material &material) {
    primitiveID = primitiveIndex;
    name = nam;
    mat = material;

}
void Object::processAnimation(Mesh& Mesh, Animation& anim){
    Animation* data = &anim;
    glm::mat4 parent(1.0);

    float range = data->actions[data->actionIndex].range.y - data->actions[data->actionIndex].range.x;
    animationTime += 0.5;
    animationTime = fmod(animationTime, range);
    data->BoneTransform(animationTime, 1, 2, 0.0);
    boneMatrices.clear();
    unsigned int j = 0;
    for (unsigned int i = 0; i < data->info.size(); i++) {
        if (data->info[i].name != Mesh.boneInfo[j].name) {
            //data->info.erase(data->info.begin() + i);


        }
        else {
            boneMatrices.push_back(data->info[i].transformedBone);
            j += 1;
            if (j > Mesh.boneInfo.size() - 1) {
                break;
            }
        }

    }
    mat.shad->setBool("hasAnimation", boneMatrices.size() > 0);
    if (data->adata.childAnimationData.size() > 0) {
        for (int i = 0; i < boneMatrices.size(); i++) {
            std::string loc = std::string("boneMat[") + std::to_string(i) + std::string("]");

            mat.shad->setMat4(loc, boneMatrices[i] * Mesh.boneInfo[i].BoneOffset);

        }
    }
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

