//
// Created by sergio on 7/15/2020.
//

#ifndef MY_APPLICATION_MATERIAL_H
#define MY_APPLICATION_MATERIAL_H


#include "../shader_manager.h"
#include "../Mesh/Mesh.h"

class Material {
public:
    enum Mode{Default,Textured, PBR};
    Mode mode = Default;
    bool bloom = false;
    bool bloomTexture = false;
    unsigned int DiffuseTextureID = 0;
    unsigned int NormalTextureID = 0;
    unsigned int GlossyTextureID = 0;
    unsigned int RoughnessTextureID = 0;
    unsigned int AmbientTextureID = 0;
    unsigned int bloomTextureID = 0;
    unsigned int brdfTexture = 0;
    unsigned int environmentTexture = 0;
    unsigned int irradianceTexture = 0;
    float roughness = 0.0;
    float metalness = 0.0;
    float ambient = 0.0;
    bool blending = false;
    Shader *shad;
    glm::vec4 objectColor = glm::vec4(1.);
    std::vector<unsigned int> *ObjectTextures;
    std::vector<Texture>* sceneTextures;
    Material(Mode &matmode);
    Material() {
    }
    void Update(Mode &matmode) {
        mode = matmode;
    }
    void set(std::vector<Shader> &shaders,std::vector<Texture> &scnTextures,std::vector<unsigned int> &objTextures);
    void start(glm::vec3 &camPos);



};


#endif //MY_APPLICATION_MATERIAL_H
