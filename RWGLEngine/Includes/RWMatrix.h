//
//  RWMatrix.h
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#ifndef RWMATRIX_H
#define RWMATRIX_H

#define PI 3.1415926535897932384626433832795f

#include <stdlib.h>
#include <math.h>
#include "Class.h"
#include "RWLogger.h"

typedef struct RWMatrix RWMatrix;

struct RWMatrix {
    Class *class;
    float mat[16];

    void (* init) (const void *_self);
    void (* identity) (const void *_self);
    void (* applyTranslation) (const void *_self, float x, float y, float z);
    void (* applyScale) (const void *_self, float x, float y, float z);
    void (* applyRotation) (const void *_self, float pitch, float yaw, float roll);
    void (* applyRotationWithMag) (const void *_self, float angle, float magX, float magY, float magZ);
    void (* setProjection) (const void *_self, float fov, float aspect, float near, float far);
    void (* setOrtho) (const void *_self, float left, float right, float top, float bottom, float near, float far);
    void (* selfMultiplyBy) (const void *_self, RWMatrix *matrix);
    void (* toFloatArray) (const void *_self, float *srcPtr);
    void (* updateFromFloatArray) (const void *_self, float *array);
    char *(* toString) (const void *_self);
};


void *RWMatrix_alloc();
void RWMatrix_dealloc(RWMatrix *ptr);

#endif //RWMATRIX_H
