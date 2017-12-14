//
//  RWMutableArray.c
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#include "RWMutableArray.h"

//Generated Prototypes
void RWMutableArray_init(const void *_self);
void RWMutableArray_initWithObjects(const void *_self, ...);
void RWMutableArray_addObject(const void *_self, void *object);
void RWMutableArray_insertObject(const void *_self, void *object, unsigned int index);
void RWMutableArray_removeAllObjects(const void *_self);
void RWMutableArray_removeObject(const void *_self, void *object);
void RWMutableArray_removeObjectAtIndex(const void *_self, unsigned int index);
void RWMutableArray_replaceObjectAtIndex(const void *_self, unsigned int index, void *object);
void *RWMutableArray_getFirstObject(const void *_self);
void *RWMutableArray_getLastObject(const void *_self);
void *RWMutableArray_getObjectAtIndex(const void *_self, unsigned int index);
long RWMutableArray_getCount(const void *_self);


void *RWMutableArray_alloc() {
    RWMutableArray *ptr = malloc(sizeof(RWMutableArray));

    ptr->class = Class_alloc("RWMutableArray");
    ptr->class->size = sizeof(ptr);
    ptr->init = &RWMutableArray_init;
    ptr->initWithObjects = &RWMutableArray_initWithObjects;
    ptr->addObject = &RWMutableArray_addObject;
    ptr->insertObject = &RWMutableArray_insertObject;
    ptr->removeAllObjects = &RWMutableArray_removeAllObjects;
    ptr->removeObject = &RWMutableArray_removeObject;
    ptr->removeObjectAtIndex = &RWMutableArray_removeObjectAtIndex;
    ptr->replaceObjectAtIndex = &RWMutableArray_replaceObjectAtIndex;
    ptr->getFirstObject = &RWMutableArray_getFirstObject;
    ptr->getLastObject = &RWMutableArray_getLastObject;
    ptr->getObjectAtIndex = &RWMutableArray_getObjectAtIndex;
    ptr->getCount = &RWMutableArray_getCount;

    ptr->first = NULL;
    ptr->last = NULL;

    return ptr;
}

void RWMutableArray_dealloc(RWMutableArray *ptr) {
    if (!ptr)
        return;

    RWMutableArray_removeAllObjects(ptr);

    Class_dealloc(ptr->class);

    free(ptr);
}


void RWMutableArray_init(const void *_self) {
    RWMutableArray *self = (RWMutableArray *)_self;

    self->first = NULL;
    self->last = NULL;
}

REQUIRE_NULL_TERMINATION void RWMutableArray_initWithObjects(const void *_self, ...){
    RWMutableArray *self = (RWMutableArray *)_self;
    va_list args;
    self->first = NULL;
    self->last = NULL;

    va_start(args, _self);

    for (void * obj = va_arg(args, void *); obj != NULL; obj = va_arg(args, void *)) {
        self->addObject(_self, obj);
    }

    va_end(args);
}

void RWMutableArray_addObject(const void *_self, void *object) {
    RWMutableArray *self = (RWMutableArray *)_self;
    //RWObjectType *obj = [[RWObjectType alloc] init];
    RWObjectNode *node = malloc(sizeof(RWObjectNode));
    node->next = NULL;
    node->previous = NULL;
    node->object = NULL;

    if (!object) {
        //@throw [NSException exceptionWithName:@"NilObjectException" reason:@"Object is nil" userInfo:nil];
        Log("NullObjectException: Object is null\n");
        return;
    }

    node->object = object;

    if (self->count == 0) {
        self->first = node;
        self->last = node;
    }
    else {
        self->last->next = node;
        node->previous = self->last;
        node->next = NULL;
        self->last = node;
    }

    self->count++;
}

void RWMutableArray_insertObject(const void *_self, void *object, unsigned int index) {
    RWMutableArray *self = (RWMutableArray *)_self;
    RWObjectNode *head = self->first;
    RWObjectNode *node = malloc(sizeof(RWObjectNode));
    node->next = NULL;
    node->previous = NULL;
    node->object = NULL;

    if (index > self->count) {
        //@throw [NSException exceptionWithName:@"IndexOutOfBoundsException" reason:@"Index is out of bounds" userInfo:nil];
        Log("IndexOutOfBoundsException: Index is out of bounds\n");
        return;
    }

    if (!object) {
        Log("NullObjectException: Object is null\n");
        return;
    }

    node->object = object;

    /*Insert at beginning*/
    if (index == 0) {
        if (self->count == 0) {
            RWMutableArray_addObject(_self, object);
            free(node);
        }
        else {
            node->next = self->first;
            node->previous = NULL;
            self->first->previous = node;
            self->first = node;
        }
    }
    /* Insert at end */
    else if (index == self->count) {
        RWMutableArray_addObject(_self, object);
        free(node);
    }
    /* Insert at other index */
    else {
        for (int i = 0; i < index; i++)
            head = head->next;

        node->next = head;
        node->previous = head->previous;
        head->previous->next = node;
        head->previous = node;
    }

    self->count++;
}

void RWMutableArray_removeAllObjects(const void *_self) {
    RWMutableArray *self = (RWMutableArray *)_self;
    while (self->first != self->last) {
        self->first = self->first->next;
        free(self->first->previous);
    }

    free(self->first);

    self->first = NULL;
    self->last = NULL;

    self->count = 0;
}

void RWMutableArray_removeObject(const void *_self, void *object) {
    RWMutableArray *self = (RWMutableArray *)_self;
    RWObjectNode *prev = NULL;

    if (!object) {
        Log("NullObjectException: Object is null\n");
        return;
    }
        //@throw [NSException exceptionWithName:@"NilObjectException" reason:@"Object is nil" userInfo:nil];

    for (RWObjectNode *obj = self->first; obj != NULL; obj = obj->next)
    {
        if (prev != NULL) {
            free(prev);
        }
        if (obj->object == object)
        {
            obj->previous->next = obj->next;
            obj->next->previous = obj->previous;
            prev = obj;
            self->count--;
        }
    }

    if (prev != NULL) {
        free(prev);
    }
}

void RWMutableArray_removeObjectAtIndex(const void *_self, unsigned int index) {
    RWMutableArray *self = (RWMutableArray *)_self;
    RWObjectNode *head = self->first;

    if (index > self->count) {
        //@throw [NSException exceptionWithName:@"IndexOutOfBoundsException" reason:@"Index is out of bounds" userInfo:nil];
        Log("IndexOutOfBoundsException: Index is out of bounds\n");
        return;
    }

    for (int i = 0; i < index; i++) {
        head = head->next;
    }

    if (index != 0)
        head->previous->next = head->next;
    if (index != self->count - 1)
        head->next->previous = head->previous;
    free(head);

    self->count--;
}

void RWMutableArray_replaceObjectAtIndex(const void *_self, unsigned int index, void *object) {
    RWMutableArray *self = (RWMutableArray *)_self;

    if (index > self->count) {
        //@throw [NSException exceptionWithName:@"IndexOutOfBoundsException" reason:@"Index is out of bounds" userInfo:nil];
        Log("IndexOutOfBoundsException: Index is out of bounds\n");
        return;
    }

    if (!object) {
        Log("NullObjectException: Object is null\n");
        return;
    }

    RWMutableArray_removeObjectAtIndex(_self, index);
    RWMutableArray_insertObject(_self, object, index);
}

void *RWMutableArray_getFirstObject(const void *_self) {
    RWMutableArray *self = (RWMutableArray *)_self;
    return self->first->object;
}

void *RWMutableArray_getLastObject(const void *_self) {
    RWMutableArray *self = (RWMutableArray *)_self;
    return self->last->object;
}

void *RWMutableArray_getObjectAtIndex(const void *_self, unsigned int index) {
    RWMutableArray *self = (RWMutableArray *)_self;
    RWObjectNode *head;

    if (index > self->count) {
        //@throw [NSException exceptionWithName:@"IndexOutOfBoundsException" reason:@"Index is out of bounds" userInfo:nil];
        Log("IndexOutOfBoundsException: Index is out of bounds\n");
        return NULL;
    }

    head = self->first;

    for (int i = 0; i < index; i++) {
        head = head->next;
    }

    return head->object;
}

long RWMutableArray_getCount(const void *_self) {
    RWMutableArray *self = (RWMutableArray *)_self;
    return self->count;
}
