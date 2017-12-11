#include "RWLogger.h"

//Generated Prototypes

//Generated Public Functions
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


//Generated Private Functions
