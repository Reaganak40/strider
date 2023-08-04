#pragma once

#include "quad.h"
#include "app.h"

#include <renderer/renderer.h>
#include "procedure.h"
#include "entityManagementSystem.h"

#include "layer.h"
#include "gui.h"

namespace core {
	
}
class Scene {
	EntityID entityCounter;

	EntityManagementSystem m_EMS;
	std::vector<Procedure*> m_procedure_stack;

	core::VertexArray m_VAO;
	SceneID m_SceneID;

	core::Renderer& m_renderer;
	core::SceneCallback& m_SceneCallback;

	std::vector<core::Layer> m_layers;
	
public:
	Scene(core::Renderer& globalRenderer, core::SceneCallback& callToInstance);
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

		m_layers[layer].AddMesh(eid, obj.vertices, 4, ib, 6);

		m_EMS.PushNewEntity(
			obj.m_Entity,
			{ obj.position, obj.size },
			{ obj.transform },
			{ layer, m_layers[layer].GetMeshVectorOffset(eid), 4}
		);
		
		return eid;
	}

	void AttachGUI(GuiTemplate* nGUI, int layer = -1);

	void AddProcedure(Procedure* nProc);
	void Update(float deltaTime);

	friend class core::Renderer;
	friend class core::AppInstance;
};


