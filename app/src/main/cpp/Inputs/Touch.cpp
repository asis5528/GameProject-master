//
// Created by sergio on 12/21/2020.
//
#include <glm/detail/type_vec2.hpp>
#include "Touch.h"
void Touch::setTouchState(bool state)
{
    touchDown = state;
}
void Touch::setTouchCoordinates(float tx,float ty){
    x=tx;
    y=ty;
}
bool Touch::getTouchState()
{
   return touchDown;
}
float Touch::getTouchX(){
    return x;
}
float Touch::getTouchY(){
    return y;
}
float Touch::getNormalizedTouchX(){
    return x/resX;
}
float Touch::getNormalizedTouchY(){
    return 1.-(y/resY);
}
glm::vec2 Touch::getTouchCoordinates(){

    return glm::vec2(x,y);
}
glm::vec2 Touch::getNormalizedTouchCoordinates(){

    return glm::vec2(x/resX,1.-(y/resY));
}
void Touch::setResolution(int x,int y){
    resX=x;
    resY=y;
}
