#pragma once

#include "indexBuffer.h"
#include "error.h"

class Renderer {
private:
public:

	void static inline Clear() { glClear(GL_COLOR_BUFFER_BIT); }

	void static inline Draw(IndexBufferCount count) { glCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr)); }

	void static inline SetBackgroundColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
};