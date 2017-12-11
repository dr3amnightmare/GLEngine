//
//  main.m
//  RWGLEngine
//
//  Created by Tyler McLean on 2017-05-10.
//  Copyright © 2017 RWG. All rights reserved.
//

#include "RWGLEngine.h"

int main() {
	// This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.

    RWGame *game = RWGame_alloc();
	game->initWithTitle(game, "Test");
    //RWGame *testInstance = (RWGame*)RWGame_getInstance();
	int invR = 0, invB = 0, invG = 0;
    float r = 0, g = 0, b = 0;

    Log("%s", glGetString(GL_VERSION));

    while (glfwWindowShouldClose(game->window) == GLFW_FALSE) {
        glClearColor(r, g, b, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        if (glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(game->window, GLFW_TRUE);

		if (!invR)
        	r += 0.001;
		else
			r -= 0.001;
		if (!invG)
        	g += 0.002;
		else
			g -= 0.002;
		if (!invB)
        	b += 0.004;
		else
			b -= 0.004;

        if (r >= 1)
            invR = 1;
        if (g >= 1)
            invG = 1;
        if (b >= 1)
            invB = 1;

		if (r <= 0)
            invR = 0;
        if (g <= 0)
            invG = 0;
        if (b <= 0)
            invB = 0;

        game->swapBuffers(game);
    }
    //sleep(3);
    game->terminate(game);

    return 1;
}
