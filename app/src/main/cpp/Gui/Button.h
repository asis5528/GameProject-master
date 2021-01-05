//
// Created by sergio on 1/3/2021.
//

#ifndef MY_APPLICATION_BUTTON_H
#define MY_APPLICATION_BUTTON_H


#include <glm/fwd.hpp>
#include <glm/detail/type_vec2.hpp>
#include "../OpenGL/OpenGLMesh.h"

class Button {
public:
    glm::vec2 pos;
    glm::vec2 size;
    Button(float x,float y,float width,float height);
    void render(Shader &shader);
    bool hit();
private:
    OpenGLMesh *mesh;
};


#endif //MY_APPLICATION_BUTTON_H
