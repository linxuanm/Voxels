#pragma once

#include "render/texture.h"
#include "render/view/buffer_builder.h"

class IModel {

public:
    virtual ~IModel() = default;
    virtual void buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) = 0;
};

class SixFaceModel: public virtual IModel {

public:
    explicit SixFaceModel(const BlockUV &inUV);
    void buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) override;

private:
    BlockUV uv;
};

class FourFaceModel: public virtual IModel {

public:
    FourFaceModel(
        const BlockUV &inTopUV,
        const BlockUV &inSideUV,
        const BlockUV &inBottomUV
    );
    void buffer(BufferBuilder &buf, BlockPos pos, bool exposed[6]) override;

private:
    BlockUV topUV;
    BlockUV sideUV;
    BlockUV bottomUV;
};
