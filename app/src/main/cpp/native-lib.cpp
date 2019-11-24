#include <jni.h>
#include <string>
#include "opengl/OpenGLHelper.h"
#include "opengl/OpenGLYUVFilter.h"




OpenGLHelper *mOpenGLHelper=NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_liuxin_opengl_OpenGlUtils_onSurfaceCreated(JNIEnv *env, jobject thiz, jobject surface) {
     if(mOpenGLHelper==NULL){
         mOpenGLHelper=new OpenGLHelper();
         mOpenGLHelper->onCreate(env,surface);
     }

}


extern "C"
JNIEXPORT void JNICALL
Java_com_liuxin_opengl_OpenGlUtils_onSurfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                    jint height) {

    if(mOpenGLHelper!=NULL){

        mOpenGLHelper->onChange(width,height);
    }

}extern "C"
JNIEXPORT void JNICALL
Java_com_liuxin_opengl_OpenGlUtils_imgData(JNIEnv *env, jobject thiz, jint w, jint h, jint length,
                                           jbyteArray _data) {

    if(mOpenGLHelper!=NULL){
       jbyte *data=env->GetByteArrayElements(_data, NULL);
        mOpenGLHelper->setPixels(data,w,h,length);
        env->ReleaseByteArrayElements(_data,data,0);
    }

}extern "C"
JNIEXPORT void JNICALL
Java_com_liuxin_opengl_OpenGlUtils_onSurfaceDestory(JNIEnv *env, jobject thiz) {

    if(mOpenGLHelper!=NULL){
        mOpenGLHelper->onDestroySurface();
        delete mOpenGLHelper;
        mOpenGLHelper=NULL;
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_liuxin_opengl_OpenGlUtils_onSurfaceChangeFilter(JNIEnv *env, jobject thiz) {
    if(mOpenGLHelper!=NULL){
        mOpenGLHelper->changeFilter();
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_liuxin_opengl_OpenGlUtils_setYUVData(JNIEnv *env, jobject thiz, jbyteArray y, jbyteArray u,
                                              jbyteArray v, jint width, jint height) {
    if(mOpenGLHelper!=NULL){
        jbyte *n_y=env->GetByteArrayElements(y, NULL);
        jbyte *n_u=env->GetByteArrayElements(u, NULL);
        jbyte *n_v=env->GetByteArrayElements(v, NULL);
        mOpenGLHelper->setYUVPixels(n_y,n_u,n_v,width,height);
        env->ReleaseByteArrayElements(y,n_y,0);
        env->ReleaseByteArrayElements(u,n_u,0);
        env->ReleaseByteArrayElements(v,n_v,0);
    }
}