//
//  RWMutableArray.h
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#ifndef RWMUTABLEARRAY_H
#define RWMUTABLEARRAY_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "Class.h"
#include "RWLogger.h"
#include "RWObjectNode.h"

typedef struct RWMutableArray RWMutableArray;

struct RWMutableArray {
    Class *class;
    long count;
    RWObjectNode *first;
    RWObjectNode *last;

    void (* init) (const void *_self);
    void (* initWithObjects) (const void *_self, ...);
    void (* addObject) (const void *_self, void *object);
    void (* insertObject) (const void *_self, void *object, unsigned int index);
    void (* removeAllObjects) (const void *_self);
    void (* removeObject) (const void *_self, void *object);
    void (* removeObjectAtIndex) (const void *_self, unsigned int index);
    void (* replaceObjectAtIndex) (const void *_self, unsigned int index, void *object);
    void * (* getFirstObject) (const void *_self);
    void * (* getLastObject) (const void *_self);
    void * (* getObjectAtIndex) (const void *_self, unsigned int index);
    long (* getCount) (const void *_self);
};


void *RWMutableArray_alloc();
void RWMutableArray_dealloc(RWMutableArray *ptr);

#endif //RWMUTABLEARRAY_H
