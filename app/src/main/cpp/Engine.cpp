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
