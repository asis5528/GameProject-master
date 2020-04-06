//
// Created by sergio on 3/27/2020.
//

#ifndef MY_APPLICATION_SCENE_H
#define MY_APPLICATION_SCENE_H

#include "PreModel.h"
class Scene{
public:
    Camera cam;
     std::vector<Object> objects;
    Scene(Camera camera){
        cam = camera;
        {
            objects = PreModel().objects;
        }
    }
    Scene(){

    }

    void Draw(){
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
        for(Object object:objects){
            object.Draw(&cam);

        }

        }
     Object *getObject(string name){
        //std::vector<Object> *o = obj;
         for(int i = 0;i<this->objects.size();i++){
             if(objects[i].name==name){
                 return &this->objects[i];
                 break;
             }
         }

    }
        int getIndex(string name){
            for(int i = 0;i<objects.size();i++){
                if(objects[i].name==name){
                    return i;
                    break;
                }
            }
    }
};
#endif //MY_APPLICATION_SCENE_H
