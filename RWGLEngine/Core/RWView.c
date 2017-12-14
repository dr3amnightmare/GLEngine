//
//  RWView.c
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#include "RWView.h"

void RWView_initWithDimensions(const void *_self, int width, int height);
void RWView_setViewport(const void *_self, int width, int height);

void *RWView_alloc() {
    RWTime *ptr = malloc(sizeof(RWTime));

    ptr->class = Class_alloc("RWView");
    ptr->class->size = sizeof(ptr);
    ptr->perspective = RWMatrix_alloc();
    ptr->perspective->init(ptr->perspective);
    ptr->width = 0;
    ptr->height = 0;
    ptr->initWithDimensions = &RWView_initWithDimensions;
    ptr->setViewport = &RWView_setViewport;

    return ptr;
}

void RWView_dealloc(RWView *ptr) {
    if (!ptr)
        return;

    Class_dealloc(ptr->class);
    RWMatrix_dealloc(ptr->perspective);

    free(ptr);
}

void setViewport(RWView *self) {
    glViewport(0, 0, self->width, self->height);
    self->perspective->setProjection(self->perspective, 90, (float)(self->width / self->height), 0, 1);
}

void RWView_initWithDimensions(const void *_self, int width, int height) {
    RWView *self = (RWView *)_self;
    self->width = width;
    self->height = height;
    setViewport(self);
}

void RWView_setViewport(const void *_self, int width, int height) {
    RWView *self = (RWView *)_self;
    self->width = width;
    self->height = height;
    setViewport(self);
}
