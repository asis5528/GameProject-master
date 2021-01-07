//
// Created by sergio on 7/12/2020.
//

#include "Scene.h"
#include <GLES3/gl3.h>
#include "../shader_manager.h"
#include "../Mesh/Mesh.h"
#include "../OpenGL/Material.h"
#include "../Object/Object.h"
#include "../OpenGL/OpenGLMesh.h"
#include "../OpenGL/OpenGLTexture.h"
#include "../Loader/SceneLoader.h"
#include "../Inputs/Touch.h"
#include <glm/gtx/component_wise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

static glm::vec3 camPos;
static btRigidBody *rBody;
static btRigidBody *rBody2;
static btRigidBody *rBody3;
void Scene::init(){
    gui.init();
    shader = Shader("Shaders/simpleQuad.vert","Shaders/simpleQuad.frag");
    shaders.push_back(shader);
    Shader texturedShader = Shader("Shaders/textured.vert","Shaders/textured.frag");
    Shader pbrShader = Shader("Shaders/ibl.vert","Shaders/ibl.frag");
    shaders.push_back(texturedShader);
    shaders.push_back(pbrShader);
    SceneLoader::loadSceneData("Man2/man.sav",this);
    for(unsigned int i=0;i<animations[0].actions.size();i++){
        __android_log_print(ANDROID_LOG_INFO,"actions","x %s\n",animations[0].actions[i].name.c_str());
    }
    __android_log_print(ANDROID_LOG_INFO,"Total count"," %d\n",objects.size());
    static float time = 0.0;
    //time+=0.01;
    time = 3.1415/2.;
    camPos.x = sin(time)*9;
    camPos.z = cos(time)*9;
    camPos.y = 4.;
    //__android_log_print(ANDROID_LOG_INFO,"dimension","x %d\n",objects[0].dimension.x);
   // __android_log_print(ANDROID_LOG_INFO,"dimension","y %d\n",objects[0].dimension.y);
   // __android_log_print(ANDROID_LOG_INFO,"dimension","z %d\n",objects[0].dimension.z);
    Character character(&objects[0],physicsManager,meshes[objects[0].primitiveID]);
    characters.push_back(character);
    //rBody = physicsManager->setBoxCollision(1.0,glm::vec3(0,10,0),objects[0].rotation,objects[0].scale,meshes[objects[0].primitiveID].minBounds,meshes[objects[0].primitiveID].maxBounds);
    //rBody2 = physicsManager->setBoxCollision(0.0,objects[1].position,objects[1].rotation,objects[1].dimension);
    rBody2 = physicsManager->setBoxCollision(0.0,objects[1].position,objects[1].rotation,objects[1].scale,meshes[objects[1].primitiveID].minBounds,meshes[objects[1].primitiveID].maxBounds);
    rBody3 =  physicsManager->setBoxCollision(1000.9,objects[2].position,objects[2].rotation,objects[2].scale,meshes[objects[2].primitiveID].minBounds,meshes[objects[2].primitiveID].maxBounds);
}

void Scene::Draw() {
    if(this->animations.size()>0){
        float n = 1.0;
    }

   // glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glm::vec3 pos = glm::vec3(3.,0.,0.);
    glm::mat4 view = glm::lookAt(camPos,glm::vec3(0.1,0.,camPos.z),glm::vec3(0,1,0));
    for(Object &object:objects){
        object.updateTransformation();
    }
    float walk = 0.05;
    float run = 0.2;
    static float oldAngle =0.;
    static bool firstAction;
    this->animations[0].actions[4].playMode =1;
    if(touch.getTouchState()){

        if (touch.getNormalizedTouchX()>0.8){



            if(touch.getNormalizedTouchY()>0.8){

                characters[0].RunRight();
            }else if(touch.getNormalizedTouchY()<0.2){


                characters[0].walkRight();
            }else{
                characters[0].IdlePose();
            }

        }else if(touch.getNormalizedTouchX()<0.2){

            if(touch.getNormalizedTouchY()>0.8){

                characters[0].RunLeft();

            }else if(touch.getNormalizedTouchY()<0.2){

                characters[0].walkLeft();

            }else{
                characters[0].IdlePose();
            }

        }
        else{


            float tx = touch.getNormalizedTouchX()-0.5;
            float ty = touch.getNormalizedTouchY()-0.5;
            float an = atan2(ty,tx);
            an = glm::atan(ty,tx);
            if(an<-3.1413){
                an = 3.1415+3.1415+an;
            }
            if(firstAction){
                oldAngle =an;
                firstAction = false;
            }
            if(abs(an-oldAngle)>3.1415){                oldAngle=an;
            }
            static float angle =0.0;

            float offset = an-oldAngle;

            angle+=offset;


            if(angle>0.0){
                angle = 0.0;
            }
            else if(angle<-3.1415){
                angle = -3.1415;

            }
            float finalAngle = abs(angle+3.1415/2.);
            if(angle<-(3.1415/2.0)){
                objects[0].rotation.y+=20;
                if(objects[0].rotation.y>180){
                    objects[0].rotation.y = 180;
                }

            }else{
                objects[0].rotation.y-=20;
                if(objects[0].rotation.y<0){
                    objects[0].rotation.y=0;
                }

            }

            oldAngle = an;
            objects[0].animator.boneName = "boss:Spine";
            objects[0].animator.TransformationMatrix = glm::mat4(1.0);
            objects[0].animator.TransformationMatrix  = glm::rotate( objects[0].animator.TransformationMatrix,finalAngle-(3.1415f/2.f), glm::vec3(1, 0, 0));
            characters[0].aim();
        }

    }else{
        firstAction = true;
       // objects[0].animator.Blendfactor -=0.1;
       // if( objects[0].animator.Blendfactor<0.0){
        //    objects[0].animator.Blendfactor=0.0;
       // }
       characters[0].IdlePose();
    }
    if((objects[0].position.z-camPos.z)>5){
        camPos.z=objects[0].position.z-5.;

    }
    else if((objects[0].position.z-camPos.z)<-5){
        camPos.z=objects[0].position.z+5.;
    }


    physicsManager->stepSimulation();
    btVector3 rpos2 = physicsManager->getPosition(rBody2);
    btVector3 rpos3 = physicsManager->getPosition(rBody3);
    //objects[0].position = glm::vec3(rpos.getX(),rpos.getY(),rpos.getZ());
    characters[0].UpdateTransformation();
    objects[1].position = glm::vec3(rpos2.getX(),rpos2.getY(),rpos2.getZ());
    objects[2].position = glm::vec3(rpos3.getX(),rpos3.getY(),rpos3.getZ());


    for(Object& object:objects ){
        object.mat.set(shaders,textures,object.textureID);
        object.mat.start(camPos);
        object.mat.shad->use();
        object.mat.shad->setMat4("view",view);
        object.mat.shad->setMat4("projection",proj);
        if(object.animationIDs.size()>0){
            object.processAnimation(meshes[object.primitiveID],animations[object.animationIDs[0]]);
        }
        else{
        object.mat.shad->setBool("hasAnimation", false);
    }
        object.Render(GLmeshes[object.primitiveID]);
    }
    gui.render();
   // objects[1].Render(GLmeshes[objects[1].primitiveID]);
}

void Scene::resize(unsigned int width, unsigned int height) {
    glViewport(0,0,width,height);
    proj =glm::perspective(glm::radians(75.0f),(float)width/(float)height,0.1f,100.f);
}
void Scene::TouchMove() {

}