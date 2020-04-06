//
// Created by sergio on 3/25/2020.
//

#include "stb_image.h"

#ifndef MY_APPLICATION_MODELLOADER_H
#define MY_APPLICATION_MODELLOADER_H

#endif //MY_APPLICATION_MODELLOADER_H
struct Texture{
    unsigned int id;
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
        void LoadTexture(char* path){
            std::vector<uint8_t> buf;
            AAsset* file = AAssetManager_open(mgr,
                                              path, AASSET_MODE_BUFFER);

            size_t fileLength = AAsset_getLength(file);
            buf.resize(fileLength);
            int64_t  readSize = AAsset_read(file,buf.data(),buf.size());
              int imgWidth,imgHeight,channelCount;
              stbi_set_flip_vertically_on_load(1);
            uint8_t* imageBits = stbi_load_from_memory(buf.data(),buf.size(),&imgWidth,&imgHeight,&channelCount,0);
            GLenum format;
            if(channelCount==3){
                format = GL_RGB;
            }else{
                format = GL_RGBA;
            }

            Texture tex;
            glGenTextures(1,&tex.id);
            int k = tex.id;
            glBindTexture(GL_TEXTURE_2D,tex.id);
            glTexImage2D(GL_TEXTURE_2D,0,format,imgWidth,imgHeight,0,format,GL_UNSIGNED_BYTE,imageBits);
            stbi_image_free(imageBits);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            textures.push_back(tex);


        }


};
