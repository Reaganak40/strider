#include "vertexBuffer.h"

VertexBufferID RegisterVertexBuffer(void* vertices, size_t size) {
	VertexBufferID bufferID = 0;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	return bufferID;
}
