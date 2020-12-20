//
// Created by sergio on 7/12/2020.
//

#ifndef MY_APPLICATION_ENGINE_H
#define MY_APPLICATION_ENGINE_H


#include "Scene/Scene.h"

class Engine {
public:
    void init();
    void render();
    void surfaceChanged(int w,int h);
    void TouchCallBack(float x,float y);

private:
    Scene scene;
};


#endif //MY_APPLICATION_ENGINE_H
