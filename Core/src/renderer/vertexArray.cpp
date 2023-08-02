#include "vertexArray.h"
#include "error.h"
#include "renderer.h"

#include "shader.h"
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace core {

	VertexArray::VertexArray(ShaderManager* nShaderManager)
		: m_shader_manager(nShaderManager)
	{
		glGenVertexArrays(1, &id);
		CRUs = {};
	}

	VertexArray::~VertexArray()
	{
		for (const auto& cru : CRUs) {
			glDeleteBuffers(1, &(cru.vbo));
			glDeleteBuffers(1, &(cru.ibo));
			glDeleteProgram(cru.shader);
		}
		glDeleteVertexArrays(1, &id);
	}

	BatchBufferID VertexArray::NewBatchBuffer()
	{

		if (CRUs.size() == VAO_MAX_RENDER_UNITS_REACHED) {
			printf("Warning: VAO Buffer limit reached!\n");
			return VAO_MAX_RENDER_UNITS_REACHED;
		}

		m_BatchBuffers[CRUs.size()] = std::make_shared<BatchBuffer>();

		CRUs.push_back({});
		CRUs.back().vbo = m_BatchBuffers[CRUs.size()-1]->batchVBO.RegisterWithVAO();
		CRUs.back().ibo = m_BatchBuffers[CRUs.size()-1]->batchIBO.RegisterWithVAO();
		CRUs.back().iboCount = 0;
		CRUs.back().shader = m_shader_manager->GetShader("default")->GetID();

		return m_BatchBuffers.size() - 1;
	}

	std::shared_ptr<BatchBuffer> VertexArray::GetBatchBuffer(BatchBufferID bbID)
	{
		return m_BatchBuffers[bbID];
	}

	void VertexArray::UpdateBatchBuffer(BatchBufferID bbID)
	{
		
		if (m_BatchBuffers.find(bbID) != m_BatchBuffers.end()) {
			if (m_BatchBuffers[bbID]->batchVBO.glUpdateBuffer() == 2) {
				DefineVertexBufferLayout(sizeof(Vertex));
			}
			CRUs[bbID].iboCount = m_BatchBuffers[bbID]->batchIBO.glUpdateBuffer();
		}
	}

	void VertexArray::PushCRU_Data(void* vboData, size_t vertexSize, unsigned int vertexCount, IndexBufferID ibo, IndexBufferCount iboCount, ShaderID shader)
	{
		if (CRUs.size() == VAO_MAX_RENDER_UNITS_REACHED) {
			std::cout << "Warning: Maximum Core rendering units reached!\n";
			return;
		}

		CRUs.push_back({});
		CRUs.back().vbo = RegisterVertexBuffer(vboData, vertexSize * vertexCount);
		CRUs.back().ibo = ibo;
		CRUs.back().iboCount = iboCount;
		CRUs.back().shader = shader;

		if (CRUs.size() == 1) {
			// first VBO => define its layout
			DefineVertexBufferLayout(vertexSize);
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

		case VERTEX_TYPE_BASE:
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexType, (const void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexType, (const void*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, vertexType, (const void*)offsetof(Vertex, texID));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vertexType, (const void*)offsetof(Vertex, colorRGBA));
			break;

		default:
			printf("Warning: Could not specifiy vertex buffer layout with vertexType: %d\n", vertexType);
		}
	}
}