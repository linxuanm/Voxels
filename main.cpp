#include <iostream>

#include "game/application.h"

int main() {

    if (!Application::launch()) {
        std::cout << "LAUNCH FAILED" << std::endl;
    }

    Application::loop();
    glfwTerminate();

    std::cout << "GAME PROCESS END" << std::endl;

    return 0;
}