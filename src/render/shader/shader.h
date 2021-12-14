#pragma once

#include <string>
#include <memory>

#include "gl.h"
#include "render/view/camera.h"

class Shader {

public:
    // different vert/frag combination is rare in Voxels' case
    Shader(std::string vertPath, std::string fragPath);
    ~Shader();

    void bind();
    GLint getUniformLocation(GLchar *name);

private:
    GLuint program;
};

class WorldOpaqueShader: public Shader {

public:
    WorldOpaqueShader();
    void updateMVP(Camera &camera);
    void setTexSampler(int channel);
    void setOffsetX(int offset);
    void setOffsetY(int offset);

private:
    GLint texSampler;
    GLint mvp;
    GLint offsetX;
    GLint offsetY;
};

typedef struct {
    GLint texSampler;
    GLint mvp;
    GLint offsetX;
    GLint offsetY;
} ShaderOpaqueData;

namespace Shaders {
    WorldOpaqueShader &shaderOpaque();
};
