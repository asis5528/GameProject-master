//
// Created by sergio on 1/5/2021.
//

#include "Character.h"

Character::Character(Object *object,PhysicsManager *physicsManager,Mesh &mesh) {
    this->object = object;
    rigidBody = physicsManager->setBoxCollision(1.0,object->position,object->rotation,object->scale,mesh.minBounds,mesh.maxBounds);
}
void Character::blendAction(){
    object->animator.Blendfactor +=0.1;
    if( object->animator.Blendfactor>1.0){
        object->animator.Blendfactor=1.0;
    }
}
void Character::IdlePose() {
    object->animator.Blendfactor -=0.1;
    if( object->animator.Blendfactor<0.0){
        object->animator.Blendfactor=0.0;
    }
}
void Character::lookLeft() {
    blendAction();
    object->rotation.y-=20;
    if(object->rotation.y<0){
        object->rotation.y=0;
    }
}
void Character::lookRight() {
    blendAction();
    object->rotation.y+=20;
    if(object->rotation.y>180){
        object->rotation.y=180;
    }
}
void Character::walkLeft() {
    blendAction();
    object->animator.blendAction = 2;
    lookLeft();
    btTransform *transform = &rigidBody->getWorldTransform();
    transform->getOrigin().setValue(transform->getOrigin().getX(),transform->getOrigin().getY(),WalkSpeed+transform->getOrigin().getZ());
    rigidBody->setWorldTransform(*transform);
}
void Character::walkRight() {
    object->animator.blendAction = 2;
    lookRight();
    btTransform *transform = &rigidBody->getWorldTransform();
    transform->getOrigin().setValue(transform->getOrigin().getX(),transform->getOrigin().getY(),transform->getOrigin().getZ()-WalkSpeed);
    rigidBody->setWorldTransform(*transform);

}
void Character::RunLeft() {
    blendAction();
    object->animator.blendAction = 3;
    lookLeft();
    btTransform *transform = &rigidBody->getWorldTransform();
    transform->getOrigin().setValue(transform->getOrigin().getX(),transform->getOrigin().getY(),transform->getOrigin().getZ()+RunSpeed);
    rigidBody->setWorldTransform(*transform);
}
void Character::RunRight() {
    blendAction();
    object->animator.blendAction = 3;
    lookRight();
    btTransform *transform = &rigidBody->getWorldTransform();
    transform->getOrigin().setValue(transform->getOrigin().getX(),transform->getOrigin().getY(),transform->getOrigin().getZ()-RunSpeed);
    rigidBody->setWorldTransform(*transform);

}
void Character::aim() {
    blendAction();
    object->animator.blendAction = 4;
}
void Character::Jump() {

}
void Character::UpdateTransformation() {
    btVector3 pos = rigidBody->getWorldTransform().getOrigin();
    object->position = glm::vec3(pos.getX(),pos.getY(),pos.getZ());
}