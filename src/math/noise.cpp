#include "noise.h"

#include <glm/glm.hpp>
#include <random>
#include <iostream>

static float perlinFade(float x) {
    return x * x * x * (x * (x * 6 - 15) + 10);
}

static float lerp(float t, float a, float b) {
    return a + t * (b - a);
}

static float grad(int hash, float u, float v) {
    return ((hash & 1) == 0 ? u : -u) + ((hash & 2) == 0 ? v : -v);
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
    int uInt = static_cast<int>(glm::floor(u)) & 255;
    int vInt = static_cast<int>(glm::floor(v)) & 255;
    float uFrac = u - glm::floor(u);
    float vFrac = v - glm::floor(v);

    float uFade = perlinFade(uFrac);
    float vFade = perlinFade(vFrac);

    int A = p[uInt] + vInt;
    int B = p[uInt + 1] + vInt;

    float val = lerp(
        vFade,
        lerp(
            uFade,
            grad(p[A], uFrac, vFrac),
            grad(p[B], uFrac - 1, vFrac)
        ),
        lerp(
            uFade,
            grad(p[A + 1], uFrac, vFrac - 1),
            grad(p[B + 1], uFrac - 1, vFrac - 1)
        )
    );

    return val;
}

CompositePerlin::CompositePerlin(uint32_t seed, uint8_t layers, float inPow)
: persistence(inPow) {
    for (int i = 0; i < layers; i++) {
        octaves.emplace_back(seed);
    }
}

float CompositePerlin::genNoise(float u, float v) {
    float out = 0;
    float dampen = 1;
    float freq = 1;

    for (auto &octave: octaves) {
        out += octave.genNoise(u * freq, v * freq) * dampen;

        dampen *= persistence;
        freq *= 2;
    }

    return out;
}
