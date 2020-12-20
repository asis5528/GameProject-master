//
// Created by sergio on 9/5/2020.
//
/*
#include "AnimationData.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
void AnimationData::readAnimation(float time, AnimationData &data, glm::mat4 &parentMatrix) {
    glm::mat4 globalMatrix(1.0);
    if (data.name != "") {

        float TicksPerSecond = (float) (tickperSec != 0 ? tickperSec : 25.0f);
        float TimeInTicks = time * TicksPerSecond;
        float AnimationTime = fmod(TimeInTicks,
                                   data.duration - data.animationTransformation[1].time);
        AnimationTime += data.animationTransformation[1].time;
        glm::vec3 pos;
        CalcInterpolatedPosition(pos,AnimationTime,data);

        //pos = data.animationTransformation[0].position;

        glm::vec3 scale;
        scale = data.animationTransformation[0].scale;

        glm::quat rotation;
        rotation = data.animationTransformation[0].rotation;

        glm::mat4 TranslationMat(1.0);
        glm::mat4 ScaleMat(1.0);
        glm::mat4 RotationMat(1.0);

        TranslationMat = glm::translate(TranslationMat,pos);
        RotationMat = glm::toMat4(rotation);
        ScaleMat = glm::scale(ScaleMat,scale);

        RotationMat = TranslationMat*RotationMat*ScaleMat;
        globalMatrix = parentMatrix*RotationMat;
        if(data.anim){
            outMatrices.push_back(globalMatrix*data.boneOffset);
        }

    for(int i = 0;i<data.childAnimationData.size();i++){
        readAnimation(time,data.childAnimationData[i],globalMatrix);
    }
// CalcInterpolatedPosition(pos, AnimationTime, data);


    }
}
void AnimationData::CalcInterpolatedPosition(glm::vec3 &Out,float AnimationTime,AnimationData& data){
        float size = data.animationTransformation.size();
        if(size==1){
            Out = data.animationTransformation[0].position;
            return;
        }
        unsigned int PositionIndex = FindKeyFrameIndex(AnimationTime,data);
        unsigned int NextPositionIndex = PositionIndex+1;
        float DeltaTime = data.animationTransformation[NextPositionIndex].time-data.animationTransformation[PositionIndex].time;
        float Factor = (AnimationTime-data.animationTransformation[PositionIndex].time)/DeltaTime;
        glm::vec3 start = data.animationTransformation[PositionIndex].position;
        glm::vec3 end = data.animationTransformation[NextPositionIndex].position;
        glm::vec3 Delta = end-start;
        Out = start+Factor*Delta;

 }
 void AnimationData::CalcInterpolatedRotation(glm::vec3 &Out, float AnimationTime,
                                              AnimationData &data) {


}

void AnimationData::CalcInterpolatedScale(glm::vec3 &Out, float AnimationTime,
                                             AnimationData &data) {


}


 unsigned int AnimationData::FindKeyFrameIndex(float AnimationTime,AnimationData &data){
    for(unsigned int i = 0;i<data.animationTransformation.size()-1;i++){
        if(AnimationTime<data.animationTransformation[i+1].time){
            return  i;
        }
    }



}



*/


