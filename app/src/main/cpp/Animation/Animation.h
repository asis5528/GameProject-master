//
// Created by sergio on 9/20/2020.
//

#ifndef MY_APPLICATION_ANIMATION_H
#define MY_APPLICATION_ANIMATION_H


#include "AnimationData.h"
struct BoneProcessedMat {
    std::string name;
    glm::mat4 transformedBone;
};
struct AnimationAction {
    std::string name;
    glm::vec2 range;
    float speed = 1.0;
    float timer = 0.0;
};
class Animation {
public:
    float duration;
    float ticksperSec;
    AnimationData adata;
    std::vector<AnimationAction> actions;
    std::string name;
    std::vector<BoneProcessedMat> info;
    unsigned int actionIndex = 0;
    bool animPlay = false;
    float fps = 30.;
    float Blendfactor;
    unsigned int blendAction = 2;
    float timee = 0.;

    void initAction();
    void BoneTransform(float &time,unsigned int act1Index,unsigned int act2Index,float blend);
    void readAnimation(float time, AnimationData& data, const glm::mat4& Parentmatrix);//put this private in future
    void CalcInterpolatedRotation(glm::quat& Out, float AnimationTime, AnimationData& data);//put this private in future
    void CalcInterpolatedPosition(glm::vec3& Out, float AnimationTime, AnimationData& data);//put this private in future
    unsigned int FindScale(float AnimationTime, AnimationData& data);
    unsigned int FindPosition(float AnimationTime, AnimationData& data);
    unsigned int FindRotation(float AnimationTime, AnimationData& data);


private:


};


#endif //MY_APPLICATION_ANIMATION_H
