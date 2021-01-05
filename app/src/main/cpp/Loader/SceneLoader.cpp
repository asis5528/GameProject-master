//
// Created by sergio on 7/13/2020.
//

#include <android/asset_manager.h>
#include <sstream>
#include "SceneLoader.h"
#include "../../../../../../../Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/android/log.h"
#include "../AssetsLoader.h"
#include <string>
#include <glm/ext.hpp>

#include "../Mesh/Mesh.h"
#include "../stb_image.h"
#include "../OpenGL/Material.h"
#include "../Animation/AnimationData.h"
#include "../Animation/Animation.h"
#include "../OpenGL/OpenGLTexture.h"
void SceneLoader::loadPrimitive(std::string path,Scene *sc) {
    path+=".pribln";
    AAsset* file = AAssetManager_open(mgr,path.c_str(),AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    char* modelData = new char[fileLength];
    AAsset_read(file, modelData, fileLength);
    modelData[fileLength] = 0;
    AAsset_close(file);
    std::istringstream iff(modelData);
    std::string nam;
    std::string n;

    //iff >> x >> y>> z;
    iff >> n >> nam;
    __android_log_print(ANDROID_LOG_INFO,"print","x %s\n",nam.c_str());
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<float> boneDatas;
    std::vector<std::string> boneList;
    std::vector<BoneInfo> boneInfo;
    std::string line;

    int state = 0;
    glm::vec3 minBounds;
    glm::vec3 maxBounds;
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
        else if (state == 3) {
          //  std::cout << "loading bone/n";
            std::string line2;
            std::getline(iff, line2);
            std::istringstream iss(line2);
            float boneData;
            if(n!=""){
            boneData = std::stof(n);
            boneDatas.push_back(boneData);
            while (iss >> boneData) {
                boneDatas.push_back(boneData);
            }
            }
            state = 4;

        }
        else if (state == 4) {
           // std::cout << "loading bone offset matrix /n";
            std::string line2;
            std::getline(iff, line2);
            std::istringstream iss(line2);
            std::string boneName;
            //boneList.push_back(n);
            BoneInfo bi;
            bi.name = n;
            float matrix[16];
            for (int i = 0; i < 16; i++) {
                float value;
                iss >> value;
                matrix[i] = value;

            }
            bi.BoneOffset = glm::make_mat4(matrix);
            boneInfo.push_back(bi);
            while (iss >> boneName) {
                bi.name = boneName;
                float matrix[16];
                for (int i = 0; i < 16; i++) {
                    float value;
                    iss >> value;
                    matrix[i] = value;

                }
                bi.BoneOffset = glm::make_mat4(matrix);
                boneInfo.push_back(bi);

            }

            float k = 0.1;
        }
        if (n == "vertexDatas") {
            state = 1;
            iff >> minBounds.x; iff >> minBounds.y; iff >> minBounds.z; iff >> maxBounds.x; iff >> maxBounds.y; iff >> maxBounds.z;

        }
    }
    std::vector<Vertex> verts;
    std::vector<VertexBoneData> bones;
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
    for (int i = 0; i < boneDatas.size() / 8; i++) {
        VertexBoneData bone;
        bone.IDs[0] = boneDatas[i * 8 + 0];
        bone.IDs[1] = boneDatas[i * 8 + 1];
        bone.IDs[2] = boneDatas[i * 8 + 2];
        bone.IDs[3] = boneDatas[i * 8 + 3];
        bone.Weights[0]= boneDatas[i * 8 + 4];
        bone.Weights[1] = boneDatas[i * 8 + 5];
        bone.Weights[2] = boneDatas[i * 8 + 6];
        bone.Weights[3] = boneDatas[i * 8 + 7];
        bones.push_back(bone);
    }

    Mesh mesh = Mesh(verts,indices,bones);
    mesh.minBounds = minBounds;
    mesh.maxBounds = maxBounds;
    mesh.boneInfo=boneInfo;

    sc->pushMesh(mesh);
    OpenGLMesh openGlMesh;
    openGlMesh.init(mesh.vertices,mesh.indices,mesh.bones);
    mesh.disposeMesh();
    sc->pushGLMesh(openGlMesh);
    //sc->pushGLMesh()
}


static void loadAnimation(std::string path,Animation &animation) {
    std::string fullname = path + ".anibln";


    AAsset* file = AAssetManager_open(mgr,fullname.c_str(),AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    char* modelData = new char[fileLength];
    AAsset_read(file, modelData, fileLength);
    modelData[fileLength] = 0;
    AAsset_close(file);
    std::istringstream iff(modelData);
    std::string line;
    //AnimationData adata;

    std::string parent;
    std::string child;
    //std::getline(iff, line);
    //iff >> parent; iff >> child;
    std::string j;
    iff >> animation.name;
    float duration;
    iff >> duration;
    float tick;
    iff >> tick;
    unsigned int keyframeSize = 0;
    iff >> keyframeSize;
    unsigned int BoneIndex = 0;

    animation.duration = duration;
    animation.ticksperSec = tick;
    std::string useless;
    iff >> useless;
    unsigned int actionSize;
    iff >> actionSize;
    std::vector<AnimationAction> actions;

    for (unsigned int i = 0; i < actionSize; i++) {
        std::cout << "lets start animation : " <<i <<"\n";
        std::string name;
        float x, y;
        iff >> name;
        iff >> x;
        iff >> y;
        AnimationAction ac;
        ac.name = name;
        ac.range = glm::vec2(x, y);
        actions.push_back(ac);
    }
    //std::cout << "lets start animation" << "\n";
    animation.actions = actions;
    unsigned int state = 0;
    std::vector<std::vector<AnimationTransformation>> AnimationTransformationData;
    std::vector<AnimationTransformation> AnimT;
    std::vector<AnimationTransformation>* AT = &AnimT;

    while (std::getline(iff, line)) {

        std::string firstValue;
        iff >> firstValue;
        if (firstValue.size() > 0) {

            if (firstValue.at(0) == '#') {
                //state = 1;

                iff >> firstValue;
                //std::cout << "bones " << AnimationTransformationData.size() << "\n";
                AnimationTransformationData.resize(AnimationTransformationData.size() + 1);
                AT = &AnimationTransformationData[AnimationTransformationData.size()-1];
            }
            if (firstValue == "AnimationTree") {

                iff >> parent; iff >> child;
                animation.adata.name = parent;
                AnimationData childdata;
                childdata.name = child;
                childdata.animationTransformation = AnimationTransformationData[BoneIndex];
                BoneIndex+=1;
                animation.adata.childAnimationData.push_back(childdata);
                state = 1;
                iff >> firstValue;
            }

            //if()
            if (state == 0) {

                AnimationTransformation at;
                glm::vec3 pos;
                pos.x = std::stof(firstValue);
                iff >> pos.y;
                iff >> pos.z;
                at.position = pos;
                glm::vec3 scale;
                iff >> scale.x;
                iff >> scale.y;
                iff >> scale.z;
                at.scale = scale;
                glm::quat rot;
                iff >> rot.w;
                iff >> rot.x;
                iff >> rot.y;
                iff >> rot.z;
                at.rotation = rot;
                float time;
                iff >> time;
                at.time = time;
                std::string line;
                AT->push_back(at);
                //iff >> line;
                //iff >> line;
                float j = 5;


            }
            else if (state == 1) {
                std::string parent = firstValue;
                std::string child;
                iff >> child;
                bool node = SceneLoader::searchNode(animation.adata, parent, child, AnimationTransformationData[BoneIndex]);
                //node->animationTransformation = AnimationTransformationData[BoneIndex];
                BoneIndex += 1;
                //AnimationData childData;
                //childData.name = child;
                //parentdata->childAnimationData.push_back(childdata);
                //	float n = 1;
            }

        }


    }

    float k = 1.334;


}
bool  SceneLoader::searchNode(AnimationData& adata, std::string Parentname,std::string Childname,std::vector<AnimationTransformation> &ATT) {
    if (Parentname == adata.name) {
        AnimationData childData;
        childData.name = Childname;
        childData.animationTransformation = ATT;
        adata.childAnimationData.push_back(childData);
        return true;


    }
    for (int i = 0; i < adata.childAnimationData.size(); i++) {
        SceneLoader::searchNode(adata.childAnimationData[i], Parentname, Childname,ATT);
    }
    return true;

}



void SceneLoader::loadSceneData(std::string path,Scene *sc) {
    std::string directory = getPathName(path);
    AAsset* file = AAssetManager_open(mgr,path.c_str(),AASSET_MODE_BUFFER);
    size_t fileLength = AAsset_getLength(file);
    char* modelData = new char[fileLength];
    AAsset_read(file, modelData, fileLength);
    modelData[fileLength] = 0;
    AAsset_close(file);
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
        else if(currentData=="#animations"){
            state=2;
        }
        else if (currentData == "#lights") {
            state = 3;
        }
        else if (currentData == "#textures") {
            state = 4;
        }
        else if (currentData == "#objects") {
            state = 5;
        }
        else if (state == 1) {
            std::string finalPathName = directory+"primitives/" + currentData;
            SceneLoader::loadPrimitive(finalPathName,sc);
        }
        else if (state == 4) {
            std::string type = currentData;
            std::string path;
            iss >> path;
            std::string fileName =  getFileName(path);
            std::string finalPath = directory+"textures/"+fileName;
            if (type == "2D") {
                loadTexture(finalPath, sc->getTextures());
            }
            else if(type=="cubemap"){
                loadCubeMapTexture(finalPath,sc->getTextures());
            }
        }

        else if (state == 2) {
            std::string finalPathName = directory+"animations/"+currentData;
            Animation animation;
            loadAnimation(finalPathName,animation);
            sc->pushAnimation(animation);
        }

        else if (state == 3) {

        }
        else if (state == 5) {
            std::string name = currentData;
            glm::vec3 pos;
            glm::vec3 scale;
            glm::vec3 rotation;
            glm::vec3 minBounds;
            glm::vec3 maxBounds;
            unsigned int primitiveIndex;
            unsigned int animationSize = 0;
            unsigned int animationID = 0;
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
            iss >> minBounds.x;
            iss >> minBounds.y;
            iss >> minBounds.z;
            iss >> maxBounds.x;
            iss >> maxBounds.y;
            iss >> maxBounds.z;
            iss >> primitiveIndex;
            iss >> animationSize;
            for(unsigned int i=0;i<animationSize;i++){
                iss >> animationID;
            }
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
            object.scene = sc;
            object.init(primitiveIndex,name,def);
            object.position = pos;
            object.rotation = rotation;
            object.scale = scale;
            object.dimension = glm::vec3();
            object.seTexturesID(textureIDS);
            if(animationSize>0){
                object.animationIDs.push_back(animationID);
            }

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
    AAsset* file = AAssetManager_open(mgr,path, AASSET_MODE_BUFFER);

    size_t fileLength = AAsset_getLength(file);
    buf.resize(fileLength);
    int64_t  readSize = AAsset_read(file,buf.data(),buf.size());
    buf[fileLength] = 0;
    AAsset_close(file);
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