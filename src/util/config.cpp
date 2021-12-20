#include "config.h"

float Config::fov;
float Config::speed;
float Config::mouseSen;
float Config::reachDistance;
float Config::actionCooldown;

// TODO: load from config file
void Config::load() {
    fov = 3.14f / 2;
    speed = 3;
    mouseSen = 0.15f;
    reachDistance = 5.0f;
    actionCooldown = 0.15f;
}
