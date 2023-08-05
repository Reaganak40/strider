#pragma once

#include "quad.h"
#include "messageManager.h"
#include "framework.h"
#include "procedure.h"
#include "layer.h"
#include "gui.h"

class Scene {
	SceneID m_SceneID;

	std::vector<Procedure*> m_procedure_stack;

	std::vector<Layer*> m_layers;

	Framework* m_framework;
	MessageManager* m_message_manager;
	EntityManager m_entities;
	
	static unsigned int SceneCounter;
public:
	Scene();
	~Scene();

	unsigned int AddLayer();

	/*
		Use an EntityTemplate to add an entity to the Scene.
	*/
	template<typename EntityDef>
	EntityID AddToScene(EntityDef& obj, unsigned int layer = 0) { return -1; }


	template<>
	EntityID AddToScene<Quad>(Quad& obj, unsigned int layer) {
		return AddEntity(&obj, layer);
	}

	void AttachGUI(GuiTemplate* nGUI, int layer = -1);

	void AddProcedure(Procedure* nProc);
	void Update(float deltaTime);
	void Activate();


	SceneID inline GetID() { return m_SceneID; }

private:
	EntityID AddEntity(EntityTemplate* nEntity, unsigned int layer);
};



