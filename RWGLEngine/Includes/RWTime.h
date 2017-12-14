//
//  RWTime.h
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#ifndef RWTIME_H
#define RWTIME_H

#include <stdlib.h>
#include <time.h>
#include "Class.h"

typedef struct RWTime RWTime;

struct RWTime {
    struct Class *class;
    struct tm *currTime;

    void (* init) (const void *_self);
    void (* setToTime) (const void *_self, int year, int month, int day, int hour, int min, int sec);
    void (* setToCurrentTime) (const void *_self);
    char * (* getStringFromTime) (const void *_self);
    char * (* getStringFromCurrentTime) (const void *_self);
};

void *RWTime_alloc();
void RWTime_dealloc(RWTime *ptr);

#endif //RWTIME_H
