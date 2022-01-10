#include <iostream>

#include "game/application.h"
#include "world/chunk.h"
#include "util/image_display.h"

int main() {
    if (!Application::launch()) {
        std::cout << "LAUNCH FAILED" << std::endl;
    }

    //Application::loop();

    std::unique_ptr<INoise> noise = std::make_unique<PerlinNoise>(1);
    Testing::noiseTexLoop(noise.get(), 10);
    glfwTerminate();

    std::cout << "GAME PROCESS END" << std::endl;

    return 0;
}