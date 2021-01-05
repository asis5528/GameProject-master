//
// Created by sergio on 12/25/2020.
//

#ifndef MY_APPLICATION_PHYSICSMANAGER_H
#define MY_APPLICATION_PHYSICSMANAGER_H

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <glm/fwd.hpp>

class PhysicsManager {
public:
    btDiscreteDynamicsWorld *dynamicsWorld;
    void initPhysics();
    btRigidBody *setBoxCollision(float mass,glm::vec3 position,glm::vec3 rotation,glm::vec3 scale,glm::vec3 minBounds,glm::vec3 maxBounds);
    btVector3 getPosition(btRigidBody *rigidBody);
    void stepSimulation( );
    void addPosition(btRigidBody *rigidBody,glm::vec3 &position);
    void addX(btRigidBody *rigidBody,float val);
    void addY(btRigidBody *rigidBody,float val);
    void addZ(btRigidBody *rigidBody,float val);
};


#endif //MY_APPLICATION_PHYSICSMANAGER_H
