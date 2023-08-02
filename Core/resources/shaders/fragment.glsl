#version 330 core

in vec2 vTexCoord;
smooth in vec4 vColor;

layout (location = 0) out vec4 color;

uniform vec4 uColor;
uniform sampler2D uTexture; 

void main() {
	color = vColor;
}