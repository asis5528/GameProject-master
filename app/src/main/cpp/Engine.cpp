//
// Created by sergio on 7/12/2020.
//

#include "Engine.h"
#include "Scene/Scene.h"
#include "Physics/PhysicsManager.h"

void Engine::init() {


    physicsManager.initPhysics();
    scene.physicsManager = &physicsManager;
    scene.init();

}

void Engine::render() {

    scene.Draw();

}

void Engine::surfaceChanged(int w, int h)  {
    scene.resize(w,h);
}
void Engine::TouchCallBack(float x,float y,int action){

}
void Engine::TouchMoveCallBack() {

}
