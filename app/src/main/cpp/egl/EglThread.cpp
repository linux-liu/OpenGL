//
// Created by liuxin on 19-11-12.
//


#include "EglThread.h"
#include "Egl_Helper.h"

EglThread::EglThread() {
    pthread_mutex_init(&pthreadMutex, NULL);

    pthread_cond_init(&pthreadCond, NULL);
    pthread = -1;
    surfaceHeight = 0;
    surfaceWidth = 0;
    nativeWindow = NULL;
    isChange = false;
    isCreate = false;
    isExit = false;
    isStart = false;
    isStart = false;
    rendType = OPENGL_RENDAR_AUTO;


}

EglThread::~EglThread() {

    nativeWindow = NULL;
    pthread_mutex_destroy(&pthreadMutex);
    pthread_cond_destroy(&pthreadCond);


    if (ISDEBUG) {
        ALOGD("~EglThread");
    }


}

void *eglThreadCallBack(void *context) {
    auto *eglThread = static_cast<EglThread *>(context);
    if (eglThread != NULL) {
        Egl_Helper *eglHelper = new Egl_Helper();
        int ret=eglHelper->init(eglThread->nativeWindow);

        if(ISDEBUG){
            ALOGE("ret=>%d",ret);
        }
        eglThread->isExit = false;


        while (true) {
          if (eglThread->isCreate) {
                eglThread->isCreate = false;
                if (eglThread->onCreate != NULL) {
                    eglThread->onCreate(eglThread->onCreateCtx);
                }

            }

            if (eglThread->isChange) {
                eglThread->isChange = false;
                if (eglThread->onChange != NULL) {
                    eglThread->onChange(eglThread->surfaceWidth, eglThread->surfaceHeight,
                                        eglThread->onChangeCtx);
                }
                eglThread->isStart = true;

            }

            if (eglThread->isChangeFilter) {
                eglThread->isChangeFilter = false;
                if (eglThread->onChangeFilter != NULL) {
                    eglThread->onChangeFilter(eglThread->surfaceWidth, eglThread->surfaceHeight,
                                              eglThread->onChangeFilterCtx);
                }
            }


            if (eglThread->isStart) {

                if (eglThread->onDraw != NULL) {
                    eglThread->onDraw(eglThread->onDrawCtx);
                }
                eglHelper->swapBuffers();

            }
            if (eglThread->isExit) {
                if (eglThread->onOwnDestory != NULL) {
                    eglThread->onOwnDestory(eglThread->onOwnDestoryCtx);
                }

                if(ISDEBUG){
                    ALOGD("isexit true");
                }

              eglHelper->destory();
                delete eglHelper;
                eglHelper = NULL;
                break;
            }
            if(!eglThread->isExit){
                if (eglThread->rendType == OPENGL_RENDAR_AUTO) {
                    //60帧每秒
                    usleep(1000 * 1000 / 60);
                } else {
                    pthread_mutex_lock(&eglThread->pthreadMutex);

                    pthread_cond_wait(&eglThread->pthreadCond, &eglThread->pthreadMutex);

                    pthread_mutex_unlock(&eglThread->pthreadMutex);


                }
            }

        }


    }
    return 0;


}

void EglThread::onSurfaceCreated(EGLNativeWindowType window) {

    isCreate = true;
    this->nativeWindow = window;
    pthread_create(&pthread, NULL, eglThreadCallBack, this);


}

void EglThread::onSurfaceChanged(int w, int h) {
    isChange = true;
    this->surfaceWidth = w;
    this->surfaceHeight = h;
    notifyDraw();
}

void EglThread::onSurfaceCreatedCallBack(EglThread::OnCreate create, void *ctx) {
    this->onCreate = create;
    this->onCreateCtx = ctx;
}

void EglThread::onSurfaceChangeCallBack(EglThread::OnChange change, void *ctx) {
    this->onChange = change;
    this->onChangeCtx = ctx;
}

void EglThread::onSurfaceDrawCallBack(EglThread::OnDraw draw, void *ctx) {
    this->onDraw = draw;
    this->onDrawCtx = ctx;
}

void EglThread::setRendType(int type) {
    this->rendType = type;

}

void EglThread::notifyDraw() {
    pthread_mutex_lock(&pthreadMutex);
    pthread_cond_signal(&pthreadCond);
    pthread_mutex_unlock(&pthreadMutex);


}

void EglThread::onDestory() {

    isExit = true;

    notifyDraw();
    pthread_join(pthread, NULL);
    nativeWindow = NULL;
    pthread = -1;
}

void EglThread::onSurfaceChangeFilter() {
    isChangeFilter = true;
    notifyDraw();
}

void EglThread::onSurfaceChangeFilterCallBack(EglThread::OnChangeFilter changeFilter, void *ctx) {
    this->onChangeFilter = changeFilter;
    this->onChangeFilterCtx = ctx;
}

void EglThread::onSurfaceOwnDestoryCallBack(EglThread::OnOwnDestory ownDestory, void *ctx) {
    this->onOwnDestory = ownDestory;
    this->onOwnDestoryCtx = ctx;
}



