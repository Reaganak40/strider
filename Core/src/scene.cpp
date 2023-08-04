#include "scene.h"

Scene::Scene(core::Renderer& globalRenderer, core::SceneCallback& callToInstance)
	: m_renderer(globalRenderer), m_SceneCallback(callToInstance), m_VAO(&globalRenderer.m_shader_manager), entityCounter(1)
{
	AddProcedure(new UpdateFinal);
}

Scene::~Scene()
{
	for (auto& ptr : m_procedure_stack) {
		delete ptr;
	}
}
unsigned int Scene::AddLayer()
{
	m_layers.push_back(core::Layer(m_VAO, m_VAO.NewBatchBuffer()));
	m_EMS.PushNewBatch(m_layers.back().GetVertexBuffer());

	return m_layers.size() - 1;
}

void Scene::AttachGUI(GuiTemplate* nGUI, int layer)
{
	if (layer < 0) {
		m_layers.back().AttachGUI(nGUI);
	}
	else {
		m_layers[layer].AttachGUI(nGUI);
	}

	m_SceneCallback.GuiIsAttached = true;
}

void Scene::AddProcedure(Procedure* nProc)
{
	nProc->AssignEMS(&m_EMS);
	m_procedure_stack.push_back(nProc);
}

void Scene::Update(float deltaTime)
{
	for (auto& layer : m_layers) {
		layer.UpdateGUI(deltaTime);
	}

	for (int i = (m_procedure_stack.size() - 1); i >= 0; i--) {
		m_procedure_stack[i]->OnUpdate(deltaTime);
	}
}
