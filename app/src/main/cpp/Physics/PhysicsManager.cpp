//
// Created by sergio on 12/25/2020.
//
#include <BulletCollision/BroadphaseCollision/btBroadphaseInterface.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include <glm/detail/type_vec2.hpp>
#include <glm/glm.hpp>
#include <android/log.h>
#include "PhysicsManager.h"
#define PI 3.1415926535
void PhysicsManager::initPhysics() {

    btBroadphaseInterface *broadphase =  new btDbvtBroadphase();
    btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher *dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-9.8,0));
    //b = setBoxCollision(0.0,btVector3(0,0,0),btVector3(0,0,0),btVector3(100,2,100.));


}

btRigidBody *PhysicsManager::setBoxCollision(float mass,glm::vec3 position,glm::vec3 rotation,glm::vec3 scale,glm::vec3 minBounds,glm::vec3 maxBounds){

    glm::vec3 Dimensions = (maxBounds*scale)-(minBounds*scale);
    glm::vec3 offset = (glm::abs(maxBounds*scale)-glm::abs(minBounds*scale))/glm::vec3(2.0);
    btCollisionShape *boxShape = new btBoxShape(btVector3(Dimensions.x/2.,Dimensions.y/2.,Dimensions.z/2.));
    btQuaternion rot;
    rot.setEulerZYX(rotation.z* (PI / 180),rotation.y* (PI / 180),rotation.x* (PI / 180));
    btTransform transform;
    transform.setOrigin(btVector3(position.x,position.y,position.z));
    transform.setRotation(rot);
    btMotionState *motionState = new btDefaultMotionState( transform);
    btVector3 intertia(0,0,0);
    boxShape->calculateLocalInertia(mass,intertia);
    btCompoundShape* compound = new btCompoundShape();
    btTransform localTrans;
    localTrans.setIdentity();
    //localTrans effectively shifts the center of mass with respect to the chassis
    localTrans.setOrigin(btVector3(offset.x,offset.y,offset.z));
    compound->addChildShape(localTrans,boxShape);


    btRigidBody::btRigidBodyConstructionInfo rigidBodyConstructionInfo(mass,motionState,compound,intertia);
    btRigidBody *body = new btRigidBody(rigidBodyConstructionInfo);

    body->setActivationState(DISABLE_DEACTIVATION);
    dynamicsWorld->addRigidBody(body);

    return body;


}
btVector3 PhysicsManager::getPosition(btRigidBody *rigidBody){


    return rigidBody->getWorldTransform().getOrigin();


}
void PhysicsManager::stepSimulation( ){

    dynamicsWorld->stepSimulation(60,3);

    // jobject position = conversion->tojVector3(env,pos);
    // jobject *object = (jobject*)rigid->getUserPointer();
    //conversion->setPos(env,obj,position);

}

void PhysicsManager::addPosition(btRigidBody *rigidBody, glm::vec3 &position) {
    btTransform *transform = &rigidBody->getWorldTransform();
    __android_log_print(ANDROID_LOG_INFO,"position","x %d\n",position.x);
    __android_log_print(ANDROID_LOG_INFO,"position","y %d\n",position.y);
    __android_log_print(ANDROID_LOG_INFO,"position","z %d\n",position.z);

    transform->getOrigin().setValue(position.x+transform->getOrigin().getX(),position.y+transform->getOrigin().getY(),position.z+transform->getOrigin().getZ());

    rigidBody->setWorldTransform(*transform);
}
void PhysicsManager::addX(btRigidBody *rigidBody,float x) {
    btTransform *transform = &rigidBody->getWorldTransform();


    transform->getOrigin().setValue(x+transform->getOrigin().getX(),transform->getOrigin().getY(),transform->getOrigin().getZ());

    rigidBody->setWorldTransform(*transform);
}
void PhysicsManager::addY(btRigidBody *rigidBody,float y) {
    btTransform *transform = &rigidBody->getWorldTransform();


    transform->getOrigin().setValue(transform->getOrigin().getX(),y+transform->getOrigin().getY(),transform->getOrigin().getZ());

    rigidBody->setWorldTransform(*transform);
}
void PhysicsManager::addZ(btRigidBody *rigidBody,float z) {
    btTransform *transform = &rigidBody->getWorldTransform();


    transform->getOrigin().setValue(transform->getOrigin().getX(),transform->getOrigin().getY(),z+transform->getOrigin().getZ());

    rigidBody->setWorldTransform(*transform);
}
