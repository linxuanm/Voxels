#include "noise.h"

#include <random>
#include <iostream>

static float perlinFade(float x) {
    return x * x * x * (x * (x * 6 - 15) + 10);
}

PerlinNoise::PerlinNoise(uint32_t inSeed): seed(inSeed) {
    std::mt19937 mt{seed};

    for (int i = 0; i < PERM_LENGTH; i++) {
        p[i] = i;
    }

    for (int i = 0; i < PERM_LENGTH; i++) {
        std::uniform_int_distribution<int> dist{0, PERM_LENGTH - i};

        int swap = dist(mt) + i;
        int curr = p[i];

        p[i] = p[swap];
        p[i + PERM_LENGTH] = p[swap];
        p[swap] = curr;
    }
}

float PerlinNoise::genNoise(float u, float v) {
    int uInt = static_cast<int>(u);
    int vInt = static_cast<int>(v);
    float uFrac = u - uInt;
    float vFrac = v - vInt;
    float uFade = perlinFade(uFrac);
    float vFade = perlinFade(vFrac);

    return u * v;
}
