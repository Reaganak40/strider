#pragma once
#include "opengl/glCore.h"
#include "gui.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "shader.h"

#include <vector>

#define VAO_MAX_RENDER_UNITS 64
#define VAO_MAX_RENDER_UNITS_REACHED 65
namespace core {
	/*
		Contains all OpenGL rendering buffers/IDs for a draw call.
	*/
	struct CoreRenderUnit {
		VertexBufferID vbo;
		IndexBufferID ibo;
		IndexBufferCount iboCount;
		ShaderID shader;
	};


	typedef unsigned int VertexArrayID;

	struct BatchBuffer {
		DynamicVertexBuffer batchVBO;
		DynamicIndexBuffer	batchIBO;
	};

	class VertexArray {
	private:

		
		VertexArrayID id;
		
		std::vector<CoreRenderUnit> CRUs;
		std::vector<std::shared_ptr<BatchBuffer>> m_BatchBuffers;
		std::vector<GuiTemplate*> m_GUIs;

		ShaderManager* m_shader_manager;

	public:
		VertexArray(ShaderManager* nShaderManager = nullptr);
		~VertexArray();

		void NewBatchBuffer(const LayerID& l_ID);
		std::shared_ptr<BatchBuffer> GetBatchBuffer(const LayerID& l_ID);
		void UpdateBatchBuffer(const LayerID& l_ID);

		void inline Bind() { glCall(glBindVertexArray(id)); }
		void inline Unbind() { glBindVertexArray(0); }

		inline std::vector<CoreRenderUnit>& GetCRUs() { return CRUs; }

		VertexArrayID inline GetID() { return id; }

		void SetGUI(const LayerID& l_ID, GuiTemplate*& nGUI);
		void RenderGUI(const LayerID& l_ID);

		void DefineVertexBufferLayout(size_t vertexType);
	private:
	};
}