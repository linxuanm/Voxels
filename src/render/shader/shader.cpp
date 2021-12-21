#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "game/application.h"

static GLuint loadShaderFile(GLuint type, const std::string &path) {
    GLuint id = glCreateShader(type);

    std::ifstream file{path};

    if (!file.good()) {
        std::cout << "[Shader] FILE \"" << path << "\" DOES NOT EXIST" << std::endl;
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string raw = buffer.str();
    const char *src = raw.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int logLen;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
        char *log = new char[logLen];
        glGetShaderInfoLog(id, logLen, &logLen, log);

        std::cout << "[Shader] SHADER COMPILATION FAILED: " << path << std::endl;
        std::cout << log << std::endl;

        delete[] log;
    }

    return id;
}

Shader::Shader(const std::string &vert, const std::string &frag) {
    GLuint vertId = loadShaderFile(GL_VERTEX_SHADER, vert);
    GLuint fragId = loadShaderFile(GL_FRAGMENT_SHADER, frag);

    program = glCreateProgram();
    glAttachShader(program, vertId);
    glAttachShader(program, fragId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertId);
    glDeleteShader(fragId);
}

Shader::~Shader() {
    glDeleteProgram(program);
}

void Shader::bind() {
    glUseProgram(program);
}

GLint Shader::getUniformLocation(GLchar *name) {
    int location = glGetUniformLocation(program, name);

    if (location == -1) {
        std::cout << "[Shader] UNIFORM \"" << name << "\" NOT FOUND" << std::endl;
    }

    return location;
}

WorldOpaqueShader::WorldOpaqueShader()
: Shader("assets/shader/world_opaque.vert", "assets/shader/world_opaque.frag") {
    mvp = getUniformLocation((char *) "MVP");
    offset = getUniformLocation((char *) "offset");
}

void WorldOpaqueShader::updateMVP(Camera &camera) {
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &camera.getViewProjMat()[0][0]);
}

void WorldOpaqueShader::setOffset(glm::vec3 offsetVec) {
    glUniform3fv(offset, 1, &offsetVec[0]);
}

SkyboxShader::SkyboxShader()
: Shader("assets/shader/skybox.vert", "assets/shader/skybox.frag") {
    mvp = getUniformLocation((char *) "MVP");
}

void SkyboxShader::updateMVP(Camera &camera) {
    glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMat()));
    glm::mat4 proj = camera.getProjMat();
    glm::mat4 projView = proj * view;
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &projView[0][0]);
}

SimpleShader::SimpleShader(const std::string &vert, const std::string &frag)
: Shader(vert, frag) {
    mvp = getUniformLocation((char *) "MVP");
    color = getUniformLocation((char *) "inColor");
}

void SimpleShader::updateMVP(const glm::mat4 &mvpMat) {
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &mvpMat[0][0]);
}

void SimpleShader::updateColor(const glm::vec4 &colorVal) {
    glUniform4fv(color, 1, &colorVal[0]);
}

WorldOpaqueShader &Shaders::shaderOpaque() {
    static WorldOpaqueShader shader;
    return shader;
}

SkyboxShader& Shaders::shaderSkybox() {
    static SkyboxShader shader;
    return shader;
}

SimpleShader& Shaders::shaderSimple() {
    static SimpleShader shader{
        "assets/shader/simple.vert",
        "assets/shader/simple.frag"
    };

    return shader;
}
