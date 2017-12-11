#include "RWTime.h"

//Generated Prototypes
void RWTime_init(const void *_self);
void RWTime_setToTime(const void *_self, int year, int month, int day, int hour, int min, int sec);
void RWTime_setToCurrentTime(const void *_self);
char *RWTime_getStringFromTime(const void *_self);
char *RWTime_getStringFromCurrentTime(const void *_self);

//Generated Public Functions
void *RWTime_alloc() {
    RWTime *ptr = malloc(sizeof(RWTime));

    ptr->currTime = NULL;
    ptr->init = &RWTime_init;
    ptr->setToTime = &RWTime_setToTime;
    ptr->setToCurrentTime = &RWTime_setToCurrentTime;
    ptr->getStringFromTime = &RWTime_getStringFromTime;
    ptr->getStringFromCurrentTime = &RWTime_getStringFromCurrentTime;

    return ptr;
}

void RWTime_dealloc(RWTime *ptr) {
    if (!ptr)
        return;

    Class_dealloc(ptr->class);

    if (ptr->currTime)
        free(ptr->currTime);

    free(ptr);
}


//Generated Private Functions
void RWTime_init(const void *_self) {
    RWTime *self = (RWTime *)_self;

    time_t epoch;
    self->currTime = malloc(sizeof(struct tm));

    time(&epoch);
    self->currTime = localtime(&epoch);
}

void RWTime_setToTime(const void *_self, int year, int month, int day, int hour, int min, int sec) {
    RWTime *self = (RWTime *)_self;

    if (!self->currTime) {
        Log("Object not initialized");
        return;
    }

    self->currTime->tm_year = year - 1900;
    self->currTime->tm_mon = month;
    self->currTime->tm_mday = day;
    self->currTime->tm_hour = hour;
    self->currTime->tm_min = min;
    self->currTime->tm_sec = sec;
}

void RWTime_setToCurrentTime(const void *_self) {
    time_t epoch;

    RWTime *self = (RWTime *)_self;

    if (!self->currTime) {
        Log("Object not initialized");
        return;
    }

    time(&epoch);
    self->currTime = localtime(&epoch);
}

char *RWTime_getStringFromTime(const void *_self) {
    char *temp;
    RWTime *self = (RWTime *)_self;

    if (!self->currTime) {
        printf("Object not initialized");
        return NULL;
    }

	temp = malloc(sizeof(char) * 128);

    snprintf(temp, 128, "[%d-%02d-%02d %02d:%02d:%02d]",
            self->currTime->tm_year + 1900, self->currTime->tm_mon, self->currTime->tm_mday,
            self->currTime->tm_hour, self->currTime->tm_min, self->currTime->tm_sec);

    return temp;
}

char *RWTime_getStringFromCurrentTime(const void *_self) {
    RWTime *self = (RWTime *)_self;

    if (!self->currTime) {
        Log("Object not initialized");
        return NULL;
    }

    self->setToCurrentTime(_self);
    return self->getStringFromTime(_self);
}
