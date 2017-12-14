//
//  RWLogger.c
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-06-11.
//  Copyright © 2017 RWG. All rights reserved.
//

#include "RWLogger.h"

//Generated Prototypes


void Log(char *message, ...) {
    RWTime *time = RWTime_alloc();
	char *temp;

    time->init(time);

    temp = time->getStringFromTime(time);

    printf("%s ", temp);

	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);

	printf("\n");

	free(temp);
}
