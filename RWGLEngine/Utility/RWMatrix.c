//
//  RWMatrix.c
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#include "RWMatrix.h"

//Generated Prototypes
void RWMatrix_init(const void *_self);
void RWMatrix_identity(const void *_self);
void RWMatrix_applyTranslation(const void *_self, float x, float y, float z);
void RWMatrix_applyScale(const void *_self, float x, float y, float z);
void RWMatrix_applyRotation(const void *_self, float pitch, float yaw, float roll);
void RWMatrix_applyRotationWithMag(const void *_self, float angle, float magX, float magY, float magZ);
void RWMatrix_setProjection(const void *_self, float fov, float aspect, float near, float far);
void RWMatrix_setOrtho(const void *_self, float left, float right, float top, float bottom, float near, float far);
void RWMatrix_selfMultiplyBy(const void *_self, RWMatrix *matrix);
void RWMatrix_toFloatArray(const void *_self, float *srcPtr);
void RWMatrix_updateFromFloatArray(const void *_self, float *array);
char *RWMatrix_toString(const void *_self);


void *RWMatrix_alloc() {
    RWMatrix *ptr = malloc(sizeof(RWMatrix));

	if (!ptr) {
		Log("Could not allocate space for object");
		exit(EXIT_FAILURE);
	}

    ptr->class = Class_alloc("RWMatrix");
    ptr->class->size = sizeof(ptr);
    ptr->init = &RWMatrix_init;
    ptr->identity = &RWMatrix_identity;
    ptr->applyTranslation = &RWMatrix_applyTranslation;
    ptr->applyScale = &RWMatrix_applyScale;
    ptr->applyRotation = &RWMatrix_applyRotation;
    ptr->applyRotationWithMag = &RWMatrix_applyRotationWithMag;
    ptr->setProjection = &RWMatrix_setProjection;
    ptr->setOrtho = &RWMatrix_setOrtho;
    ptr->selfMultiplyBy = &RWMatrix_selfMultiplyBy;
    ptr->toFloatArray = &RWMatrix_toFloatArray;
    ptr->updateFromFloatArray = &RWMatrix_updateFromFloatArray;
    ptr->toString = &RWMatrix_toString;

    return ptr;
}

void RWMatrix_dealloc(RWMatrix *ptr) {
    if (!ptr)
        return;

    Class_dealloc(ptr->class);
    free(ptr);
}


void RWMatrix_init(const void *_self) {
    RWMatrix *self = (RWMatrix *)_self;

    self->identity(_self);
}

void RWMatrix_identity(const void *_self) {
    RWMatrix *self = (RWMatrix *)_self;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == i)
                self->mat[i * 4 + j] = 1.0f;
            else
                self->mat[i * 4 + j] = 0.0f;
        }
    }
}

void RWMatrix_applyTranslation(const void *_self, float x, float y, float z) {
    RWMatrix *self = (RWMatrix *)_self;

    RWMatrix *temp = RWMatrix_alloc();
    temp->init(temp);

    temp->mat[12] = x;
    temp->mat[13] = y;
    temp->mat[14] = z;

    self->selfMultiplyBy(_self, temp);

    RWMatrix_dealloc(temp);

}

void RWMatrix_applyScale(const void *_self, float x, float y, float z) {
    RWMatrix *self = (RWMatrix *)_self;
    RWMatrix *temp = RWMatrix_alloc();
    temp->init(temp);

    temp->mat[0] = x;
    temp->mat[5] = y;
    temp->mat[10] = z;

    self->selfMultiplyBy(_self, temp);

    RWMatrix_dealloc(temp);
}

void RWMatrix_applyRotation(const void *_self, float pitch, float yaw, float roll) {
    RWMatrix *self = (RWMatrix *)_self;
    RWMatrix *temp = RWMatrix_alloc();
    temp->init(temp);

    if (pitch != 0) {
        float c = (float) cos(pitch);
        float s = (float) sin(pitch);

        temp->mat[5] = c;
        temp->mat[6] = -s;
        temp->mat[9] = s;
        temp->mat[10] = c;

        self->selfMultiplyBy(_self, temp);
    }

    temp->identity(_self);

    if (yaw != 0) {
        float c = (float) cos(yaw);
        float s = (float) sin(yaw);

        temp->mat[0] = c;
        temp->mat[2] = s;
        temp->mat[8] = -s;
        temp->mat[10] = c;

        self->selfMultiplyBy(_self, temp);
    }

    temp->identity(_self);

    if (roll != 0) {
        float c = (float) cos(roll);
        float s = (float) sin(roll);

        temp->mat[0] = c;
        temp->mat[1] = -s;
        temp->mat[4] = s;
        temp->mat[5] = c;

        self->selfMultiplyBy(_self, temp);
    }

    temp->identity(_self);

    RWMatrix_dealloc(temp);
}

void RWMatrix_applyRotationWithMag(const void *_self, float angle, float magX, float magY, float magZ) {
    RWMatrix *self = (RWMatrix *)_self;
    RWMatrix *temp = RWMatrix_alloc();
    temp->init(temp);

    float sinAngle, cosAngle;
    float magnitude;

    magnitude = (float) sqrt((magX * magX) + (magY * magY) + (magZ * magZ));

    sinAngle = (float) sin(angle * PI / 180.0f);
    cosAngle = (float) cos(angle * PI / 180.0f);

    if (magnitude > 0) {
        float xx, yy, zz, xy, xz, yz, xs, ys, zs;
        float oneMinusCos;

        magX /= magnitude;
        magY /= magnitude;
        magZ /= magnitude;

        xx = magX * magX;
        yy = magY * magY;
        zz = magZ * magZ;
        xy = magX * magY;
        xz = magX * magZ;
        yz = magY * magZ;
        xs = magX * sinAngle;
        ys = magY * sinAngle;
        zs = magZ * sinAngle;

        oneMinusCos = 1 - cosAngle;

        temp->mat[0] = (oneMinusCos * xx) + cosAngle;
        temp->mat[1] = (oneMinusCos * xy) - zs;
        temp->mat[2] = (oneMinusCos * xz) + ys;
        temp->mat[3] = 0;

        temp->mat[4] = (oneMinusCos * xy) + zs;
        temp->mat[5] = (oneMinusCos * yy) + cosAngle;
        temp->mat[6] = (oneMinusCos * yz) - xs;
        temp->mat[7] = 0;

        temp->mat[8] = (oneMinusCos * xz) - ys;
        temp->mat[9] = (oneMinusCos * yz) + xs;
        temp->mat[10] = (oneMinusCos * zz) + cosAngle;
        temp->mat[11] = 0;

        temp->mat[12] = 0;
        temp->mat[13] = 0;
        temp->mat[14] = 0;
        temp->mat[15] = 1;

        self->selfMultiplyBy(_self, temp);
    }

    RWMatrix_dealloc(temp);
}

void RWMatrix_setProjection(const void *_self, float fov, float aspect, float near, float far) {
    RWMatrix *self = (RWMatrix *)_self;
    RWMatrix *temp = RWMatrix_alloc();
    temp->init(_self);

    float r = fov * PI / 180.0f;
    float f = 1.0f / (float) tan(r / 2.0f);

    temp->mat[0] = f/aspect;
    temp->mat[5] = f;
    temp->mat[10] = (far + near) / (near - far);
    temp->mat[11] = -1;
    temp->mat[14] = (2 * far * near) / (near - far);
    temp->mat[15] = 0;

    self->selfMultiplyBy(_self, temp);

    RWMatrix_dealloc(temp);
}

void RWMatrix_setOrtho(const void *_self, float left, float right, float top, float bottom, float near, float far) {
    RWMatrix *self = (RWMatrix *)_self;
    RWMatrix *temp = RWMatrix_alloc();
    temp->init(temp);

    temp->mat[0] = 2/(right - left);
    temp->mat[5] = 2/(top - bottom);
    temp->mat[10] = -2/(far - near);
    temp->mat[12] = -(right + left) / (right - left);
    temp->mat[13] = -(top + bottom) / (top - bottom);
    temp->mat[14] = -(far + near)/(far - near);


// |   2 / (r - l)   ,        0        ,        0        , 0 | [0 - 3]
// |        0        ,    2/(t - b)    ,        0        , 0 | [4 - 7]
// |        0        ,        0        ,    -2/(f - n)   , 0 | [8 - 11]
// | -(r + l)/(r - l), -(t + b)/(t - b), -(f + n)/(f - n), 1 | [12 - 15]

    self->selfMultiplyBy(_self, temp);

    RWMatrix_dealloc(temp);
}

void RWMatrix_selfMultiplyBy(const void *_self, RWMatrix *matrix) {
    RWMatrix *self = (RWMatrix *)_self;
    float firstMat[16];
    float secondMat[16];
    float tempMatrix[16];

    self->toFloatArray(self, firstMat);
    matrix->toFloatArray(matrix, secondMat);

    //Column 1
    tempMatrix[0] = (secondMat[0] * firstMat[0]) +
    (secondMat[4] * firstMat[1]) +
    (secondMat[8] * firstMat[2]) +
    (secondMat[12] * firstMat[3]);

    tempMatrix[1] = (secondMat[1] * firstMat[0]) +
    (secondMat[5] * firstMat[1]) +
    (secondMat[9] * firstMat[2]) +
    (secondMat[13] * firstMat[3]);

    tempMatrix[2] = (secondMat[2] * firstMat[0]) +
    (secondMat[6] * firstMat[1]) +
    (secondMat[10] * firstMat[2]) +
    (secondMat[14] * firstMat[3]);

    tempMatrix[3] = (secondMat[3] * firstMat[0]) +
    (secondMat[7] * firstMat[1]) +
    (secondMat[11] * firstMat[2]) +
    (secondMat[15] * firstMat[3]);

    //Column 2
    tempMatrix[4] = (secondMat[0] * firstMat[4]) +
    (secondMat[4] * firstMat[5]) +
    (secondMat[8] * firstMat[6]) +
    (secondMat[12] * firstMat[7]);

    tempMatrix[5] = (secondMat[1] * firstMat[4]) +
    (secondMat[5] * firstMat[5]) +
    (secondMat[9] * firstMat[6]) +
    (secondMat[13] * firstMat[7]);

    tempMatrix[6] = (secondMat[2] * firstMat[4]) +
    (secondMat[6] * firstMat[5]) +
    (secondMat[10] * firstMat[6]) +
    (secondMat[14] * firstMat[7]);

    tempMatrix[7] = (secondMat[3] * firstMat[4]) +
    (secondMat[7] * firstMat[5]) +
    (secondMat[11] * firstMat[6]) +
    (secondMat[15] * firstMat[7]);

    //Column 3
    tempMatrix[8] = (secondMat[0] * firstMat[8]) +
    (secondMat[4] * firstMat[9]) +
    (secondMat[8] * firstMat[10]) +
    (secondMat[12] * firstMat[11]);

    tempMatrix[9] = (secondMat[1] * firstMat[8]) +
    (secondMat[5] * firstMat[9]) +
    (secondMat[9] * firstMat[10]) +
    (secondMat[13] * firstMat[11]);

    tempMatrix[10] = (secondMat[2] * firstMat[8]) +
    (secondMat[6] * firstMat[9]) +
    (secondMat[10] * firstMat[10]) +
    (secondMat[14] * firstMat[11]);

    tempMatrix[11] = (secondMat[3] * firstMat[8]) +
    (secondMat[7] * firstMat[9]) +
    (secondMat[11] * firstMat[10]) +
    (secondMat[15] * firstMat[11]);

    //Column 4
    tempMatrix[12] = (secondMat[0] * firstMat[12]) +
    (secondMat[4] * firstMat[13]) +
    (secondMat[8] * firstMat[14]) +
    (secondMat[12] * firstMat[15]);

    tempMatrix[13] = (secondMat[1] * firstMat[12]) +
    (secondMat[5] * firstMat[13]) +
    (secondMat[9] * firstMat[14]) +
    (secondMat[13] * firstMat[15]);

    tempMatrix[14] = (secondMat[2] * firstMat[12]) +
    (secondMat[6] * firstMat[13]) +
    (secondMat[10] * firstMat[14]) +
    (secondMat[14] * firstMat[15]);

    tempMatrix[15] = (secondMat[3] * firstMat[12]) +
    (secondMat[7] * firstMat[13]) +
    (secondMat[11] * firstMat[14]) +
    (secondMat[15] * firstMat[15]);

    self->updateFromFloatArray(_self, tempMatrix);
}

void RWMatrix_toFloatArray(const void *_self, float *srcPtr) {
    RWMatrix *self = (RWMatrix *)_self;

    for (int i = 0; i < 16; i++) {
        srcPtr[i] = self->mat[i];
    }
}

void RWMatrix_updateFromFloatArray(const void *_self, float *array) {
    RWMatrix *self = (RWMatrix *)_self;

    for (int i = 0; i < 16; i++) {
        self->mat[i] = array[i];
    }
}

char *RWMatrix_toString(const void *_self) {
    RWMatrix *self = (RWMatrix *)_self;
	char *retVal = malloc(sizeof(char) * 2048);
	char *buffer = NULL;

	sprintf(buffer, "%.4f %.4f %.4f %.4f\n"
                    "%.4f %.4f %.4f %.4f\n"
                    "%.4f %.4f %.4f %.4f\n"
                    "%.4f %.4f %.4f %.4f\n",
                    self->mat[0], self->mat[1], self->mat[2], self->mat[3],
                    self->mat[4], self->mat[5], self->mat[6], self->mat[7],
                    self->mat[8], self->mat[9], self->mat[10], self->mat[11],
                    self->mat[12], self->mat[13], self->mat[14], self->mat[15]);

	strcpy(retVal, buffer);

    return retVal;
}
