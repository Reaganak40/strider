#pragma once
#include "framework.h"
#include "entity.h"
#include "mesh.h"
#include "gui.h"

class Layer {
private:
	SceneID m_sID;
	LayerID m_lID;

	GuiTemplate* m_layer_gui;
	Framework* m_framework;
public:
	Layer(SceneID s_ID, LayerID l_ID);
	~Layer();

	
		
	void AttachGUI(GuiTemplate* nGUI);
	void UpdateGUI(float deltaTime);
};
