#ifndef CLASS_H
#define CLASS_H

#define REQUIRE_NULL_TERMINATION __attribute__((sentinel))

#include <stdlib.h>
#include <string.h>
#include "RWLogger.h"

typedef struct Class Class;

struct Class {
    char *name;
    size_t size;
};

void *Class_alloc(char *name);
void Class_dealloc(Class *ptr);

#endif //CLASS_H
