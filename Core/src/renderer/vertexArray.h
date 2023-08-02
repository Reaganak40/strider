#pragma once
#include "core.h"
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
	typedef unsigned int BatchBufferID;

	struct BatchBuffer {
		DynamicVertexBuffer batchVBO;
		DynamicIndexBuffer	batchIBO;
	};

	class VertexArray {
	private:

		
		VertexArrayID id;
		std::vector<CoreRenderUnit> CRUs;

		std::unordered_map<BatchBufferID, std::shared_ptr<BatchBuffer>> m_BatchBuffers;

		ShaderManager* m_shader_manager;

	public:
		VertexArray(ShaderManager* nShaderManager = nullptr);
		~VertexArray();

		BatchBufferID NewBatchBuffer();
		std::shared_ptr<BatchBuffer> GetBatchBuffer(BatchBufferID bbID);
		void UpdateBatchBuffer(BatchBufferID bbID);
		
		void PushCRU_Data(void* vboData, size_t vertexSize, unsigned int vertexCount,
			IndexBufferID ibo, IndexBufferCount iboCount, ShaderID shader);

		void inline Bind() { glBindVertexArray(id); }
		void inline Unbind() { glBindVertexArray(0); }

		inline const std::vector<CoreRenderUnit>& GetCRUs() { return CRUs; }

		VertexArrayID inline GetID() { return id; }

	private:
		void DefineVertexBufferLayout(size_t vertexType);
	};
}