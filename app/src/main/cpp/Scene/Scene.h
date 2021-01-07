//
// Created by sergio on 7/12/2020.
//

#ifndef MY_APPLICATION_SCENE_H
#define MY_APPLICATION_SCENE_H


#include "../shader_manager.h"
#include "../OpenGL/OpenGLMesh.h"
#include "../Object/Object.h"
#include "../Animation/Animation.h"
#include "../Physics/PhysicsManager.h"
#include "../Gui/Gui.h"
#include "../GameLogic/Character.h"


class Scene {
public:
    PhysicsManager *physicsManager;
    std::vector<Animation> animations;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures;
    void init();
    void Draw();
    void resize(unsigned int width,unsigned int height);
    void TouchMove();
    void pushGLMesh(OpenGLMesh & mesh){
        GLmeshes.push_back(mesh);
    }
    void pushMesh(Mesh &mesh){
        meshes.push_back(mesh);
    }
    void pushObjects(Object &object){
        objects.push_back(object);
    }
    std::vector<Texture> &getTextures(){
        return  textures;
    }
    void pushAnimation(Animation &animation){
        animations.push_back(animation);
    }
    Object *getObjects(int index){
        return &objects[index];
    }
    Animation *getAnimation(int index){
        return &animations[index];
    }
    int getObjectSize(){
        return  objects.size();
    }
private:
    //unsigned int VAO;
   // unsigned int VBO;
   // unsigned int EBO;
   // int shaderProgram;
    Shader shader;
    OpenGLMesh m;
    glm::mat4 proj;
    std::vector<Object> objects;
    std::vector<OpenGLMesh> GLmeshes;
    Gui gui;
    std::vector<Character> characters;
    std::vector<Shader> shaders;



  //  glm::vec3 camPos;
   // float time = 0.;

};


#endif //MY_APPLICATION_SCENE_H
