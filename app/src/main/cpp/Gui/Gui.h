//
// Created by sergio on 1/3/2021.
//

#ifndef MY_APPLICATION_GUI_H
#define MY_APPLICATION_GUI_H


#include "../shader_manager.h"
#include "Button.h"

class Gui {
public:
    void init();
    void render();

private:
    Shader buttonShader;
    std::vector<Button> buttons;

};


#endif //MY_APPLICATION_GUI_H
