//
//  Class.c
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#include "Class.h"

void *Class_alloc(char *name) {
    Class *ptr = malloc(sizeof(Class));

	if (!ptr) {
		Log("Could not allocate space for object");
		exit(EXIT_FAILURE);
	}

    ptr->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(ptr->name, name);
    ptr->size = 0;

    return ptr;
}

void Class_dealloc(Class *ptr) {
    if (!ptr)
        return;

    free(ptr->name);
    free(ptr);
}
