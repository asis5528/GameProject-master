//
// Created by sergio on 1/3/2021.
//

#include "Button.h"
#include "../Inputs/Touch.h"

Button::Button(float x, float y, float width, float height) {
    pos = glm::vec2(x,y);
    size = glm::vec2(width,height);
    std::vector<Vertex> verts;
    Vertex v;
    float vx = width/2;
    float vy = height/2;
    v.Position = glm::vec3(vx,vy,0);
    verts.push_back(v);
    v.Position = glm::vec3(-vx,vy,0);
    verts.push_back(v);
    v.Position = glm::vec3(vx,-vy,0);
    verts.push_back(v);
    v.Position = glm::vec3(-vx,-vy,0);
    verts.push_back(v);
    std::vector<unsigned int> indices;
    indices = {0,1,2,2,1,3};
    mesh->init(verts,indices);
}
bool Button::hit(){
    float mx = touch.getNormalizedTouchX()-pos.x;
    float my = touch.getNormalizedTouchY()-pos.y;


    if(abs(mx)<(size.x/2.)){
        if(abs(my)<(size.y/2.)){
            return true;
        }else{
            return false;
        }

    }else{
        return false;
    }

}
void Button::render(Shader &shader) {
    shader.use();
    shader.setVec2("pos",glm::vec2((pos.x-0.5)*2.0,(pos.y-0.5)*2.0));
    mesh->Render(shader);
}
