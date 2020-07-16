//
// Created by sergio on 7/15/2020.
//

#include "Material.h"

Material::Material(Material::Mode &matmode) {
    mode = matmode;
}
void Material::set(std::vector<Shader> &shaders, std::vector<Texture> &scnTextures,
                   std::vector<unsigned int> &objTextures) {
    ObjectTextures =&objTextures;
    sceneTextures = &scnTextures;
    if (mode == Default) {
        shad = &shaders[0];
    }
    else if (mode == Textured) {
        shad = &shaders[1];
    }
    else if (mode == PBR) {
        shad = &shaders[2];
    }
}

void Material::start(glm::vec3 &camPos) {
    shad->use();
    shad->setBool("blending", blending);
    if (mode == Default) {
        shad->setVec4("objectColor", objectColor);
        if (bloom) {
            shad->setBool("bloom", true);
            if (bloomTexture) {
                if (ObjectTextures->size() > 0) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D,
                                  sceneTextures->at(ObjectTextures->at(bloomTextureID)).id);
                    shad->setBool("GlowTexture", 0);
                    shad->setBool("BloomTexture", 1);
                } else {
                    shad->setBool("BloomTexture", 0);
                }
            }
        } else {
            shad->setBool("bloom", false);
            shad->setBool("BloomTexture", 0);
        }
    }
        else if (mode == Textured) {
            if (ObjectTextures->size() > 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(DiffuseTextureID)).id);
                shad->setInt("DiffuseTexture", 0);
                if (bloom) {
                    shad->setBool("bloom", true);
                    if (bloomTexture) {
                        glActiveTexture(GL_TEXTURE1);
                        glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(bloomTextureID)).id);
                        shad->setInt("GlowTexture", 2);
                        shad->setBool("BloomTexture", 1);
                    }
                    else {
                        shad->setBool("BloomTexture", 0);
                    }
                }
                else {
                    shad->setBool("bloom", false);
                    shad->setBool("BloomTexture", 0);
                }
            }
        }
        else if (mode == PBR) {
            if (ObjectTextures->size() > 0) {
                //glActiveTexture(GL_TEXTURE0);
                //glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(DiffuseTextureID)).id);
                //shad->setInt("DiffuseTexture", 0);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, sceneTextures->at(ObjectTextures->at(environmentTexture)).id);
                shad->setInt("envMap", 0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(DiffuseTextureID)).id);
                shad->setInt("DiffuseTexture", 1);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(GlossyTextureID)).id);
                shad->setInt("glossyTexture", 2);
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(RoughnessTextureID)).id);
                shad->setInt("roughnessTexture", 3);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(NormalTextureID)).id);
                shad->setInt("normalMap", 4);
                glActiveTexture(GL_TEXTURE5);
                glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(bloomTextureID)).id);
                shad->setInt("GlowTexture", 5);
                glActiveTexture(GL_TEXTURE6);
                glBindTexture(GL_TEXTURE_CUBE_MAP, sceneTextures->at(ObjectTextures->at(irradianceTexture)).id);
                shad->setInt("IrradianceTexture", 6);

                //glActiveTexture(GL_TEXTURE7);
                //glBindTexture(GL_TEXTURE_2D, sceneTextures->at(ObjectTextures->at(AmbientTextureID)).id);
               // shad->setInt("AoTexture", 7);


                shad->setVec3("camPos", camPos);
                shad->setFloat("roughness", roughness);
                shad->setFloat("metalness", metalness);
                shad->setFloat("Ambient", ambient);

                if (bloom) {
                    shad->setBool("bloom", true);
                    if (bloomTexture) {
                        shad->setBool("BloomTexture", 1);
                    }
                    else {

                        shad->setBool("BloomTexture", 0);
                    }
                }
                else {
                    shad->setBool("bloom", false);
                    //shad->setBool("BloomTexture", 0);
                }
            }


        }
    }


