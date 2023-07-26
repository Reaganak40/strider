#include "indexBuffer.h"

IndexBufferID RegisterIndexBuffer(IndexBuffer* ibo, size_t size) {
	IndexBufferID bufferID = 0;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, ibo, GL_STATIC_DRAW);
	return bufferID;
}


