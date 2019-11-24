//
// Created by liuxin on 19-11-23.
//

#ifndef OPENGL_BASEOPENGL_H
#define OPENGL_BASEOPENGL_H

#include "GLES2/gl2.h"
#include <string.h>
#include "../log/mylog.h"
class BaseOpenGL {

public:
    GLuint  program=-1;
    GLuint  vertexShader=-1;
    GLuint  fragmentShader=-1;

    char *vertex=NULL; //顶点程序
    char *fragment=NULL; //渲染程序
    float *vertexs=NULL; //顶点坐标
    float *fragments=NULL; //渲染坐标

    GLint vPosition=-1; //获取顶点坐标变量
    GLint fPosition=-1;//获取渲染坐标变量


    GLint  uMatrixs=-1;//矩阵变换


    int  width=0;
    int  height=0;

    int pic_width=0;
    int pic_height=0;

    float matriex[16]={0};










public:
     BaseOpenGL();

     virtual void onCreate()=0;

     virtual void onChange(int width,int height)=0;

     virtual void onDraw()=0;

     virtual void setPixels(void *pixels, int picWidth, int picHeight);

     virtual void setYUVPixels(void *Y, void *U, void *V,int picWidth,int picHeight);

     virtual void onDestory()=0;



     virtual ~BaseOpenGL();

};


#endif //OPENGL_BASEOPENGL_H
