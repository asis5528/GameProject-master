//
// Created by sergio on 2/13/2020.
//
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.h"
#include <GLES3/gl3.h>
#include <iostream>
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include <string>
#include <vector>

#include "shader_manager.h"
#include <glm/gtx/component_wise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader/objloader.hpp"
#include "Loader/vboindexer.hpp"
#include "Renderer/Mesh.h"
#include "Renderer/ModelLoader.h"
#include "Renderer/Camera.h"
#include "Loader/load.h"
#include "Object/Object.h"
#include "Renderer/FBO.h"
#include "Scene/Scene.h"


using namespace glm;

float tim;
mat4 proj;

float width,height;
Camera cam;


Scene *scene;
FBO framebuffer;
FBO fbo2;
FBO fbo3;
Quad quad;
Quad quad1;
Quad quad2;

void Renderer::init() {






  // Load("g");
   scene = new Scene(Camera(glm::vec3(0.0,-0.9,0.0),proj));

    Shader quadShader = Shader("Shaders/quad.vert","Shaders/quad.frag");
    Shader vShader =  Shader("Shaders/Vblur.vert","Shaders/blur.frag");
    Shader hShader =  Shader("Shaders/Hblur.vert","Shaders/blur.frag");
    float w  = 1280;
    float h  = 720;
    framebuffer = FBO(w,h,2);

    fbo2 = FBO(w/2,h/2);

    fbo3 = FBO(w/2,h/2);
    quad = Quad(hShader);
    quad.setTexture(framebuffer.textures[1]);
    quad.setTexture(framebuffer.textures[0]);

    quad1 = Quad(vShader);
    quad1.setTexture(fbo2.textures[0]);

    quad2 = Quad(quadShader);
    quad2.setTexture(fbo3.textures[0]);
    quad2.setTexture(framebuffer.textures[0]);

    Object *bill = scene->getObject("bill");
    vector<string> paths = {"posx.png","negx.png","posy.png","negy.png","posz.png","negz.png"};
    bill->model.LoadTexture("bill2.png");
    Object *cube = scene->getObject("cube");
    cube->model.LoadCubeTexture(paths);
    Object *model = scene->getObject("model");
    model->model.addTexture(cube->model.textures[0]);
}

void Renderer::render() {
    //cam.pos.z=3.0;
   // width = 512;
    //height = 512;
    Object *cube = scene->getObject("cube");
    Object *model = scene->getObject("model");
    model->shader.use();
    model->shader.setVec3("cameraPos",scene->cam.pos);
   // cube->data.Rotation.y+=0.1;
    scene->cam.pos.y=7.7;
    float radius = 23.;
    scene->cam.pos.z = sin(tim*0.5)*radius;
    scene->cam.pos.x = cos(tim*0.5)*radius;
    scene->cam.update();
    tim+=0.02;
    int ind = scene->getIndex("bill");
    //scene.objects[ind].setPosition(vec3(tim,0.,0.));
    //scene.getObject("bill",scene.objects).setPosition(vec3(tim,0.,0.));
   Object *bill = scene->getObject("bill");
   bill->shader.use();
   bill->shader.setFloat("fac",sin(tim*19.)+0.5);
   bill->shader.setFloat("test",0.1);
   Object *tree = scene->getObject("tree");

   //bill->setPosition(vec3(tim,0.,0.));

    //__android_log_print(ANDROID_LOG_INFO,"position","%f",bill->data.Position.x);
     //bill->data.Position.x+=0.01;
     bill->data.Rotation.y+=0.01;

    // bill->updateTransform();
    //scene.objects[2].setPosition(vec3(tim,0.,0.));
    //bil.updateTransform();
   framebuffer.bind();
    scene->Draw();
    framebuffer.ubind();


    fbo2.bind();
    quad.shader.use();
    quad.shader.setFloat("width",fbo2.width);
    quad.Draw();
    fbo2.ubind();

    fbo3.bind();
    quad1.shader.use();
    quad1.shader.setFloat("height",fbo3.height);
    quad1.Draw();
    fbo3.ubind();

    glViewport(0,0,width,height);
    quad2.Draw();

}

void Renderer::surfaceChanged(int w,int h) {


    proj = glm::perspective(glm::radians(60.0f),(float)w/(float)h,0.02f,100.f);
    scene->cam.projMatrix = proj;
    scene->cam.update();
    width = w;
    height = h;
    /*
    framebuffer = FBO(width,height,2);

    fbo2 = FBO(width/2,height/2);

    fbo3 = FBO(width/2,height/2);
    quad.setTexture(framebuffer.textures[1]);
    quad.setTexture(framebuffer.textures[0]);
    quad1.setTexture(fbo2.textures[0]);
    quad2.setTexture(fbo3.textures[0]);
    quad2.setTexture(framebuffer.textures[0]);
     */
    glViewport(0,0,w,h);


}

