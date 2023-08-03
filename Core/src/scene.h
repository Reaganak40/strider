#pragma once

#include "quad.h"
#include "app.h"

#include <renderer/renderer.h>
#include "procedure.h"
#include "entityManagementSystem.h"

class Scene {
	EntityID entityCounter;

	EntityManagementSystem m_EMS;
	std::vector<Procedure*> m_procedure_stack;

	core::VertexArray m_VAO;
	SceneID m_SceneID;

	std::vector<core::BatchBufferID> layers;
	core::Renderer& m_renderer;
public:
	Scene(core::Renderer& globalRenderer);
	~Scene();

	unsigned int AddLayer();

	/*
		Use an EntityTemplate to add an entity to the Scene.
	*/
	template<typename EntityDef>
	EntityID AddToScene(EntityDef& obj, unsigned int layer = 0) { return -1; }


	template<>
	EntityID AddToScene<Quad>(Quad& obj, unsigned int layer) {
		EntityID eid = m_EMS.Count();
		core::IndexBuffer ib[6] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO.GetBatchBuffer(layers[layer])->batchVBO.PushBack(eid, obj.vertices, 4);
		m_VAO.GetBatchBuffer(layers[layer])->batchIBO.PushBack(eid, ib, 6, 4);
		
		if (m_VAO.GetBatchBuffer(layers[layer])->batchVBO.MeshCount() == 1) {
			m_VAO.Bind();
			m_VAO.GetBatchBuffer(layers[layer])->batchVBO.BindVBO();
			m_VAO.GetBatchBuffer(layers[layer])->batchVBO.glUpdateBuffer();
			m_VAO.DefineVertexBufferLayout(sizeof(core::Vertex));
		}

		m_EMS.PushNewEntity(
			obj.m_Entity,
			{ obj.position, obj.size },
			{ obj.transform },
			{ layer, m_VAO.GetBatchBuffer(layers[layer])->batchVBO.GetMeshVectorOffset(eid), 4 }
		);
		
		return eid;
	}

	void AddProcedure(Procedure* nProc);
	void Update(float deltaTime);

	friend class core::Renderer;
	friend class core::AppInstance;
};


