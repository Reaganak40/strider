#include "layer.h"

namespace core {

	Layer::Layer(VertexArray& nSceneVAO, BatchBufferID nBBID)
		: m_sceneVAO(nSceneVAO), m_layer_gui(nullptr)
	{
		m_bbid = nBBID;
		m_batch_buffer = nSceneVAO.GetBatchBuffer(m_bbid);
	}

	Layer::~Layer()
	{
		if (m_layer_gui != nullptr) {
			delete m_layer_gui;
		}
	}

	void Layer::AddMesh(EntityID eid, Vertex* vertices, unsigned int VertexCount, IndexBuffer* indices, unsigned int IndexCount)
	{
		m_batch_buffer->batchVBO.PushBack(eid, vertices, VertexCount);
		m_batch_buffer->batchIBO.PushBack(eid, indices, IndexCount, VertexCount);

		if (m_batch_buffer->batchVBO.MeshCount() == 1) {
			m_sceneVAO.Bind();
			m_batch_buffer->batchVBO.BindVBO();
			m_batch_buffer->batchVBO.glUpdateBuffer();
			m_sceneVAO.DefineVertexBufferLayout(sizeof(core::Vertex));
		}
	}

	void Layer::UpdateBatchBuffer()
	{
		m_batch_buffer->batchVBO.glUpdateBuffer();
		if (m_batch_buffer->batchIBO.glUpdateBuffer()) {
			m_sceneVAO.GetCRU(m_bbid).iboCount = m_batch_buffer->batchIBO.IndexCount();
		}
	}

	void Layer::AttachGUI(GuiTemplate* nGUI)
	{
		if (m_layer_gui != nullptr) {
			delete m_layer_gui;
		}
		m_layer_gui = nGUI;
	}

	void Layer::UpdateGUI(float deltaTime)
	{
		if (m_layer_gui != nullptr) {
			m_layer_gui->OnUpdate(deltaTime);
		}
	}

	void Layer::RenderGUI()
	{
		if (m_layer_gui != nullptr) {
			m_layer_gui->OnRender();
		}
	}

	CoreRenderUnit& Layer::GetCRU()
	{
		return m_sceneVAO.GetCRU(m_bbid);
	}
}
