//
// Created by sergio on 3/26/2020.
//

#ifndef MY_APPLICATION_FBO_H
#define MY_APPLICATION_FBO_H
#define LOG_TAG "Debug"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define GL_CHECK(x)                                                                              \
    x;                                                                                           \
    {                                                                                            \
        GLenum glError = glGetError();                                                           \
        if(glError != GL_NO_ERROR) {                                                             \
            LOGE("glGetError() = %i (0x%.8x) at %s:%i\n", glError, glError, __FILE__, __LINE__); \
            exit(1);                                                                             \
        }                                                                                        \
    }

class FBO{
public:
    unsigned int ColorTexture;
    std::vector<unsigned  int> textures;
    unsigned int framebuffer;
    unsigned int width;
    unsigned int height;
        FBO(int w,int h,int ColorNum = 1){
            this->width = w;
            this->height = h;
            GL_CHECK(glGenFramebuffers(1,&framebuffer));
            for(int i =0;i<ColorNum;i++){
                unsigned int ColorTexture;
                glGenTextures(1,&ColorTexture);
                glBindTexture(GL_TEXTURE_2D, ColorTexture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                textures.push_back(ColorTexture);
            }

            ColorTexture = textures.at(0);
            glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
            int k = 0;
            unsigned int attachments[textures.size()];
            for(unsigned int texture:textures){
               // glBindTexture(GL_TEXTURE_2D,texture);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+k, GL_TEXTURE_2D, texture, 0);
                attachments[k]=GL_COLOR_ATTACHMENT0+k;

                k++;
            }

            glDrawBuffers(textures.size(),attachments);

            unsigned int rbo;
            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
            bool flag = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;
            glBindFramebuffer(GL_FRAMEBUFFER,0);
            glBindTexture(GL_TEXTURE_2D,0);

        }
        FBO(){

        }
        void bind(){
            glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
            glViewport(0,0,width,height);
        }
        void ubind(){
            glBindFramebuffer(GL_FRAMEBUFFER,0);
        }
        unsigned int getColorTexture(){

            return textures.at(0);
        }

};
class Quad{
public:
    unsigned int texture;
    std::vector<unsigned int> textures;
    unsigned int quadVAO, quadVBO;
    Shader shader;
    Quad(){

    }
    Quad(Shader shader){
        this->shader = shader;
        float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    }
    void Draw(){
        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        glBindVertexArray(quadVAO);
        for(unsigned int i = 0;i<textures.size();i++){
            glActiveTexture(GL_TEXTURE0+i);
            glBindTexture(GL_TEXTURE_2D,textures[i]);

            string name = "tex"+std::to_string(i);
            glUniform1i(glGetUniformLocation(this->shader.ID, name.c_str()), i);
            float k = 1;
        }

        glDrawArrays(GL_TRIANGLES,0,6);
        shader.ubind();
    }
    void setTexture(unsigned int tex){
        textures.push_back(tex);
        //this->texture = tex;
    }

};
#endif //MY_APPLICATION_FBO_H
