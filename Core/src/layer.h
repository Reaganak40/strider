#pragma once
#include <renderer/renderer.h>
#include "gui.h"

namespace core {
	class Layer {
	private:
		VertexArray& m_sceneVAO;
		BatchBufferID m_bbid;
		std::shared_ptr <BatchBuffer> m_batch_buffer;

		GuiTemplate* m_layer_gui;
	public:
		Layer(VertexArray& nSceneVAO, BatchBufferID nBBID);
		~Layer();

		void AddMesh(EntityID eid, Vertex* vertices, unsigned int VertexCount, IndexBuffer* indices, unsigned int IndexCount);
		
		inline Vertex* GetVertexBuffer() { return m_batch_buffer->batchVBO.GetVertexBuffer(); }
		inline unsigned int GetMeshVectorOffset(EntityID eid) { return m_batch_buffer->batchVBO.GetMeshVectorOffset(eid); }
		void UpdateBatchBuffer();

		void AttachGUI(GuiTemplate* nGUI);
		void UpdateGUI(float deltaTime);
		void RenderGUI();

		CoreRenderUnit& GetCRU();
	};
}