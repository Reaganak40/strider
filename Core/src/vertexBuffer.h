#pragma once
#include "core.h"

struct VertexBufferLayoutElement {
	unsigned int glType;
	int count;

	unsigned int GetSize() {
		switch (glType) {
		case GL_FLOAT:
			return sizeof(float);
		case GL_INT:
			return sizeof(int);
		}
		std::cout << "Warning: Could not find sizeof(type): " << std::hex << glType << std::endl;
		return 0;
	}
};

/*
	Contains 3-float positions and 2-float texCoords.
*/
struct Vertex_PT {
	float position[3];
	float texCoords[2];
};

/*
	Contains 3-float positions, 2-float texCoords, and 4-float RGBA.
*/
struct Vertex_PTC {
	float position[3];
	float texCoords[2];
	float colorRGBA[4];
};

#define VERTEX_TYPE_PTC sizeof(Vertex_PTC)
#define VERTEX_TYPE_PT sizeof(Vertex_PT)


typedef unsigned int VertexBufferID;

VertexBufferID RegisterVertexBuffer(void* vertices, size_t size);

inline void BindVertexBuffer(VertexBufferID vbo) { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
inline void UnbindVertexBuffer() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

