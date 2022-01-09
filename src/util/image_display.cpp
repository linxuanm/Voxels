#include "image_display.h"

#define STB_IMAGE_IMPLEMENTATION

#include "game/application.h"
#include "util/log.h"

void Testing::drawTextureLoop() {
    glfwSwapBuffers(Application::window); // Mac OS

    auto deltaTime = (float) glfwGetTime();
    float lastFrame = deltaTime;

    while (!glfwWindowShouldClose(Application::window)) {
        auto currTime = (float) glfwGetTime();
        deltaTime = currTime - lastFrame;
        lastFrame = currTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwSwapBuffers(Application::window);
        glfwPollEvents();

        Log::logGLError();
    }
}
