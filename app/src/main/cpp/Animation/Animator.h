//
// Created by sergio on 12/23/2020.
//

#ifndef MY_APPLICATION_ANIMATOR_H
#define MY_APPLICATION_ANIMATOR_H



struct BoneProcessedMat {
    std::string name;
    glm::mat4 transformedBone;
};
struct Animator{
std::vector<BoneProcessedMat> AnimatedMatrices;
    unsigned int actionIndex = 1;
    float Blendfactor=0.0;
    unsigned int blendAction = 2;
    float time =0.0;
    glm::mat4 TransformationMatrix = glm::mat4(1.0);
    std::string boneName;
};
#endif //MY_APPLICATION_ANIMATOR_H
