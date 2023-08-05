#include "scene.h"

unsigned int Scene::SceneCounter = 0;

Scene::Scene()
	: m_framework(Framework::GetInstance()), m_message_manager(MessageManager::GetInstance())
{
	m_SceneID = SceneCounter;
	m_entities.SetSceneID(m_SceneID);
	SceneCounter++;

	AddProcedure(new UpdateFinal);
}

Scene::~Scene()
{
	for (auto& ptr : m_procedure_stack) {
		delete ptr;
	}

	for (auto& ptr : m_layers) {
		delete ptr;
	}
}
unsigned int Scene::AddLayer()
{
	m_layers.push_back(new Layer(m_SceneID, m_layers.size()));
	m_entities.PushNewBatch(m_layers.size() - 1);

	return (unsigned int)m_layers.size() - 1;
}

void Scene::AttachGUI(GuiTemplate* nGUI, int layer)
{
	if (layer < 0) {
		m_layers.back()->AttachGUI(nGUI);
	}
	else {
		m_layers[layer]->AttachGUI(nGUI);
	}
}

void Scene::AddProcedure(Procedure* nProc)
{
	nProc->AssignEMS(&m_entities);
	m_procedure_stack.push_back(nProc);
}

void Scene::Update(float deltaTime)
{
	for (auto& layer : m_layers) {
		layer->UpdateGUI(deltaTime);
	}

	for (int i = (m_procedure_stack.size() - 1); i >= 0; i--) {
		m_procedure_stack[i]->OnUpdate(deltaTime);
	}
}

void Scene::Activate()
{
	m_message_manager->SetEntityManager(&m_entities);
}

EntityID Scene::AddEntity(EntityTemplate* nEntity, unsigned int layer)
{
	return m_entities.PushNewEntity(layer, nEntity);
}

