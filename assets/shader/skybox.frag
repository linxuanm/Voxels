#version 410 core

layout(location = 0) out vec4 color;

in vec3 outTexCoord;

uniform samplerCube texSampler;

void main() {
   color = texture(texSampler, outTexCoord);
}