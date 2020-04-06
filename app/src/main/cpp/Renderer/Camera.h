//
// Created by sergio on 3/25/2020.
//

#ifndef MY_APPLICATION_CAMERA_H
#define MY_APPLICATION_CAMERA_H



class Camera{
public:
    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;
    glm::vec3 pos;
        Camera(glm::vec3 position,glm::mat4 proj){
            this->pos = position;
            viewMatrix = glm::lookAt(pos,glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
            this->projMatrix = proj;
        }
        Camera(){

        }
        void update(){
            viewMatrix = glm::lookAt(pos,glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
            //projMatrix = glm::perspective(glm::radians(90.0f),(float)512/(float)512,0.02f,100.f);

        }


};
#endif //MY_APPLICATION_CAMERA_H
