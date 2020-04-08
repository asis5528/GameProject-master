//
// Created by sergio on 3/25/2020.
//

#include "stb_image.h"

#ifndef MY_APPLICATION_MODELLOADER_H
#define MY_APPLICATION_MODELLOADER_H

#endif //MY_APPLICATION_MODELLOADER_H

struct Texture{
    unsigned int id;
    GLenum type = GL_TEXTURE_2D;

};
class Model{
    public:
    Mesh mesh;
    std::vector<Texture> textures;
        Model(char* path){
            std::vector<GLushort> inds;
            std::vector<glm::vec3> verts;
            std::vector<glm::vec2> uv;
            std::vector<glm::vec3> norm;
            string m = "Models/";
            m = m+path;
            loadOBJ(m.c_str(),verts,uv,norm);

            std::vector<glm::vec3> indexed_vertices;
            std::vector<glm::vec2> indexed_uvs;
            std::vector<glm::vec3> indexed_normals;
            indexed_uvs.size();
            indexed_normals.size();
            indexed_vertices.size();
            indexVBO(verts,uv,norm,inds,indexed_vertices,indexed_uvs,indexed_normals);

            std::vector<Vertex> vertData;
            for(int i =0;i<indexed_vertices.size();i++){
                Vertex v;
                v.Position = indexed_vertices.at(i);
                v.Normal = indexed_normals.at(i);
                v.TexCoords = indexed_uvs.at(i);
                vertData.push_back(v);
            }
            mesh = Mesh(vertData,inds);

        }
        Model(){

        }
        void Draw(Shader shader){
            mesh.draw(shader);
        }
        void LoadTexture(char* path,GLenum type = GL_TEXTURE_2D){

              int imgWidth,imgHeight,channelCount;
              stbi_set_flip_vertically_on_load(1);
            unsigned  char* data;
           data = loadTextureBuffer(path,&imgWidth,&imgHeight,&channelCount);
            GLenum format;
            if(channelCount==3){
                format = GL_RGB;
            }else{
                format = GL_RGBA;
            }

            Texture tex;

            tex.type = type;
            glGenTextures(1,&tex.id);
            textures.push_back(tex);
            glBindTexture(type,tex.id);
            glTexImage2D(type,0,format,imgWidth,imgHeight,0,format,GL_UNSIGNED_BYTE,data);
            stbi_image_free(data);
            glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameterf(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



        }

        void addTexture(Texture tex){
            textures.push_back(tex);
        }

    void LoadCubeTexture(vector<string> paths,GLenum type = GL_TEXTURE_CUBE_MAP){
        Texture tex;

        tex.type = type;
        glGenTextures(1,&tex.id);
        textures.push_back(tex);
        glBindTexture(GL_TEXTURE_CUBE_MAP,tex.id);

        int imgWidth,imgHeight,channelCount;
        stbi_set_flip_vertically_on_load(1);

        unsigned  char* data;
        for(GLuint i =0;i<paths.size();i++){
            data = loadTextureBuffer(paths[i].c_str(),&imgWidth,&imgHeight,&channelCount);
            GLenum format;
            if(channelCount==3){
                format = GL_RGB;
            }else{
                format = GL_RGBA;
            }
            if(data){
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(type);
                stbi_image_free(data);
            }

        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



    }

private:
    uint8_t *loadTextureBuffer(const char* path,int *imgWidth,int *imgHeight,int *channelCount){
        std::vector<uint8_t> buf;
        string front = "Textures/";
        front =front+path;
        AAsset* file = AAssetManager_open(mgr,
                                          front.c_str(), AASSET_MODE_BUFFER);

        size_t fileLength = AAsset_getLength(file);
        buf.resize(fileLength);
        int64_t  readSize = AAsset_read(file,buf.data(),buf.size());

        stbi_set_flip_vertically_on_load(1);
        uint8_t* imageBits = stbi_load_from_memory(buf.data(),buf.size(),imgWidth,imgHeight,channelCount,0);
        buf.clear();
        return imageBits;

        }


};
