#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_Tex;

uniform mat4 viewProjectionMatrix, modelMatrix;

out vec3 normal;

void main() {
    normal = normalize(vec3(modelMatrix * vec4(a_Normal, 0.0)));
    gl_Position = viewProjectionMatrix * modelMatrix * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec3 normal;

struct LightDir {
    vec3 direction;
    vec3 color;
    float intensity;
};

uniform LightDir dirLights[10];
uniform int dirLightCount;

void main() {
    vec3 lightSum = vec3(0.0);
    for (int i = 0; i < dirLightCount; ++i) {
        lightSum += dirLights[i].intensity * max(dot(normal, -normalize(dirLights[i].direction)), 0.0) * dirLights[i].color;
    }
    color = vec4(0.1, 0.6, 0.3, 1.0) * vec4(lightSum, 1.0);
}
