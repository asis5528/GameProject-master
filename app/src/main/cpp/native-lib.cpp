#include <jni.h>
#include <string>
#include <android/log.h>
#include <glm/glm.hpp>
#include <GLES3/gl3.h>
#include <android/asset_manager_jni.h>
#include "Engine.h"
#include "AssetsLoader.h"
#include "Inputs/Touch.h"


#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
AAssetManager *mgr;
Engine *engine;
Touch touch;


extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_GLView_00024Renderer_setAssetManager(
        JNIEnv *env,
        jobject,jobject assetManager) {
    mgr = AAssetManager_fromJava(env,assetManager);

    // env->DeleteGlobalRef(assetManager);



}


extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_GLView_00024Renderer_init(
        JNIEnv *env,
        jobject) {
    engine = new Engine();
    engine->init();
    //ren.init();
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_GLView_00024Renderer_render(
        JNIEnv *env,
        jobject /* this */) {
    engine->render();
    //ren.render();
}
extern  "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_GLView_TouchDownCallBack(JNIEnv *env,jobject /* this */,jfloat x,jfloat y,jint action){
    engine->TouchCallBack(x,y,action);
    //__android_log_print(ANDROID_LOG_INFO,"print"," TouchCallBack");
    touch.setTouchState(action);
    touch.setTouchCoordinates(x,y);

}
extern  "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_GLView_TouchMoveCallBack(JNIEnv *env,jobject /* this */,jfloat x,jfloat y){
    touch.setTouchCoordinates(x,y);
   // engine->TouchCallBack(x,y,action);
    //__android_log_print(ANDROID_LOG_INFO,"print"," TouchCallBack");
  //  touch.setTouchState(action);
  // touch.setTouchCoordinates(x,y);

}


extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_GLView_00024Renderer_surfaceChanged(
        JNIEnv *env,
        jobject /* this */,jint w,jint h) {
    engine->surfaceChanged(w,h);
    touch.setResolution(w,h);
    //ren.render();
}
