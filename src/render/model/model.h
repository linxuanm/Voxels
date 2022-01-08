#pragma once

#include "render/view/buffer_builder.h"

class IModel {

public:
    virtual void buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) = 0;
};

class SixFaceModel: public virtual IModel {

public:
    SixFaceModel(int inU, int inV);
    void buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) override;

private:
    int u, v;
};
