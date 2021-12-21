#pragma once

#include <string>
#include <memory>

#include "gl.h"
#include "render/view/camera.h"

class Shader {

public:
    // different vert/frag combination is rare in Voxels' case
    Shader(const std::string &vert, const std::string &frag);
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

class SimpleShader: public Shader {

public:
    SimpleShader(const std::string &vert, const std::string &frag);
    void updateMVP(const glm::mat4 &mvpMat);
    void updateColor(const glm::vec4 &colorVal);

private:
    GLint mvp;
    GLint color;
};

namespace Shaders {
    WorldOpaqueShader &shaderOpaque();
    SkyboxShader &shaderSkybox();
    SimpleShader &shaderSimple();
    SimpleShader &shaderColor();
};
