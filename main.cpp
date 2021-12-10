#include <iostream>

#include "game/application.h"

int main() {
    Application &app = Application::get();

    if (!app.launch()) {
        std::cout << "LAUNCH FAILED" << std::endl;
    }

    app.loop();
    glfwTerminate();

    std::cout << "GAME PROCESS END" << std::endl;

    return 0;
}