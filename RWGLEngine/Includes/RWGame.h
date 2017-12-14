//
//  RWGame.h
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#ifndef RWGAME_H
#define RWGAME_H

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Class.h"
#include "RWLogger.h"

typedef struct RWGame RWGame;

struct RWGame {
    Class *class;
    GLFWwindow *window;
    int width;
    int height;

    void (* initWithTitle) (const void *_self, char *title);
    void (* swapBuffers) (const void *_self);
    void (* terminate) (const void *_self);
};


void *RWGame_alloc();
void RWGame_dealloc(RWGame *ptr);
void *RWGame_getInstance(void);

#endif //RWGAME_H
