#include "scene.h"

Scene::Scene(core::Renderer& globalRenderer)
	: m_renderer(globalRenderer), m_VAO(&globalRenderer.m_shader_manager), entityCounter(1)
{
	layers = {};
}

Scene::~Scene()
{
}
unsigned int Scene::AddLayer()
{
	layers.push_back(m_VAO.NewBatchBuffer());
	return layers.size() - 1;
}
