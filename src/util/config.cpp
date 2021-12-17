#include "config.h"

float Config::fov;
float Config::speed;
float Config::mouseSen;
float Config::reachDistance;

// TODO: load from config file
void Config::load() {
    fov = 3.14f / 2;
    speed = 2;
    mouseSen = 0.15f;
    reachDistance = 10.0f;
}
