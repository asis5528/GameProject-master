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

struct AnimationTransformation{
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    float time;


};
class AnimationData {
public:
    std::string name;
    std::vector<AnimationTransformation> animationTransformation;
    std::vector<AnimationData> childAnimationData;
    unsigned int index;

private:



};


#endif //MY_APPLICATION_ANIMATIONDATA_H
