#include "RWGame.h"

static void *instance = NULL;

//Generated Prototypes
void RWGame_initWithTitle(const void *_self, char *title);
void RWGame_swapBuffers(const void *_self);
void RWGame_terminate(const void *_self);
void errorCallback(int error, const char *description);

//Generated Public Functions
void *RWGame_getInstance(void) {
    if (instance)
        return instance;

    return NULL;
}

void *RWGame_alloc() {
	RWGame *ptr = malloc(sizeof(RWGame));

	if (!ptr) {
		Log("Could not allocate space for object");
		exit(EXIT_FAILURE);
	}

    ptr->class = Class_alloc("RWGame");
    ptr->class->size = sizeof(ptr);
	ptr->window = NULL;
	ptr->width = 0;
	ptr->height = 0;
    ptr->initWithTitle = &RWGame_initWithTitle;
    ptr->swapBuffers = &RWGame_swapBuffers;
	ptr->terminate = &RWGame_terminate;

    return ptr;
}

void RWGame_dealloc(RWGame *ptr) {
	if (!ptr)
		return;

	Class_dealloc(ptr->class);
	if (ptr->window)
		glfwDestroyWindow(ptr->window);

	free(ptr);
}

//Generated Private Functions
void RWGame_initWithTitle(const void *_self, char *title) {
    RWGame *self = (RWGame *)_self;

	if (!glfwInit())
    {
        Log("Could not initialize GLFW3");
        return;
    }

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    self->width = mode->width;
    self->height = mode->height;

    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    self->window = glfwCreateWindow(self->width, self->height, title, glfwGetPrimaryMonitor(), NULL);

    if (!self->window) {
        Log("Could not create window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(self->window);
    glfwSwapInterval(1);

    instance = (RWGame *)_self;

}

void RWGame_swapBuffers(const void *_self) {
    RWGame *self = (RWGame *)_self;

    glfwSwapBuffers(self->window);
}

void RWGame_terminate(const void *_self) {
    RWGame *self = (RWGame *)_self;

    glfwDestroyWindow(self->window);
    glfwTerminate();
}

//Protected Functions
void errorCallback(int error, const char *description) {
    Log("Error #%d: %s", error, description);
}
