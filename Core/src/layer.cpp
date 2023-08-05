#include "layer.h"

Layer::Layer(SceneID s_ID, LayerID l_ID)
	: m_sID(s_ID), m_lID(l_ID), m_layer_gui(nullptr)
{
	m_framework = Framework::GetInstance();
	m_framework->Platform()->AddDrawLayer(s_ID, l_ID);
}

Layer::~Layer()
{
	if (m_layer_gui != nullptr) {
		delete m_layer_gui;
	}
}


void Layer::AttachGUI(GuiTemplate* nGUI)
{
	if (m_layer_gui != nullptr) {
		delete m_layer_gui;
	}

	m_framework->Platform()->AttachGui(m_sID, m_lID, nGUI);

	m_layer_gui = nGUI;
}

void Layer::UpdateGUI(float deltaTime)
{
	if (m_layer_gui != nullptr) {
		m_layer_gui->OnUpdate(deltaTime);
	}
}
