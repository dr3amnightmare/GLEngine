//
//  RWView.h
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#ifndef RWVIEW_H
#define RWVIEW_H

#include "Class.h"
#include "RWMatrix.h"

typedef struct RWView RWView;

struct RWView {
    Class *class;
    RWMatrix *perspective;
    int width;
    int height;
    void (*initWithDimensions)(const void *_self, int width, int height);
    void (*setViewport)(const void *_self, int width, int height);
};

void *RWView_alloc();
void RWView_dealloc(RWView *ptr);

#endif //_RWVIEW_H
