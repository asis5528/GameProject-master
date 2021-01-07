//
// Created by sergio on 1/5/2021.
//

#ifndef MY_APPLICATION_CHARACTER_H
#define MY_APPLICATION_CHARACTER_H


#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "../Object/Object.h"
#include "../Physics/PhysicsManager.h"

class Character {
public:
    Object *object;
    btRigidBody *rigidBody;
    glm::mat4 modelMatrix;
    Character(Object *object,PhysicsManager *physicsManager,Mesh &mesh);
    float WalkSpeed = 0.05;
    float RunSpeed = 0.2;
    void IdlePose();
    void blendAction();
    void lookLeft();
    void lookRight();
    void walkLeft();
    void walkRight();
    void RunLeft();
    void RunRight();
    void aim();
    void Jump();
    void UpdateTransformation();

};


#endif //MY_APPLICATION_CHARACTER_H
