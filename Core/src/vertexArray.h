#pragma once
#include "core.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "shader.h"

/*
	Contains all OpenGL rendering buffers/IDs for a draw call.
*/
struct CoreRenderUnit {
	VertexBufferID vbo;
	IndexBufferID ibo;
	IndexBufferCount iboCount;
	ShaderID shader;
};

#define VAO_MAX_RENDER_UNITS 64

typedef unsigned int VertexArrayID;

class VertexArray {
private:
	VertexArrayID id;
	CoreRenderUnit CRUs[VAO_MAX_RENDER_UNITS];
	unsigned int renderUnitCount;
public:
	VertexArray();
	~VertexArray();

	void PushCRU_Data(void* vboData, size_t vertexSize, unsigned int vertexCount,
		IndexBufferID ibo, IndexBufferCount iboCount, ShaderID shader);

	void inline Bind()   { glBindVertexArray(id); }
	void inline Unbind() { glBindVertexArray(0);  }

	void DrawAll();

private:
	void DefineVertexBufferLayout(size_t vertexType);
};