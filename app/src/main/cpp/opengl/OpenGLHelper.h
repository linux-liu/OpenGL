//
// Created by liuxin on 19-11-23.
//

#ifndef OPENGL_OPENGLHELPER_H
#define OPENGL_OPENGLHELPER_H

#include <EGL/eglplatform.h>
#include "../egl/EglThread.h"
#include "android/native_window_jni.h"
#include "BaseOpenGL.h"
#include "OpenGLCommonFilter.h"
#include "OpenGLGreyFilter.h"
#include "OpenGLYUVFilter.h"

class OpenGLHelper {

public:
    EGLNativeWindowType windowType=NULL;
    EglThread *eglThread=NULL;
    void *mPixels=NULL;
    BaseOpenGL *baseOpenGl=NULL;

    int picWidth;
    int picHeight;

    void *y=NULL;

    void *u=NULL;

    void *v=NULL;


public:
    OpenGLHelper();
    ~OpenGLHelper();
    void  onCreate(JNIEnv *env,jobject surface);
    void  onChange(int width,int height);

    void  onDestroySurface();

    void  changeFilter();

    void  setPixels(void *pixels, int picWidth, int picHeight,int length);

    void setYUVPixels(void *Y, void *U, void *V,int picWidth,int picHeight);


};


#endif //OPENGL_OPENGLHELPER_H
