//
// Created by liuxin on 19-11-9.
//

#ifndef OPENGL_EGL_HELPER_H
#define OPENGL_EGL_HELPER_H

#include "../log/mylog.h"
#include "EGL/egl.h"
#include "android/native_window.h"
class Egl_Helper {
public:
    EGLDisplay  mEglDisplay;
    EGLSurface  mEglSurface;
    EGLConfig  mEGlConfig;
    EGLContext mEGLContext;

public:
    Egl_Helper();
    int init(EGLNativeWindowType windowType);
    void  destory();
    int swapBuffers();
    ~Egl_Helper();
};


#endif //OPENGL_EGL_HELPER_H
