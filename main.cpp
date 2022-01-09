#include <iostream>

#include "game/application.h"
#include "world/chunk.h"
#include "util/image_display.h"

int main() {
    if (!Application::launch()) {
        std::cout << "LAUNCH FAILED" << std::endl;
    }

    Application::loop();
    //Testing::drawQuadLoop(700);
    glfwTerminate();

    std::cout << "GAME PROCESS END" << std::endl;

    return 0;
}