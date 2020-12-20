//
// Created by sergio on 7/13/2020.
//
#define STB_IMAGE_IMPLEMENTATION
#ifndef MY_APPLICATION_SCENELOADER_H
#define MY_APPLICATION_SCENELOADER_H


#include <string>
#include "../Mesh/Mesh.h"

#include "../Scene/Scene.h"
#include "../Animation/AnimationData.h"

class SceneLoader {
public:
    template <class Scene>
    static void sc(Scene *sc){
        //sc->test = 5.0;
        //__android_log_print(ANDROID_LOG_INFO,"print","x %f\n",sc->test);
    }
    static void loadSceneData(std::string path,Scene *sc);
    static void loadPrimitive(std::string path,Scene *sc);
    static bool searchNode(AnimationData& adata, std::string Parentname,std::string Childname,std::vector<AnimationTransformation> &ATT);

private:

    static void loadTexture(std::string path,std::vector<Texture>& textures);
    static unsigned int LoadTextureData(const char* path, int &width, int &height,GLenum &format);
    static void loadCubeMapTexture(std::string path,std::vector<Texture>& textures);
    static unsigned int LoadCubeMapTextureData(std::vector<std::string> faces, int& width, int& height, GLenum& format);
    static std::string getFileName(std::string filePath, bool withExtension = true, char seperator = '/')
    {
        // Get last dot position
        std::size_t dotPos = filePath.rfind('.');
        std::size_t sepPos = filePath.rfind(seperator);
        if(sepPos==std::string::npos){
            return filePath;
        }
        if (sepPos != std::string::npos)
        {
            return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos));
        }
        return "";
    }
    static std::string getPathName(const std::string& s) {

        char sep = '/';
        size_t i = s.rfind(sep, s.length());
        if (i != std::string::npos) {
            return(s.substr(0, i)+"/");
        }
        return("");
    }


};


#endif //MY_APPLICATION_SCENELOADER_H
