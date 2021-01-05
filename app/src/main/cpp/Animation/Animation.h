//
// Created by sergio on 9/20/2020.
//

#ifndef MY_APPLICATION_ANIMATION_H
#define MY_APPLICATION_ANIMATION_H


#include "AnimationData.h"
#include "Animator.h"

struct AnimationAction {
    std::string name;
    glm::vec2 range;
    float speed = 1.0;
    float timer = 0.0;
    unsigned int playMode = 0;
    float incremationDirection = 1.0;
};
class Animation {
public:
    float duration;
    float ticksperSec;
    AnimationData adata;
    std::vector<AnimationAction> actions;
    std::string name;



    float fps = 30.;


    float timee = 0.;

    void initAction();
    void BoneTransform(Animator &animator);
    void applyTransformation(Animator &animator,glm::mat4 transformationMatrix);
    void applyBonesTransformation(AnimationData &data,const glm::mat4 Parentmatrix,Animator &animator,const glm::mat4 transformationMatrix);
    void readAnimation(float time, float time2,AnimationData& data, const glm::mat4& Parentmatrix,Animator &animator);//put this private in future
    void CalcInterpolatedRotation(glm::quat& Out, float AnimationTime, AnimationData& data);//put this private in future
    void CalcInterpolatedPosition(glm::vec3& Out, float AnimationTime, AnimationData& data);//put this private in future
    unsigned int FindScale(float AnimationTime, AnimationData& data);
    unsigned int FindPosition(float AnimationTime, AnimationData& data);
    unsigned int FindRotation(float AnimationTime, AnimationData& data);



private:


};


#endif //MY_APPLICATION_ANIMATION_H
