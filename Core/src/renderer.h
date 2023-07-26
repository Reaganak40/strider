#pragma once

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "shader.h"

struct CoreRenderUnit {
	VertexBufferID vbo;
	IndexBufferID ibo;
	IndexBufferCount iboCount;
	ShaderID shader;
};

class Renderer {
private:
	float clearColor[4];
public:

	void inline Clear() { glClear(GL_COLOR_BUFFER_BIT); }

	void Draw(CoreRenderUnit cru);

	void inline SetBackgroundColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
};