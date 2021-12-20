#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out VertOut {
    vec2 texCoord;
    vec3 normal;
} vertOut;

uniform mat4 MVP;
uniform vec3 offset;

void main() {
    vec3 pos = position.xyz + offset * 16.0f;
    gl_Position = MVP * vec4(pos, 1.0f);
    vertOut.texCoord = texCoord;
    vertOut.normal = normal;
}