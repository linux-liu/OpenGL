//
// Created by liuxin on 19-11-23.
//

#include "OpenGLHelper.h"


void callbackSurfaceCreate(void *context){
    OpenGLHelper *openGlHelper= static_cast<OpenGLHelper *>(context);
    if(openGlHelper!=NULL){
        if(openGlHelper->baseOpenGl!=NULL){
            openGlHelper->baseOpenGl->onCreate();
        }

    }
}

void callbackSurfaceChange(int width,int height, void *context){
    OpenGLHelper *openGlHelper= static_cast<OpenGLHelper *>(context);
    if(openGlHelper!=NULL){
        if(openGlHelper->baseOpenGl!=NULL){
            openGlHelper->baseOpenGl->onChange(width,height);
        }
    }
}

void callbackSurfaceDraw(void *context){
    OpenGLHelper *openGlHelper= static_cast<OpenGLHelper *>(context);
    if(openGlHelper!=NULL){
        if(openGlHelper->baseOpenGl!=NULL){
            openGlHelper->baseOpenGl->onDraw();
        }
    }
}

void callbackChangeFilter(int width,int height,void *context){
    OpenGLHelper *openGlHelper= static_cast<OpenGLHelper *>(context);
    if(openGlHelper!=NULL){
        if(openGlHelper->baseOpenGl!=NULL){
            openGlHelper->baseOpenGl->onDestory();
            delete openGlHelper->baseOpenGl;
            openGlHelper->baseOpenGl=NULL;
        }
        openGlHelper->baseOpenGl=new OpenGLGreyFilter();
        openGlHelper->baseOpenGl->onCreate();
        openGlHelper->baseOpenGl->onChange(width,height);
        openGlHelper->baseOpenGl->setPixels(openGlHelper->mPixels,openGlHelper->picWidth,openGlHelper->picHeight);
        openGlHelper->eglThread->notifyDraw();

    }
}

void callbackSurfacOwnDestory(void *context){
    OpenGLHelper *openGlHelper= static_cast<OpenGLHelper *>(context);
    if(openGlHelper!=NULL){
        if(openGlHelper->baseOpenGl!=NULL){
            openGlHelper->baseOpenGl->onDestory();
            delete openGlHelper->baseOpenGl;
            openGlHelper->baseOpenGl=NULL;
        }
    }
}

void OpenGLHelper::onCreate(JNIEnv *env, jobject surface) {

    windowType=ANativeWindow_fromSurface(env,surface);
    eglThread=new EglThread();
    eglThread->setRendType(OPENGL_RENDAR_MANUAL);
    eglThread->onSurfaceCreatedCallBack(callbackSurfaceCreate,this);
    eglThread->onSurfaceChangeCallBack(callbackSurfaceChange,this);
    eglThread->onSurfaceDrawCallBack(callbackSurfaceDraw,this);
    eglThread->onSurfaceChangeFilterCallBack(callbackChangeFilter,this);
    eglThread->onSurfaceOwnDestoryCallBack(callbackSurfacOwnDestory,this);

     baseOpenGl=new OpenGLYUVFilter();
    eglThread->onSurfaceCreated(windowType);
}

void OpenGLHelper::onChange(int width, int height) {

    if(eglThread!=NULL){
        eglThread->onSurfaceChanged(width,height);
    }
}

OpenGLHelper::OpenGLHelper() {

}

OpenGLHelper::~OpenGLHelper() {

}

void OpenGLHelper::onDestroySurface() {

    if(eglThread){
        eglThread->onDestory();
        delete  eglThread;
        eglThread=NULL;
    }
    if(windowType){
      ANativeWindow_release(windowType);
      windowType=NULL;
    }


    if(mPixels!=NULL){
        free(mPixels);
        mPixels=NULL;
    }

    if(y){
        free(y);
        y=NULL;
    }

    if(u){
        free(u);
        u=NULL;
    }

    if(v){
        free(v);
        v=NULL;
    }
}

void OpenGLHelper::setPixels(void *pixels, int picWidth, int picHeight,int length) {
    if(mPixels!=NULL){
        free(mPixels);
        mPixels=NULL;
    }
    this->picWidth=picWidth;
    this->picHeight=picHeight;

    mPixels=malloc(length);
    memcpy(mPixels,pixels,length);
    if(baseOpenGl!= NULL){
        baseOpenGl->setPixels(mPixels,picWidth,picHeight);
    }
    if(eglThread!=NULL){
        eglThread->notifyDraw();
    }
}

void OpenGLHelper::changeFilter() {
     if(eglThread!=NULL){
         eglThread->onSurfaceChangeFilter();
     }
}

void OpenGLHelper::setYUVPixels(void *Y, void *U, void *V, int picWidth, int picHeight) {
    if(picWidth!=this->picWidth||picHeight!=this->picHeight){
        this->picWidth=picWidth;
        this->picHeight=picHeight;
        if(y){
            free(y);
            y=NULL;
        }
        if(u){
            free(u);
            u=NULL;
        }
        if(v){
            free(v);
            v=NULL;
        }
        y=malloc(picWidth*picHeight);
        u=malloc(picWidth*picHeight/4);
        v=malloc(picWidth*picHeight/4);

    }
    memcpy(y,Y,picWidth*picHeight);
    memcpy(u,U,picWidth*picHeight/4);
    memcpy(v,V,picWidth*picHeight/4);

    if(baseOpenGl!= NULL){
        baseOpenGl->setYUVPixels(y,u,v,picWidth,picHeight);
    }

    if(eglThread!=NULL){
        eglThread->notifyDraw();
    }
}
