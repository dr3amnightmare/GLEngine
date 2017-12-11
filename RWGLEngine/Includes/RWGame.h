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
//Generated Private Functions
    void (* initWithTitle) (const void *_self, char *title);
    void (* swapBuffers) (const void *_self);
    void (* terminate) (const void *_self);
};

//Generated Public Functions
void *RWGame_alloc();
void RWGame_dealloc(RWGame *ptr);
void *RWGame_getInstance(void);

#endif //RWGAME_H
