//
// Created by liuxin on 19-11-23.
//


#include "BaseOpenGL.h"


BaseOpenGL::BaseOpenGL() {
    if(ISDEBUG){
        ALOGD("BaseOpenGL");
    }
    program=-1;
    vertexs=new float[8];
    fragments=new float[8];
    //参考顶点坐标系
    float tempVertexs[8] = {
            1.0f,-1.0f,
            1.0f,1.0f,
            -1.0f,-1.0f,
            -1.0f,1.0f
    };
    memcpy(vertexs,tempVertexs, sizeof(tempVertexs));



    float tempFragments[8] ={
            1.0f,1.0f,
            1.0f,0.0f,
            0.0f,1.0f,
            0.0f,0.0f
    };
    memcpy(fragments,tempFragments, sizeof(tempFragments));


}

BaseOpenGL::~BaseOpenGL() {
    if(ISDEBUG){
        ALOGD("~BaseOpenGL");
    }
     delete []vertexs;
     delete []fragments;
}

void BaseOpenGL::setPixels(void *pixels, int picWidth, int picHeight) {

}

void BaseOpenGL::setYUVPixels(void *Y, void *U, void *V, int picWidth, int picHeight) {

}



