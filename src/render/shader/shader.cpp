#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

Shader::Shader(std::string &vertPath, std::string &fragPath) {
    GLuint vertId = loadShaderFile(GL_VERTEX_SHADER, vertPath);
    GLuint fragId = loadShaderFile(GL_FRAGMENT_SHADER, fragPath);

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
        std::cout << "[Shader] UNIFORM \"" << name << "\" NOT FOUND";
    }

    return location;
}
