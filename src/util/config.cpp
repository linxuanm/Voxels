#include "config.h"

float Config::fov;
float Config::speed;

// TODO: load from config file
void Config::load() {
    fov = 3.14f / 2;
    speed = 2;
}
