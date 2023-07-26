#pragma once
#include "core.h"

typedef unsigned int IndexBuffer;
typedef unsigned int IndexBufferID;
typedef unsigned int IndexBufferCount;

IndexBufferID RegisterIndexBuffer(IndexBuffer* ibo, size_t size);

inline void BindIndexBuffer(IndexBufferID ibo) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); }
inline void UnbindIndexBuffer() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

