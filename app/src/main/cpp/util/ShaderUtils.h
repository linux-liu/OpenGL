//
// Created by liuxin on 19-11-18.
//

#ifndef OPENGL_SHADERUTILS_H
#define OPENGL_SHADERUTILS_H

#include "GLES2/gl2.h"


static GLuint  loadShaders(int shaderType, const char *code) {
    GLuint  shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);
    return  shader;


}

static GLuint  createProgram(const char *vertex, const char *fragment,GLuint *vShader,GLuint *fShader) {
    GLuint  vertexShader = loadShaders(GL_VERTEX_SHADER, vertex);
    GLuint  fragmentShader = loadShaders(GL_FRAGMENT_SHADER, fragment);
    *vShader=vertexShader;
    *fShader=fragmentShader;
    GLuint  program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;


}

#endif //OPENGL_SHADERUTILS_H
