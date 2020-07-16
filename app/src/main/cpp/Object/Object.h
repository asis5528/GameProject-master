//
// Created by sergio on 7/14/2020.
//

#ifndef MY_APPLICATION_OBJECT_H
#define MY_APPLICATION_OBJECT_H


#include "../../../../../../../Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/c++/v1/string"
#include "../shader_manager.h"
#include "../OpenGL/OpenGLMesh.h"
#include "../OpenGL/Material.h"
#include <glm/glm.hpp>
class Object {
public:
    std::string name;
    unsigned int primitiveID;
    Material mat;
    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 scale = glm::vec3(0.01);
    glm::vec3 rotation = glm::vec3(0.);
    std::vector<unsigned int> textureID;
    void init(unsigned int primitiveIndex,std::string nam,Material &material);
    void Render(OpenGLMesh &mesh);
    void pushTextureID(unsigned int ID){
        textureID.push_back(ID);
    }
    unsigned int getTextureID(unsigned int index){
        return textureID[index];
    }
    void seTexturesID(std::vector<unsigned int> &tIDs){
        textureID = tIDs;
    }


private:

};


#endif //MY_APPLICATION_OBJECT_H
