//
// Created by sergio on 12/24/2020.
//

#ifndef MY_APPLICATION_OPENGLTEXTURE_H
#define MY_APPLICATION_OPENGLTEXTURE_H


#include <string>

class Texture {
public:
    std::string name;
    unsigned int id;
    GLenum type = GL_TEXTURE_2D;
    unsigned int width;
    unsigned int height;
    GLenum format = GL_RGBA;

    void initialize(){

    }
    void Dispose();
};


#endif //MY_APPLICATION_OPENGLTEXTURE_H
