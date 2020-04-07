//
// Created by sergio on 3/25/2020.
//

#ifndef MY_APPLICATION_OBJECT_H
#define MY_APPLICATION_OBJECT_H


#include <GLES3/gl3.h>

using namespace glm;

struct TransformData{
    vec3 Position;
    vec3 Rotation;
    vec3 Scale;
};
class Object{

public:
    Model model;
    Shader shader;
    mat4 modelMat;
    TransformData data;
    string name;
    bool transformFlag = 0;
    Object(Model model,Shader shader,TransformData transformData,string name){
        this->model = model;
        this->shader = shader;
        this->data = transformData;
        this->name = name;
        modelMat = mat4(1.0);
        modelMat = glm::translate(modelMat,data.Position);
        modelMat = glm::rotate(modelMat,data.Rotation.x,vec3(1,0,0));
        modelMat = glm::rotate(modelMat,data.Rotation.y,vec3(0,1,0));
        modelMat = glm::rotate(modelMat,data.Rotation.z,vec3(0,0,1));
        modelMat = glm::scale(modelMat,data.Scale);
    }
    Object(){

    }
    void updateTransform(){
        this->modelMat = mat4(1.0);
        this->modelMat = glm::translate(this->modelMat,data.Position);
        this->modelMat = glm::rotate(this->modelMat,data.Rotation.x,vec3(1,0,0));
        this->modelMat = glm::rotate(this->modelMat,data.Rotation.y,vec3(0,1,0));
        this->modelMat = glm::rotate(this->modelMat,data.Rotation.z,vec3(0,0,1));
        this->modelMat = glm::scale(this->modelMat,data.Scale);

    }
    void setPosition(vec3 p ){
        this->modelMat = mat4(1.0);
        this-> modelMat = glm::translate(modelMat, p);
        this->modelMat = glm::rotate(modelMat, this->data.Rotation.x,vec3(1,0,0));
        this->modelMat = glm::rotate(modelMat, this->data.Rotation.y,vec3(0,1,0));
        this->modelMat = glm::rotate(modelMat, this->data.Rotation.z,vec3(0,0,1));
        this->modelMat = glm::scale(modelMat, this->data.Scale);
        this->shader.use();
        this->shader.setMat4("model",this->modelMat);
    }
    void Draw(Camera *camera){
        this->shader.use();

        if(transformFlag){
            updateTransform();
            transformFlag = false;
        }
        updateTransform();
        this->shader.setMat4("view",camera->viewMatrix);
        this->shader.setMat4("proj",camera->projMatrix);
        this->shader.setMat4("model",modelMat);
        for(int i = 0;i<this->model.textures.size();i++){

                glActiveTexture(GL_TEXTURE0+i);

                glBindTexture(model.textures[i].type,model.textures[i].id);
                string name = "tex"+std::to_string(i);
                glUniform1i(glGetUniformLocation(this->shader.ID, name.c_str()), i);

        }


        this->model.Draw(this->shader);
    }
};

class ObjectInit{

    public:
        Object object;
        ObjectInit(char* modelPath,char* vertexShaderPath,char* fragmentShaderPath,char* texturePath = nullptr){
            char* k = modelPath;
            LoadTrans t  = LoadTrans(modelPath);
            Model model = Model(k);
            TransformData data;
            float toRad = 3.1415/180;
                data.Position = vec3(t.position.x,t.position.z,-t.position.y);
                data.Rotation = vec3(t.rotation.x*toRad,t.rotation.z*toRad,-t.rotation.y*toRad);
                data.Scale = vec3(1.0,1.0,1.0);

            size_t found =string(k).find(".");
            string name = string(k).substr(0,found);
            //LoadTransformation(modelPath);


            if(texturePath!= nullptr){
                model.LoadTexture(texturePath);
            }
           Shader shader = Shader(vertexShaderPath,fragmentShaderPath);
           object = Object(model,shader,data,name);

        }
        ObjectInit(){

        }
};
#endif //MY_APPLICATION_OBJECT_H
