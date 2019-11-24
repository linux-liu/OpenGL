//
// Created by liuxin on 19-11-23.
//

#ifndef OPENGL_OPENGLGREYFILTER_H
#define OPENGL_OPENGLGREYFILTER_H

#include "BaseOpenGL.h"
#include "../log/mylog.h"
#include "../util/ShaderUtils.h"
#include "../util/MatrixUtils.h"
class OpenGLGreyFilter: public BaseOpenGL {
private:
    GLuint textureId=-1;
    GLint sTexture=-1; //纹理
    void * pixels=NULL;

public:
    OpenGLGreyFilter();
    ~OpenGLGreyFilter();
    void onCreate();
    void onChange(int width,int height);
    void onDraw();
    void onDestory();
    void setPixels(void *pixels, int picWidth, int picHeight);

private:
    void setMatriex();
};



#endif //OPENGL_OPENGLGREYFILTER_H
