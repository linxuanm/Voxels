#include <iostream>

#include "game/application.h"
#include "world/chunk.h"
#include "util/image_display.h"

static void loopNoise() {
    auto func = [](float w, float h){
        return w * h;
    };
    TexPtr tex = Testing::genNoiseTex(func, 100, 100);
    Testing::drawQuadLoop(700);
}

int main() {
    if (!Application::launch()) {
        std::cout << "LAUNCH FAILED" << std::endl;
    }

    Application::loop();

    glfwTerminate();

    std::cout << "GAME PROCESS END" << std::endl;

    return 0;
}