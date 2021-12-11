#include "voxels.h"

Voxels::Voxels() = default;

Voxels& Voxels::get() {
    static Voxels game;

    return game;
}
