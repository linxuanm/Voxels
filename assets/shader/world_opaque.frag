#version 410 core

layout(location = 0) out vec4 color;

in VertOut {
    vec2 texCoord;
    vec3 normal;
} vertOut;

uniform sampler2D texSampler;

void main() {
    float light = dot(vertOut.normal, vec3(0, 1, 0)) / 4 + 0.75f;
    vec4 texColor = texture(texSampler, vertOut.texCoord);
    color = texColor * light;
}