#pragma once

#include "core.h"
#include "timestep.h"
#include <memory>

#include "framework.h"
#include "renderer.h"
#include "scene.h"
#include "messageManager.h"
#include <unordered_map>

class Application {
private:


	Framework* m_framework;
	
	std::unordered_map<const char*, std::shared_ptr<Scene>> m_scenes;
	std::shared_ptr<Renderer> m_renderer;

	MessageManager* m_message_manager;
	MessageResponse frameworkState;

	std::shared_ptr<Scene> m_currentScene;
	Timestep timestep;
public:

	Application(const char* nWindowName, int nWindowWidth, int nWindowHeight);
	~Application();

	inline bool IsOpen() { return m_framework->Platform()->IsOpen(); }

	void Update();
	void Render();

	std::shared_ptr<Scene> NewScene(const char* name);
	std::shared_ptr<Scene> SetScene(const char* name);
};