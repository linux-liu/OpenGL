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
    //形成第一个顶点到第三个顶点形成一个三角形
    //第二个到第四个顶点形成另一个三角形 这两个三角形合成一个四边形
    float tempVertexs[8] = {
            1.0f,-1.0f, //右下
            1.0f,1.0f, //右上
            -1.0f,-1.0f, //左下
            -1.0f,1.0f //左上
    };
    memcpy(vertexs,tempVertexs, sizeof(tempVertexs));



    float tempFragments[8] ={
            1.0f,1.0f, // 纹理坐标 右上  计算机坐标 右下
            1.0f,0.0f, //纹理坐标 右下    计算机坐标 右上
            0.0f,1.0f, //纹理坐标 左上    计算机坐标 左下
            0.0f,0.0f //纹理坐标 左下     计算机组别 左上
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



