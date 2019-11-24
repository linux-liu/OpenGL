//
// Created by liuxin on 19-11-12.
//

#ifndef OPENGL_EGLTHREAD_H
#define OPENGL_EGLTHREAD_H


#include "pthread.h"
#include "android/native_window.h"
#include "../log/mylog.h"
#include "GLES2/gl2.h"
#include "EGL/eglplatform.h"
#include "Egl_Helper.h"
#include <unistd.h>
#define  OPENGL_RENDAR_AUTO 1
#define  OPENGL_RENDAR_MANUAL 2

class EglThread {
public:
    pthread_t pthread=-1;
    pthread_cond_t pthreadCond;
    pthread_mutex_t pthreadMutex;
    EGLNativeWindowType nativeWindow=NULL;

    int surfaceWidth=0;
    int surfaceHeight=0;
    bool  isCreate= false;
    bool  isChange= false;
    bool  isExit= false;
    bool  isStart= false;
    bool  isChangeFilter= false;

    typedef void (*OnCreate)(void *ctx);

    typedef void (*OnChange)(int w,int h,void *ctx);

    typedef void (*OnDraw)(void *ctx);

    typedef void  (*OnChangeFilter)(int w,int h,void *ctx);

    typedef void  (*OnOwnDestory)(void*ctx);
    OnCreate  onCreate=NULL;
    OnChange  onChange=NULL;
    OnDraw  onDraw=NULL;


    OnChangeFilter  onChangeFilter=NULL;
    OnOwnDestory onOwnDestory=NULL;

    void *onCreateCtx=NULL;
    void  *onChangeCtx=NULL;
    void  *onDrawCtx=NULL;

    void  *onOwnDestoryCtx=NULL;

    void *onChangeFilterCtx=NULL;
    int rendType=OPENGL_RENDAR_AUTO;


public:
    EglThread();
    ~EglThread();
    void  onSurfaceCreated(EGLNativeWindowType window);
    void  onSurfaceChanged(int w,int h);
    void  onSurfaceChangeFilter();




    void  onSurfaceCreatedCallBack(OnCreate create, void *ctx);
    void  onSurfaceChangeCallBack(OnChange change, void *ctx);
    void  onSurfaceDrawCallBack(OnDraw draw, void *ctx);
    void  onSurfaceChangeFilterCallBack(OnChangeFilter changeFilter, void *ctx);
    void  onSurfaceOwnDestoryCallBack(OnOwnDestory ownDestory, void *ctx);
    void  setRendType(int type);

    void onDestory();

    void notifyDraw();


};


#endif //OPENGL_EGLTHREAD_H
