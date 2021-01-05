//
// Created by sergio on 12/24/2020.
//

#include <GLES3/gl3.h>
#include "OpenGLTexture.h"

void Texture::Dispose(){
    glDeleteTextures(1,&id);
}