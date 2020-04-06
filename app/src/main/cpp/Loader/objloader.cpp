#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <glm/glm.hpp>
#include <android/asset_manager.h>

#include "objloader.hpp"
#include "../AssetsLoader.h"


bool loadOBJ(
        const char * path,
        std::vector<glm::vec3> & out_vertices,
        std::vector<glm::vec2> & out_uvs,
        std::vector<glm::vec3> & out_normals
){
    //printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    AAsset* fil = AAssetManager_open(mgr,path, AASSET_MODE_BUFFER);

    size_t fileLength = AAsset_getLength(fil);

    char* modelData = new char[fileLength];
    AAsset_read(fil, modelData, fileLength);
    std::string line;
    std::istringstream iss(modelData);
  while(std::getline(iss,line)){

      std::istringstream in(line);

      std::string type;
      in>>type;

      float x,y,z;
        if (type=="v"){

            in>>x;
            in>>y;
            in>>z;
            glm::vec3 vertex(x,y,z);
            temp_vertices.push_back(vertex);
        } else if (type=="vt"){
          glm::vec2 uv;

           //fscanf(file, "%f %f\n", &uv.x, &uv.y );
           in >> uv.x;
           in >> uv.y;
           // uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        } else if (type=="vn") {
           glm::vec3 normal;
            in >> normal.x;
            in >> normal.y;
            in >> normal.z;
            //fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if (type=="f"){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            //int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            char w;
            sscanf(line.c_str(),"%s %d/%d/%d %d/%d/%d %d/%d/%d\n",&w,&vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        glm::vec2 uv = temp_uvs[ uvIndex-1 ];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
        out_normals .push_back(normal);

    }

    return true;
}


