#pragma once

#include "quad.h"
#include "app.h"

#include <renderer/renderer.h>


class Scene {
	EntityID entityCounter;

	core::VertexArray m_VAO;
	SceneID m_SceneID;

	std::vector<core::BatchBufferID> layers;
	core::Renderer& m_renderer;
public:
	Scene(core::Renderer& globalRenderer);
	~Scene();

	unsigned int AddLayer();

	template<typename GameObj>
	void AddToScene(GameObj& obj, unsigned int layer = 0) {}


	template<>
	void AddToScene<Quad>(Quad& obj, unsigned int layer) {
		obj.m_ID = entityCounter++; // give quad an entityID
		
		core::IndexBuffer ib[6] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO.GetBatchBuffer(layers[layer])->batchVBO.PushBack(obj.m_ID, obj.vertices, 4);
		m_VAO.GetBatchBuffer(layers[layer])->batchIBO.PushBack(obj.m_ID, ib, 6, 4);
		
		if (m_VAO.GetBatchBuffer(layers[layer])->batchVBO.MeshCount() == 1) {
			m_VAO.Bind();
			m_VAO.GetBatchBuffer(layers[layer])->batchVBO.BindVBO();
			m_VAO.GetBatchBuffer(layers[layer])->batchVBO.glUpdateBuffer();
			m_VAO.DefineVertexBufferLayout(sizeof(core::Vertex));
		}

		delete[] obj.vertices;
		obj.vertices = m_VAO.GetBatchBuffer(layers[layer])->batchVBO.GetMeshBuffer(obj.m_ID);
	}

	friend class core::Renderer;
	friend class core::AppInstance;
};
