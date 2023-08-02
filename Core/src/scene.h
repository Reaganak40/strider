#pragma once

#include "quad.h"
#include "app.h"

#include <renderer/renderer.h>


class Scene {
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
		core::IndexBuffer ib[6] = {
			0, 1, 2,
			2, 3, 0
		};
		m_VAO.GetBatchBuffer(layers[layer])->batchVBO.PushBack(obj.eid, obj.vertices, 4);
		m_VAO.GetBatchBuffer(layers[layer])->batchIBO.PushBack(obj.eid, ib, 6, 4);
	}

	friend class core::Renderer;
	friend class core::AppInstance;
};
