#include "config.h"

float Config::fov;
float Config::speed;

void Config::load() {
    fov = 3.14f / 2;
    speed = 1;
}
