#version 410 core

layout(location = 0) out vec4 color;

in vec2 outTexCoord;

uniform vec4 uniformColor;
uniform sampler2D texSampler;

void main() {
   vec4 texColor = texture(texSampler, outTexCoord);
   color = texColor;
}