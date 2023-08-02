#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoords;
layout (location = 3) in vec4 color;

out vec2 vTexCoord;
smooth out vec4 vColor;
uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * position;
    vColor = color;
};