#include "vertexArray.h"
#include "error.h"
#include "renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	
	for (int i = 0; i < VAO_MAX_RENDER_UNITS; i++) {
		CRUs[i] = { 0 };
	}

	renderUnitCount = 0;
}

VertexArray::~VertexArray()
{
	for (unsigned int i = 0; i < renderUnitCount; i++) {
		glDeleteBuffers(1, &(CRUs[i].vbo));
	}
	glDeleteVertexArrays(1, &id);
}

void VertexArray::PushCRU_Data(void* vboData, size_t vertexSize, unsigned int vertexCount, IndexBufferID ibo, IndexBufferCount iboCount, ShaderID shader)
{
	if (renderUnitCount >= VAO_MAX_RENDER_UNITS) {
		std::cout << "Warning: Maximum Core rendering units reached!\n";
		return;
	}

	CRUs[renderUnitCount].vbo = RegisterVertexBuffer(vboData, vertexSize * vertexCount);
	CRUs[renderUnitCount].ibo = ibo;
	CRUs[renderUnitCount].iboCount = iboCount;
	CRUs[renderUnitCount].shader = shader;

	if (!renderUnitCount) {
		// first VBO => define its layout
		DefineVertexBufferLayout(vertexSize);
	}
	renderUnitCount++;
}


void VertexArray::DrawAll()
{
	if (renderUnitCount == 0) {
		return;
	}
	BindVertexBuffer(CRUs[0].vbo);
	BindIndexBuffer(CRUs[0].ibo);
	BindShader(CRUs[0].shader);
	Renderer::Draw(CRUs[0].iboCount);

	for (unsigned int i = 1; i < renderUnitCount; i++) {
		
		BindVertexBuffer(CRUs[i].vbo);
		if (CRUs[i].ibo != CRUs[i - 1].ibo) {
			BindIndexBuffer(CRUs[i].ibo);
		}

		if (CRUs[i].shader != CRUs[i - 1].shader) {
			BindShader(CRUs[i].shader);
		}
		Renderer::Draw(CRUs[i].iboCount);
	}
}

void VertexArray::DefineVertexBufferLayout(size_t vertexType) {

	switch (vertexType) {
	case VERTEX_TYPE_PTC:
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexType, (const void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexType, (const void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vertexType, (const void*)(sizeof(float) * 5));
		break;

	case VERTEX_TYPE_PT:
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexType, (const void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexType, (const void*)(sizeof(float) * 3));
		break;

	default:
		printf("Warning: Could not specifiy vertex buffer layout with vertexType: %d\n", vertexType);
	}
}

