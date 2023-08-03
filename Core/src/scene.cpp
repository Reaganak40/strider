#include "scene.h"

Scene::Scene(core::Renderer& globalRenderer)
	: m_renderer(globalRenderer), m_VAO(&globalRenderer.m_shader_manager), entityCounter(1)
{
	layers = {};
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
	layers.push_back(m_VAO.NewBatchBuffer());
	m_EMS.PushNewBatch(m_VAO.GetBatchBuffer(layers.back())->batchVBO.GetVertexBuffer());

	return layers.size() - 1;
}

void Scene::AddProcedure(Procedure* nProc)
{
	nProc->AssignEMS(&m_EMS);
	m_procedure_stack.push_back(nProc);
}

void Scene::Update(float deltaTime)
{
	for (int i = (m_procedure_stack.size() - 1); i >= 0; i--) {
		m_procedure_stack[i]->OnUpdate(deltaTime);
	}
}
