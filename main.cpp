#include <iostream>

#include "game/application.h"
#include "world/chunk.h"
#include "util/image_display.h"

static void loopNoise(INoise *noise) {
    auto func = [noise](float w, float h){
        return noise->genNoise(w, h);
    };
    TexPtr tex = Testing::genNoiseTex(func, 250, 250);
    Testing::drawQuadLoop(700);
}

int main() {
    if (!Application::launch()) {
        std::cout << "LAUNCH FAILED" << std::endl;
    }

    //Application::loop();

    std::unique_ptr<INoise> noise = std::make_unique<PerlinNoise>(1);
    loopNoise(noise.get());
    glfwTerminate();

    std::cout << "GAME PROCESS END" << std::endl;

    return 0;
}