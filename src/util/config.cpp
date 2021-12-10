#include "config.h"

float Config::fov = 0;

void Config::load() {
    fov = 3.14f / 2;
}
