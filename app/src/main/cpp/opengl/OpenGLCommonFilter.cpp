//
// Created by liuxin on 19-11-23.
//

#include "OpenGLCommonFilter.h"

OpenGLCommonFilter::OpenGLCommonFilter() {
    vertex = "attribute vec4 v_Position;\n"
             "attribute vec2 f_Position;\n"
             "varying vec2 ft_Position;\n"
             "uniform mat4 u_Matrix;\n"
             "void main() {\n"
             "    ft_Position = f_Position;\n"
             "    gl_Position = v_Position*u_Matrix;\n"
             "}";


    fragment = "precision mediump float;\n"
               "varying vec2 ft_Position;\n"
               "uniform sampler2D sTexture;\n"
               "void main() {\n"
               "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
               "}";
}



void OpenGLCommonFilter::onCreate() {


    if(ISDEBUG){
        ALOGI("callbackSurfaceCreate");
    }
    program=createProgram(vertex,fragment,&vertexShader,&fragmentShader);
    if(ISDEBUG){
        ALOGI("program%d",program);
    }



    vPosition = glGetAttribLocation(program, "v_Position");
    fPosition=glGetAttribLocation(program,"f_Position");

    sTexture=glGetUniformLocation(program,"sTexture");
    uMatrixs=glGetUniformLocation(program,"u_Matrix");

    if(ISDEBUG){
        ALOGI("vPosition=>%d,fPosition=>%d,sTexture>%d,Matrixs=>%d",vPosition,fPosition,sTexture,uMatrixs);
    }

    //获取纹理绑定纹理
    glGenTextures(1,&textureId);
    glBindTexture(GL_TEXTURE_2D,textureId);

    if(ISDEBUG){
        ALOGI("textureId=>%d",textureId);
    }
    //设置参数
    //填充方式x y轴
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    //缩放方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    //解除绑定
    glBindTexture(GL_TEXTURE_2D,0);
    if(ISDEBUG){
        ALOGI("AttribLacation%d",vPosition);
    }
}

void OpenGLCommonFilter::onChange(int width, int height) {
    glViewport(0,0,width,height);
    if(ISDEBUG){
        ALOGD("onChange w=>%d h=>%d pw=>%d,ph=>%d" ,width,height,pic_width,pic_height);

    }
    this->width=width;
    this->height=height;
    setMatriex();

}

void OpenGLCommonFilter::onDraw() {
    if(ISDEBUG){
        ALOGI("callbackSurfaceDraw");
    }

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //一定要写
    glUseProgram(program);

    //矩阵变换关联
    glUniformMatrix4fv(uMatrixs,1,GL_TRUE,matriex);
    //激活设置纹理,要一致0
    glActiveTexture(GL_TEXTURE5);

    //重新绑定
    glBindTexture(GL_TEXTURE_2D,textureId);
    glUniform1i(sTexture,5);
    if(pixels!=NULL){
        if(ISDEBUG){
            ALOGD("绘制中");
        }
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pic_width,pic_height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
    }
    //反射使参数可用
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition,2,GL_FLOAT, false,8,vertexs);

    glEnableVertexAttribArray(fPosition);
    glVertexAttribPointer(fPosition,2,GL_FLOAT, false,8,fragments);


    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    //解除绑定
    glBindTexture(GL_TEXTURE_2D,0);

}

void OpenGLCommonFilter::setPixels(void *pixels, int picWidth, int picHeight) {

    this->pixels=pixels;
    this->pic_width=picWidth;
    this->pic_height=picHeight;
    if(picWidth>0&&picHeight>0){
        setMatriex();
    }
}



void OpenGLCommonFilter::setMatriex() {
    init(matriex);

    if (pic_width > 0 && pic_height > 0) {
        double screen_r = 1.0 * width / height;
        double picture_r = 1.0 * pic_width / pic_height;
        if (screen_r < picture_r) {
            //高度缩放
            double r = height / (1.0 * width / pic_width * pic_height);
            projection(-1, 1, r, -r, matriex);

        } else {
            //宽度缩放
            double r = width / (1.0 * height / pic_height * pic_width);

            projection(-r, r, 1, -1, matriex);
        }
    }
}

void OpenGLCommonFilter::onDestory() {
    if(ISDEBUG){
        ALOGD("opengl CommonFilter onDestory");
    }

    if(textureId>0){
        glDeleteTextures(1,&textureId);
    }
    if(program>0){
        glDetachShader(program,vertexShader);
        glDeleteShader(vertexShader);

        glDetachShader(program,fragmentShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        vertexShader=-1;
        fragmentShader=-1;
        program=-1;
    }





}

OpenGLCommonFilter::~OpenGLCommonFilter() {
    if(pixels!=NULL){
        pixels=NULL;
    }
}
