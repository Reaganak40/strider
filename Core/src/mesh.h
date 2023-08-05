#pragma once
#include "component.h"

struct Vertex {
	float position[3];
	float texCoords[2];
	int texID;
	float colorRGBA[4];
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

struct Vertex_PC {
	float position[3];
	float colorRGBA[4];
};

#define VERTEX_TYPE_BASE sizeof(Vertex)
#define VERTEX_TYPE_PTC sizeof(Vertex_PTC)
#define VERTEX_TYPE_PT sizeof(Vertex_PT)
#define VERTEX_TYPE_PC sizeof(Vertex_PC)

typedef unsigned int IndexBuffer;

struct Mesh {
	EntityID eid;
	Vertex* vertices;
	unsigned int vertexCount;
	IndexBuffer* indices;
	unsigned int indexCount;
};
