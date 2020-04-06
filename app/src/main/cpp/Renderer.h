//
// Created by sergio on 2/13/2020.
//

#ifndef NATIVE_ACTIVITY_RENDERER_H
#define NATIVE_ACTIVITY_RENDERER_H


#include <GLES3/gl3.h>
//#include "shader_manager.h"

class Renderer {
    public:
        void init();
        void render();
        void surfaceChanged(int w,int h);

    private:
       unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        float time;
        int shaderProgram;


};


#endif //NATIVE_ACTIVITY_RENDERER_H
