#include "config.h"

#include "world/chunk.h"

float Config::fov;
float Config::speed;
float Config::mouseSen;
float Config::reachDistance;
float Config::actionCooldown;
float Config::crosshairSize;
int Config::maxChunkLoadPerSec;

ChunkPos Config::renderDist;

// TODO: load from config file
void Config::load() {
    fov = 3.14159f / 2;
    speed = 5;
    mouseSen = 0.15f;
    reachDistance = 5.0f;
    actionCooldown = 0.15f;
    crosshairSize = 50.0f;
    renderDist = 6;
    maxChunkLoadPerSec = 5;
}
