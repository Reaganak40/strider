#include "vertexArray.h"
#include "rendererGL.h"

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

	void VertexArray::NewBatchBuffer(const LayerID& l_ID)
	{

		if (CRUs.size() == VAO_MAX_RENDER_UNITS_REACHED) {
			printf("Warning: VAO Buffer limit reached!\n");
			return;
		}

		if (m_BatchBuffers.size() == l_ID) {
			m_BatchBuffers.push_back(std::make_shared<BatchBuffer>());
		}
		else {
			printf("Error: Insert functionality for batch layers not implemented!\n");
			exit(1);
		}

		CRUs.push_back({});
		CRUs.back().vbo = m_BatchBuffers.back()->batchVBO.RegisterWithVAO();
		CRUs.back().ibo = m_BatchBuffers.back()->batchIBO.RegisterWithVAO();
		CRUs.back().iboCount = 0;
		CRUs.back().shader = m_shader_manager->GetShader("default")->GetID();

		m_GUIs.push_back(nullptr);
	}

	std::shared_ptr<BatchBuffer> VertexArray::GetBatchBuffer(const LayerID& l_ID)
	{
		return m_BatchBuffers.at(l_ID);
	}

	void VertexArray::UpdateBatchBuffer(const LayerID& l_ID)
	{
		m_BatchBuffers.at(l_ID)->batchVBO.glUpdateBuffer();
		if (m_BatchBuffers.at(l_ID)->batchIBO.glUpdateBuffer()) {
			CRUs[l_ID].iboCount = m_BatchBuffers.at(l_ID)->batchIBO.IndexCount();
		}
	}

	void VertexArray::SetGUI(const LayerID& l_ID, GuiTemplate*& nGUI)
	{
		m_GUIs[l_ID] = nGUI;
	}

	void VertexArray::RenderGUI(const LayerID& l_ID)
	{
		if (m_GUIs[l_ID]) {
			m_GUIs[l_ID]->OnRender();
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
			printf("Warning: Could not specifiy vertex buffer layout with vertexType: %d\n", (unsigned int)vertexType);
		}
	}
}