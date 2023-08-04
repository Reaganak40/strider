#pragma once
#include <stdio.h>

class GuiTemplate {
private:
public:
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() { printf("Warning: Using GuiTemplate::OnRender()!\n"); }
protected:
	void RenderImGui();
};

class DiagnosticsGUI : public GuiTemplate {
public:
	void OnUpdate(float deltaTime) override;
	void OnRender() override;
};