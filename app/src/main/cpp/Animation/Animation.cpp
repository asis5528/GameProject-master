//
// Created by sergio on 9/20/2020.
//

#include <glm/ext/quaternion_common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <android/log.h>
#include "Animation.h"
#include "Animator.h"
#include "../Inputs/Touch.h"

void Animation::initAction() {
    AnimationAction defaultAction;
    defaultAction.name = "defaultAction";
    defaultAction.range = glm::vec2(0.0, duration);
    actions.push_back(defaultAction);
    /*
    defaultAction.name = "idle";
    defaultAction.range = glm::vec2(0.0, 35);
    actions.push_back(defaultAction);
    defaultAction.name = "walk";
    defaultAction.range = glm::vec2(263, 287.5);
    actions.push_back(defaultAction);
    defaultAction.name = "run";
    defaultAction.range = glm::vec2(289, 298.0);
    actions.push_back(defaultAction);
    defaultAction.name = "idle2";
    defaultAction.range = glm::vec2(81, 149.0);
    actions.push_back(defaultAction);
    */
    defaultAction.name = "walk";
    defaultAction.range = glm::vec2(259, 290.0);
    actions.push_back(defaultAction);
    defaultAction.name = "run";
    defaultAction.range = glm::vec2(294, 316.0);
    actions.push_back(defaultAction);

    defaultAction.name = "hook";
    defaultAction.range = glm::vec2(319, 359.0);
    actions.push_back(defaultAction);

    defaultAction.name = "box";
    defaultAction.range = glm::vec2(374, 439.0);
    actions.push_back(defaultAction);

    defaultAction.name = "dance";
    defaultAction.range = glm::vec2(445, 914.0);
    actions.push_back(defaultAction);
}

void Animation::BoneTransform(Animator &animator) {
    glm::mat4 identity(1.0);
 //   actionIndex = act1Index;
   // blendAction = act2Index;
  //  Blendfactor = blend;
    float range = actions[animator.actionIndex].range.y - actions[animator.actionIndex].range.x;
    float range2 = actions[animator.blendAction].range.y - actions[animator.blendAction].range.x;
    if(animator.Blendfactor <0.001){
        actions[animator.blendAction].timer = 0.0;
    }
    //actions[animator.actionIndex].timer = fmod(animator.time, range);
    actions[animator.actionIndex].timer+=0.5*actions[animator.actionIndex].incremationDirection;
    actions[animator.blendAction].timer +=0.5*actions[animator.blendAction].incremationDirection;
    if( actions[animator.actionIndex].playMode==0){
        actions[animator.actionIndex].timer = fmod( actions[animator.actionIndex].timer, range);
    }else if(actions[animator.actionIndex].playMode==1){
        if(abs(actions[animator.actionIndex].timer-range)<0.001){
            actions[animator.actionIndex].incremationDirection = -1.0;
        }else if(actions[animator.actionIndex].timer<0){
            actions[animator.actionIndex].incremationDirection = 1.0;
        }
    }
    if( actions[animator.blendAction].playMode==0){
        actions[animator.blendAction].timer = fmod( actions[animator.blendAction].timer, range2);
    }else if(actions[animator.blendAction].playMode==1){
        if(abs(actions[animator.blendAction].timer-range2)<1.001){
            actions[animator.blendAction].incremationDirection = 0.0;
        }else if(actions[animator.blendAction].timer<1){
            actions[animator.blendAction].incremationDirection = 1.0;
        }
    }
    animator.AnimatedMatrices.clear();
    readAnimation((actions[animator.actionIndex].timer + actions[animator.actionIndex].range.x),(actions[animator.blendAction].timer + actions[animator.blendAction].range.x), adata.childAnimationData[0],identity,animator);
}

void Animation::applyTransformation(Animator &animator,glm::mat4 transformation) {

}
void Animation::readAnimation(float time, float time2,AnimationData& data, const glm::mat4& Parentmatrix,Animator &animator) {
    glm::mat4 globalMatrix(1.0);
        float n =duration - data.animationTransformation.at(0).time;
        time += data.animationTransformation.at(0).time;
        time2+= data.animationTransformation.at(0).time;

        glm::vec3 pos;
        CalcInterpolatedPosition(pos, time, data);
        glm::vec3 pos2;
        CalcInterpolatedPosition(pos2, time2, data);


        pos = data.animationTransformation[0].position;
        //pos = data.animationTransformation[0].position;
        glm::vec3 sc = data.animationTransformation[0].scale;
        glm::mat4 trans(1.0);
        glm::mat4 scale(1.0);
        glm::quat q;
        CalcInterpolatedRotation(q, time, data);
        glm::quat q2;
        CalcInterpolatedRotation(q2, time2, data);
        glm::quat fina = glm::slerp(q, q2, animator.Blendfactor);
        fina = glm::normalize(fina);
        glm::mat4 rotmat = glm::toMat4(fina);
        if(data.name==animator.boneName){

            rotmat = animator.TransformationMatrix*rotmat;

        }
        trans = glm::translate(trans, glm::vec3(pos.x, pos.y, pos.z));
        scale = glm::scale(scale, glm::vec3(sc.x, sc.y, sc.z));
        rotmat = trans * rotmat * scale;
        globalMatrix = Parentmatrix * rotmat;
        //	Parentmatrix = rotmat;
        BoneProcessedMat boneInfo;
        boneInfo.name = data.name;
        boneInfo.transformedBone = globalMatrix;
        animator.AnimatedMatrices.push_back(boneInfo);


    for (int i = 0; i < data.childAnimationData.size(); i++) {

        readAnimation(time,time2, data.childAnimationData[i], globalMatrix,animator);
    }
    //	std::cout << "Time  " << AnimationTime << "\n";
}

void Animation::CalcInterpolatedRotation(glm::quat& Out, float AnimationTime, AnimationData& data)
{
    // we need at least two values to interpolate...
    float size = data.animationTransformation.size();
    if (data.animationTransformation.size() == 1) {
        Out = data.animationTransformation[0].rotation;
        return;
    }

    unsigned int RotationIndex = Animation::FindRotation(AnimationTime, data);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < size);
    float DeltaTime = (float)(data.animationTransformation[NextRotationIndex].time - data.animationTransformation[RotationIndex].time);
    float Factor = (AnimationTime - (float)data.animationTransformation[RotationIndex].time) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const glm::quat& StartRotationQ = data.animationTransformation[RotationIndex].rotation;
    const  glm::quat& EndRotationQ = data.animationTransformation[NextRotationIndex].rotation;
    //std::cout << "start: " << RotationIndex << "\n";
    //std::cout << "next: " << NextRotationIndex << "\n";
    glm::quat q1;
    q1.w = StartRotationQ.w; q1.x = StartRotationQ.x; q1.y = StartRotationQ.y; q1.z = StartRotationQ.z;
    glm::quat q2;
    q2.w = EndRotationQ.w; q2.x = EndRotationQ.x; q2.y = EndRotationQ.y; q2.z = EndRotationQ.z;
    //std::cout << "k  " << q1.w << "\n";
    glm::quat fina = glm::slerp(q1, q2, Factor);

    fina = glm::normalize(fina);
    //aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    //Out = Out.Normalize();
    Out = fina;
}

void Animation::CalcInterpolatedPosition(glm::vec3& Out, float AnimationTime, AnimationData& data)
{
    // we need at least two values to interpolate...
    int size = data.animationTransformation.size();
    if (data.animationTransformation.size() == 1) {
        Out = data.animationTransformation[0].position;
        return;
    }

    unsigned int PositionIndex = Animation::FindPosition(AnimationTime, data);

    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < size);
    float DeltaTime = (float)(data.animationTransformation[NextPositionIndex].time - data.animationTransformation[PositionIndex].time);
    float Factor = (AnimationTime - (float)data.animationTransformation[PositionIndex].time) / DeltaTime;

    assert(Factor >= 0.0f && Factor <= 1.0f);
    const glm::vec3 start = data.animationTransformation[PositionIndex].position;
    const  glm::vec3 End = data.animationTransformation[NextPositionIndex].position;
    glm::vec3 Delta = End - start;
    Out = start + Factor * Delta;
}
unsigned int Animation::FindRotation(float AnimationTime, AnimationData& data)
{
    assert(data.animationTransformation.size() > 0);
    //std::cout << "animationData: " << AnimationTime << "\n";
    for (unsigned int i = 0; i < data.animationTransformation.size() - 1; i++) {
        if (AnimationTime < (float)data.animationTransformation[i + 1].time) {

            return i;
        }
    }
    //std::cout << "animationData: " << AnimationTime << "\n";
    assert(0);
    return 0;
}

unsigned int Animation::FindPosition(float AnimationTime, AnimationData& data)
{
    assert(data.animationTransformation.size() > 0);

    for (unsigned int i = 0; i < data.animationTransformation.size() - 1; i++) {
        if (AnimationTime < (float)data.animationTransformation[i + 1].time) {

            return i;
        }
    }
    //std::cout << "animationData: " << AnimationTime << "\n";
    assert(0);
    return 0;
}

unsigned int Animation::FindScale(float AnimationTime, AnimationData& data)
{
    assert(data.animationTransformation.size() > 0);

    for (unsigned int i = 0; i < data.animationTransformation.size() - 1; i++) {
        if (AnimationTime < (float)data.animationTransformation[i + 1].time) {

            return i;
        }
    }
    //std::cout << "animationData: " << AnimationTime << "\n";
    assert(0);

    return 0;
}