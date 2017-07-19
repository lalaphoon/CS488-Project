#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <glm/glm.hpp>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
/* Function prototypes */
glm::vec3 vCalcRotVec(float fNewX, float fNewY,
                 float fOldX, float fOldY,
                 float fDiameter);
glm::mat4 vAxisRotMatrix(float fVecX, float fVecY, float fVecZ);

GLuint LoadTexture(const char * filename, int width, int height);
void FreeTexture( GLuint texture );
void square(GLuint texture);

#endif
