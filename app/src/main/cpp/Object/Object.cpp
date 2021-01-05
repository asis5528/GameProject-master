//
// Created by sergio on 7/14/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "../OpenGL/OpenGLMesh.h"
#include "../Animation/Animation.h"
#include <glm/glm.hpp>
#include "../Animation/Animator.h"
#define PI 3.1415926535
void Object::init(unsigned int primitiveIndex, std::string nam,Material &material) {
    primitiveID = primitiveIndex;
    name = nam;
    mat = material;



}
void Object::processAnimation(Mesh& Mesh, Animation& anim){
    Animation* data = &anim;
    glm::mat4 parent(1.0);
    //animator.actionIndex =1;
    float range = data->actions[animator.actionIndex].range.y - data->actions[animator.actionIndex].range.x;
    animator.time += 0.5;
    animator.time = fmod( animator.time, range);
    data->BoneTransform(animator);
    boneMatrices.clear();
    unsigned int j = 0;
    for (unsigned int i = 0; i < animator.AnimatedMatrices.size(); i++) {
        if (animator.AnimatedMatrices[i].name != Mesh.boneInfo[j].name) {
            //data->info.erase(data->info.begin() + i);


        }
        else {
            boneMatrices.push_back(animator.AnimatedMatrices[i].transformedBone);
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
void Object::updateTransformation(){
    glm::mat4 modelMatrix(1.0);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position[0], position[1], position[2]));
    modelMatrix = glm::rotate(modelMatrix, (float)(rotation[2] * (PI / 180)), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, (float)(rotation[1] * (PI / 180)), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix,(float)(rotation[0] *(PI / 180)), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, scale);
    transformationMatrix = modelMatrix;
}

void Object::Render(OpenGLMesh &mesh){

    mat.shad->use();




    mat.shad->setMat4("model",transformationMatrix);
    mesh.Render(*mat.shad);
}

