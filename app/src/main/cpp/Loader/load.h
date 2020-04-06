//
// Created by sergio on 3/29/2020.
//

#ifndef MY_APPLICATION_LOAD_H
#define MY_APPLICATION_LOAD_H
using namespace glm;
class LoadTrans{
public:
    vec3 position;
    vec3 rotation;
    LoadTrans(char* path){
        string m = "Models/";
        m = m+path+".pos";
        AAsset* fil = AAssetManager_open(mgr,m.c_str(), AASSET_MODE_BUFFER);

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
            if (type=="p"){
                in>>x;
                in>>y;
                in>>z;
                position = vec3(x,y,z);
                __android_log_print(ANDROID_LOG_INFO,"print","position");
                __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",x);
                __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",y);
                __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",z);
            }
            else if(type=="r"){
                in>>x;
                in>>y;
                in>>z;
                rotation = vec3(x,y,z);
                __android_log_print(ANDROID_LOG_INFO,"print","rotation");
                __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",x);
                __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",y);
                __android_log_print(ANDROID_LOG_INFO,"print","x %f\n",z);
            }
            else if(type=="d"){

            }

    }

    }
    LoadTrans(){

    }
};
#endif //MY_APPLICATION_LOAD_H
