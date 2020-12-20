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

#include "../Loader/SceneLoader.h"
#include <glm/gtx/component_wise.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Scene::init(){

    shader = Shader("Shaders/simpleQuad.vert","Shaders/simpleQuad.frag");
    shaders.push_back(shader);
    Shader texturedShader = Shader("Shaders/textured.vert","Shaders/textured.frag");
    Shader pbrShader = Shader("Shaders/ibl.vert","Shaders/ibl.frag");
    shaders.push_back(texturedShader);
    shaders.push_back(pbrShader);
    SceneLoader::loadSceneData("Girl/girl.sav",this);


}

void Scene::Draw() {
    if(this->animations.size()>0){
        float n = 1.0;
    }
    static glm::vec3 camPos;
    static float time = 0.0;
    time+=0.01;
    camPos.x = sin(time)*4;
    camPos.z = cos(time)*4;
    camPos.y = 2.;
   // glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glm::vec3 pos = glm::vec3(3.,0.,0.);
    glm::mat4 view = glm::lookAt(camPos,glm::vec3(0.,0.,0.),glm::vec3(0,1,0));

    for(Object& object:objects ){
        object.mat.set(shaders,textures,object.textureID);
        object.position.x=-0.;
        object.position.z=-0.;
        object.position.y=-2.;
        object.scale= glm::vec3(0.003);
        object.mat.start(camPos);
        object.mat.shad->use();
        object.mat.shad->setMat4("view",view);
        object.mat.shad->setMat4("projection",proj);
        if(object.animationIDs.size()>0){
            object.processAnimation(meshes[object.primitiveID],animations[object.animationIDs[0]]);
        }
        object.Render(GLmeshes[object.primitiveID]);
    }


}

void Scene::resize(unsigned int width, unsigned int height) {
    glViewport(0,0,width,height);
    proj =glm::perspective(glm::radians(90.0f),(float)width/(float)height,0.1f,100.f);
}