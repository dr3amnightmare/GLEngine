CC=clang
AR=ar rc
INCLUDES=-I./Includes -I./
BUILD_DIR=./Build
CFLAGS= -Wall -pedantic -std=c99 -c -g
LDFLAGS= -lglfw3

CORE_DIR = ./Core
UTILITY_DIR = ./Utility

SRC=  Core/RWGame.c\
      Utility/RWLogger.c\
	  Utility/RWMatrix.c\
	  Utility/RWMutableArray.c\
	  Utility/RWTime.c\
	  Utility/Class.c

OBJS := $(SRC:.c=.o)

libRWGLEngine.a: $(OBJS)
	$(AR) ./Build/$@ ./Build/Core/*.o ./Build/Utility/*.o

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $(BUILD_DIR)/$@
