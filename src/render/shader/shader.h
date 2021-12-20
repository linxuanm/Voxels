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
    void setOffset(glm::vec3 offsetVec);

private:
    GLint mvp;
    GLint offset;
};

class SkyboxShader: public Shader {

public:
    SkyboxShader();
    void updateMVP(Camera &camera);

private:
    GLint mvp;
};

class HUDShader: public Shader {

public:
    HUDShader();
    void updateOrtho();

private:
    GLint mvp;
};

namespace Shaders {
    WorldOpaqueShader &shaderOpaque();
    SkyboxShader &shaderSkybox();
    HUDShader &shaderHUD();
};
