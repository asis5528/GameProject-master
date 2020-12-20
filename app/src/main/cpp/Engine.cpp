//
// Created by sergio on 7/12/2020.
//

#include "Engine.h"
#include "Scene/Scene.h"

void Engine::init() {
    scene.init();

}

void Engine::render() {
    scene.Draw();
}

void Engine::surfaceChanged(int w, int h)  {
    scene.resize(w,h);
}
void Engine::TouchCallBack(float x,float y){
        
    __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",x);
    __android_log_print(ANDROID_LOG_INFO,"print","y %f\n",y);
}
