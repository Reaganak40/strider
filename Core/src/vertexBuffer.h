#pragma once
#include "core.h"

/*
	Makes up 1 positional vertex.
*/
struct VertexBuffer2f {
	float positions[2];
};

typedef unsigned int VertexBufferID;

VertexBufferID RegisterVertexBuffer(VertexBuffer2f* vertices, size_t size);

inline void BindVertexBuffer(VertexBufferID vbo) { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
inline void UnbindVertexBuffer() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

