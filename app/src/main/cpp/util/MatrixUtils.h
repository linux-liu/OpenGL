//
// Created by liuxin on 19-11-20.
//

#ifndef OPENGL_MATRIXUTILS_H
#define OPENGL_MATRIXUTILS_H


#include "math.h"
static void  init(float * matrixs){
    for(int i=0;i<16;i++){
        if(i%5==0){
            matrixs[i]=1;
        } else{
            matrixs[i]=0;
        }
    }
}

static void rotate(double angle,float *matrixs){
    double  f_angle=angle*(M_PI/180);
    matrixs[0]=cos(f_angle);
    matrixs[1]=-sin(f_angle);

    matrixs[4]=sin(f_angle);
    matrixs[5]=cos(f_angle);
}

static void  scale(double scale, float * matrixs){
    matrixs[0]=scale;//缩放x轴
    matrixs[5]=scale;//缩放y轴


}
static void  translate(double transX, double transY, float *matrixs){
    matrixs[3]=transX;
    matrixs[7]=transY;
}

static void projection(double left, double right, double top, double bottom, float *matrixs){
    matrixs[0]=2.0/(right-left);
    matrixs[3]=-(right+left)/(right-left);
    matrixs[5]=2.0/(top-bottom);
    matrixs[7]=-(top+bottom)/(top-bottom);

}


#endif //OPENGL_MATRIXUTILS_H
