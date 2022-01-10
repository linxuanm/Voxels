#pragma once

#include <stb_image.h>

#include "gl.h"
#include "math/noise.h"
#include "render/texture.h"

typedef std::unique_ptr<Texture> TexPtr;

/*
 * This file is dedicated to drawing testing data and stuff.
 * Currently it is used for tuning noises.
 */
namespace Testing {

    void noiseTexLoop(INoise *noise, float scale);
    void drawQuadLoop(float size);
    TexPtr genNoiseTex(NoiseSampler sampler, int width, int height);
};
