package com.example.myapplication;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.PixelFormat;
import android.opengl.EGL14;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGL11;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.EGL14.EGL_OPENGL_ES2_BIT;
import static android.opengl.EGL14.EGL_OPENGL_ES_BIT;
//import static android.opengl

/**
 * A simple GLSurfaceView sub-class that demonstrate how to perform
 * OpenGL ES 2.0 rendering into a GL Surface. Note the following important
 * details:
 *
 * - The class must use a custom context factory to enable 2.0 rendering.
 *   See ContextFactory class definition below.
 *
 * - The class must use a custom EGLConfigChooser to be able to select
 *   an EGLConfig that supports 2.0. This is done by providing a config
 *   specification to eglChooseConfig() that has the attribute
 *   EGL10.ELG_RENDERABLE_TYPE containing the EGL_OPENGL_ES2_BIT flag
 *   set. See ConfigChooser class definition below.
 *
 * - The class must select the surface's format, then choose an EGLConfig
 *   that matches it exactly (with regards to red/green/blue/alpha channels
 *   bit depths). Failure to do so would result in an EGL_BAD_MATCH error.
 */

class GLView extends GLSurfaceView {
    private static String TAG = "GL2JNIView";
    private static final boolean DEBUG = false;


    public GLView(Context context) {
        super(context);
        //setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        //setEGLConfigChooser(8, 8, 8, 8, 16, 16);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8,8,8,8,24,0);
        setRenderer(new Renderer(context));
     //   init(true, 0, 0);
    }



    private static class Renderer implements GLSurfaceView.Renderer {
        /*
    static {
        try{
            System.load("src/main/jni/Assimp_libs/release/x86/libassimp.so");
        }
        catch(UnsatisfiedLinkError e){
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(0);
        }

    }
*/
    static {
            System.loadLibrary("native-lib");

        }



        private native void init();
        private  native void render();
        private native void surfaceChanged(int w,int h);
        private native void setAssetManager(AssetManager mgr);
        private native void sendIn(float a);
        private Context context;



        public void onDrawFrame(GL10 gl) {
            //GL2JNILib.step();

            render();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
           // GL2JNILib.init(width, height);
            surfaceChanged(width,height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            // Do nothing.
            //GLES20.glClearColor(1.f,0.f,0.f,1.f);
            //GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

            setAssetManager(context.getAssets());
            init();
            sendIn(4.2f);
        }
        public Renderer(Context c){
            context = c;
        }
    }
}