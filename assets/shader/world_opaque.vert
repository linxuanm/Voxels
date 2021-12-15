#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 outTexCoord;

uniform mat4 MVP;
uniform float offsetX;
uniform float offsetY;

void main() {
    vec3 pos = vec3(position.x + offsetX * 16.0f, position.y + offsetY * 16.0f, position.z);
    gl_Position = MVP * vec4(pos, 1.0f);
    outTexCoord = texCoord;
}