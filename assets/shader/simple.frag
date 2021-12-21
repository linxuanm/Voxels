#version 410 core

layout(location = 0) out vec4 color;

in vec2 outTexCoord;

uniform sampler2D texSampler;
uniform vec4 inColor;

void main() {
    color = texture(texSampler, outTexCoord) * inColor;
}