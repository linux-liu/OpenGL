//
// Created by liuxin on 19-11-24.
//

#ifndef OPENGL_OPENGLYUVFILTER_H
#define OPENGL_OPENGLYUVFILTER_H

#include "BaseOpenGL.h"
#include "../log/mylog.h"
#include "../util/ShaderUtils.h"
#include "../util/MatrixUtils.h"
class OpenGLYUVFilter: public BaseOpenGL {
private:
    GLuint textureIds[3]={0};
    GLint sampler_y=-1; //纹理
    GLint sampler_u=-1; //纹理
    GLint sampler_v=-1; //纹理
    void * y=NULL;
    void *u=NULL;
    void *v=NULL;

public:
    OpenGLYUVFilter();
    ~OpenGLYUVFilter();
    void onCreate();
    void onChange(int width,int height);
    void onDraw();
    void onDestory();
    void setYUVPixels(void *Y, void *U, void *V,int picWidth,int picHeight);

private:
    void setMatriex();
};


#endif //OPENGL_OPENGLYUVFILTER_H
