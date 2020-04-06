//
// Created by sergio on 2/13/2020.
//

#ifndef NATIVE_ACTIVITY_SHADER_MANAGER_H
#define NATIVE_ACTIVITY_SHADER_MANAGER_H


#include <ios>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLES3/gl3.h>
#include <android/log.h>
#include "AssetsLoader.h"

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly std
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
    {


        AAsset* file = AAssetManager_open(mgr,
                                          vertexPath, AASSET_MODE_BUFFER);

        size_t fileLength = AAsset_getLength(file);

        char* vShaderCode = new char[fileLength];
        AAsset_read(file, vShaderCode, fileLength);

        std::string line;
        std::string v(vShaderCode);
        std::istringstream iss(vShaderCode);

        while(std::getline(iss,line)){


        }
        vShaderCode[fileLength] = 0;







        AAsset* file1 = AAssetManager_open(mgr,
                                          fragmentPath, AASSET_MODE_BUFFER);
        size_t fileLength1 = AAsset_getLength(file1);
        char* fShaderCode = new char[fileLength1];
        AAsset_read(file1, fShaderCode, fileLength1);
        fShaderCode[fileLength1] = 0;

        // char* vShaderCode = lod->LoadtoChar(a);


         //char* fShaderCode = lod->LoadtoChar(a);
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX",vertexPath);
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT",fragmentPath);
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if (geometryPath != nullptr)
        {/*
            const char* gShaderCode;
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
            */
        }
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
            glAttachShader(ID, geometry);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM",vertexPath);
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != nullptr)
            glDeleteShader(geometry);

    }
    Shader(){

    }
    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }
    void ubind(){
        glUseProgram(0);
    }
    int getID(){
        return ID;
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type,const char* path)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                __android_log_print(ANDROID_LOG_DEBUG,"shader_name","%s",path);
                __android_log_print(ANDROID_LOG_DEBUG,"shader","%s",infoLog);

               // std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                __android_log_print(ANDROID_LOG_DEBUG,"shader","%s",infoLog);
               // std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif //NATIVE_ACTIVITY_SHADER_MANAGER_H