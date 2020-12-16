//
// Created by sergio on 9/5/2020.
//

#ifndef MY_APPLICATION_ANIMATIONDATA_H
#define MY_APPLICATION_ANIMATIONDATA_H


#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>
#include <vector>
#include <string>

struct KeyFrameTransformation{
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    float time;


};
class AnimationData {
public:
    void readAnimation(float time,AnimationData &data,glm::mat4 &parentMatrix);

private:
    std::string name;
    std::vector<KeyFrameTransformation> animationTransformation;
    float duration;
    float tickperSec;
    glm::mat4 boneOffset;
    std::vector<glm::mat4> outMatrices;
    bool anim = false;
    std::vector<AnimationData> childAnimationData;



    void CalcInterpolatedPosition(glm::vec3 &Out,float AnimationTime,AnimationData& data);
    void CalcInterpolatedScale(glm::vec3 &Out,float AnimationTime,AnimationData& data);
    void CalcInterpolatedRotation(glm::vec3 &Out,float AnimationTime,AnimationData& data);
    unsigned int FindKeyFrameIndex(float AnimationTime,AnimationData &data);


};


#endif //MY_APPLICATION_ANIMATIONDATA_H
