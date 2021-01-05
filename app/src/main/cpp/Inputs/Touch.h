//
// Created by sergio on 12/21/2020.
//

#ifndef MY_APPLICATION_TOUCH_H
#define MY_APPLICATION_TOUCH_H

#include <glm/fwd.hpp>

class Touch{
public:
    void setTouchState(bool state);
    void setTouchCoordinates(float x,float y);
    float getTouchX();
    float getTouchY();
    float getNormalizedTouchX();
    float getNormalizedTouchY();
    glm::vec2 getTouchCoordinates();
    bool getTouchState();
    void setResolution(int x,int y);
private:
    bool touchDown =false;
    float x,y;
    int resX,resY;


    glm::vec2 getNormalizedTouchCoordinates();
};

extern Touch touch;


#endif //MY_APPLICATION_TOUCH_H
