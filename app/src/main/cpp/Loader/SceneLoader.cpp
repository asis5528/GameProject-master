//
// Created by sergio on 7/13/2020.
//

#include <android/asset_manager.h>
#include <sstream>
#include "SceneLoader.h"
#include "../../../../../../../Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"
#include "../AssetsLoader.h"
#include <string>

#include "../Mesh/Mesh.h"
#include "../stb_image.h"
#include "../OpenGL/Material.h"

void SceneLoader::loadPrimitive(std::string path,Scene *sc) {
    path+=".pribln";
    AAsset* file = AAssetManager_open(mgr,path.c_str(),AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    char* modelData = new char[fileLength];
    AAsset_read(file, modelData, fileLength);
    std::istringstream iff(modelData);
    std::string nam;
    std::string n;

    //iff >> x >> y>> z;
    iff >> n >> nam;
    __android_log_print(ANDROID_LOG_INFO,"print","x %s\n",nam.c_str());
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::string line;

    int state = 0;
    while (std::getline(iff, line)) {
        std::string n;
        iff >> n;

        if (state == 1) {

            std::string line2;
            std::getline(iff, line2);
            std::istringstream iss(line2);
            float vertex;
            vertex = std::stof(n);
            vertices.push_back(vertex);
            while (iss >> vertex) {
                vertices.push_back(vertex);
            }

            state = 2;


        }
        else if (state == 2) {

            std::string line2;
            std::getline(iff, line2);
            std::istringstream iss(line2);

            int index;

            index = std::stoi(n);
            indices.push_back(index);
            while (iss >> index) {
                indices.push_back(index);
            }

            state = 3;

        }
        if (n == "vertexDatas") {
            state = 1;

        }
    }
    std::vector<Vertex> verts;
    for (int i = 0; i < vertices.size() / 8; i++) {
        Vertex v;
        v.Position.x = vertices[i * 8 + 0];
        v.Position.y = vertices[i * 8 + 1];
        v.Position.z = vertices[i * 8 + 2];
        v.Normals.x = vertices[i * 8 + 3];
        v.Normals.y = vertices[i * 8 + 4];
        v.Normals.z = vertices[i * 8 + 5];
        v.TextureCoordinates.x = vertices[i * 8 + 6];
        v.TextureCoordinates.y = vertices[i * 8 + 7];

        verts.push_back(v);
    }
    Mesh mesh = Mesh(verts,indices);
    sc->pushMesh(mesh);
    OpenGLMesh openGlMesh;
    openGlMesh.init(mesh.vertices,mesh.indices);
    sc->pushGLMesh(openGlMesh);
    //sc->pushGLMesh()
}

void SceneLoader::loadSceneData(std::string path,Scene *sc) {
    AAsset* file = AAssetManager_open(mgr,path.c_str(),AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    char* modelData = new char[fileLength];
    AAsset_read(file, modelData, fileLength);
    std::istringstream iff(modelData);
    unsigned int NObjects;
    unsigned int NPrimitives;
    std::string line;
    int state = 0;
    while (std::getline(iff, line)) {
        std::istringstream iss(line);
        std::string currentData;
        iss >> currentData;
        if (currentData == "NObjects") {
            std::string nobjects;
            iss >> nobjects;
            NObjects = std::stoi(nobjects);

        }
        if (currentData == "NPrimitives") {
            std::string nprimitives;
            iss >> nprimitives;
            NPrimitives = std::stoi(nprimitives);

        }

        if (currentData == "#prim") {
            state = 1;

        }
        else if (currentData == "#textures") {
            state = 2;
        }
        else if (currentData == "#lights") {
            state = 4;

        }
        else if (currentData == "#objects") {
            state = 3;
        }
        else if (state == 1) {

            std::string finalPathName = "primitives/" + currentData;
            SceneLoader::loadPrimitive(finalPathName,sc);
        }
        else if (state == 2) {
            std::string type = currentData;
            std::string path;
            iss >> path;
            std::string fileName =  getFileName(path);
            std::string finalPath = "Textures/"+fileName;
            if (type == "2D") {
                loadTexture(finalPath, sc->getTextures());
            }
            else if(type=="cubemap"){
                loadCubeMapTexture(finalPath,sc->getTextures());
            }

        }
        else if (state == 4) {



        }
        else if (state == 3) {
            std::string name = currentData;
            glm::vec3 pos;
            glm::vec3 scale;
            glm::vec3 rotation;
            unsigned int primitiveIndex;
            unsigned int textureSize;
            std::vector<unsigned int> textureIDS;
            unsigned int materialmodeindex;
            glm::vec4 objectColor = glm::vec4(1.);
            iss >> pos.x;
            iss >> pos.y;
            iss >> pos.z;
            iss >> rotation.x;
            iss >> rotation.y;
            iss >> rotation.z;
            iss >> scale.x;
            iss >> scale.y;
            iss >> scale.z;
            iss >> primitiveIndex;
            iss >> textureSize;
            for (int i = 0; i < textureSize; i++) {
                unsigned int ID;
                iss >> ID;
                textureIDS.push_back(ID);
            }
            iss >> materialmodeindex;
            for (int j = 0; j < 4; j++) {

                iss >> objectColor[j];

            }
            Material::Mode m = static_cast<Material::Mode>(materialmodeindex);
            Material def(m);
            iss >> def.roughness;
            iss >> def.metalness;
            iss >> def.ambient;
            iss >> def.blending;
            iss >> def.bloom;
            iss >> def.bloomTexture;
            iss >> def.DiffuseTextureID;
            iss >> def.NormalTextureID;
            iss >> def.GlossyTextureID;
            iss >> def.RoughnessTextureID;
            iss >> def.bloomTextureID;
            iss >> def.brdfTexture;
            iss >> def.environmentTexture;
            iss >> def.irradianceTexture;

            Object object;
            object.init(primitiveIndex,name,def);
            object.position = pos;
            object.rotation = rotation;
            object.scale = scale;
            object.seTexturesID(textureIDS);
            sc->pushObjects(object);


        }
    }
}

void SceneLoader::loadTexture(std::string path, std::vector<Texture> &textures) {
    Texture tex;
    int width;
    int height;
    GLenum format = GL_RGBA;
    tex.id = LoadTextureData(path.c_str(),width,height,format);
    tex.type = GL_TEXTURE_2D;
  //  tex.path = path;
    tex.width = width;
    tex.height = height;
    tex.format = format;
    textures.push_back(tex);
  //  tex.name = Tools::getFileName(path, true);
}
unsigned int SceneLoader::LoadTextureData(const char *path, int &width, int &height, GLenum &format) {


    std::vector<uint8_t> buf;
    AAsset* file = AAssetManager_open(mgr,
                                      path, AASSET_MODE_BUFFER);

    size_t fileLength = AAsset_getLength(file);
    buf.resize(fileLength);
    int64_t  readSize = AAsset_read(file,buf.data(),buf.size());



    unsigned int textureID;
    glGenTextures(1, &textureID);
    stbi_set_flip_vertically_on_load(0);
    int nrComponents;
    uint8_t* imageBits = stbi_load_from_memory(buf.data(),buf.size(),&width,&height,&nrComponents,0);
    float n = 1.0;
    if (imageBits)
    {
        //GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageBits);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(imageBits);
    }
    else
    {

        stbi_image_free(imageBits);
    }

    return textureID;
}

void SceneLoader::loadCubeMapTexture(std::string path, std::vector<Texture> &textures) {
    Texture tex;
    int width;
    int height;
    GLenum format = GL_RGB;
    std::vector<std::string> paths;
    for(int i = 0;i<6;i++){
        paths.push_back(path+std::to_string(i)+".png");
    }
    tex.id = LoadCubeMapTextureData(paths,width,height,format);
    tex.type = GL_TEXTURE_CUBE_MAP;
    tex.width = width;
    tex.height = height;
    tex.format = format;
    textures.push_back(tex);
}

unsigned int  SceneLoader::LoadCubeMapTextureData(std::vector<std::string> faces, int& width, int& height, GLenum& format) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int nrChannels;
    format = GL_RGB;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        std::string filename = std::string(faces[0]);

        std::vector<uint8_t> buf;
        AAsset* file = AAssetManager_open(mgr,
                                          faces[i].c_str(), AASSET_MODE_BUFFER);

        size_t fileLength = AAsset_getLength(file);
        buf.resize(fileLength);
        int64_t  readSize = AAsset_read(file,buf.data(),buf.size());
        uint8_t* imageBits = stbi_load_from_memory(buf.data(),buf.size(),&width,&height,&nrChannels,0);
        if (imageBits)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBits
            );
            stbi_image_free(imageBits);
        }
        else
        {
            stbi_image_free(imageBits);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    return textureID;
}