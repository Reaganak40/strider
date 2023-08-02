#pragma once

#include "core.h"
#include <renderer/renderer.h>
#include "timestep.h"
#include <memory>

class Scene;
namespace core {

	class AppInstance {
	private:
		GLFWwindow* window;
		int windowWidth, windowHeight;

		std::unordered_map <SceneID, std::shared_ptr<Scene>> m_scenes;
		
		std::shared_ptr<Scene> m_currentScene;

	public:
		Renderer m_renderer;

		AppInstance(const char* nWindowName, int nWindowWidth, int nWindowHeight);
		~AppInstance();

		inline bool IsOpen() { return !glfwWindowShouldClose(window); }

		void Update(float deltaTime);
		void Render();

		std::shared_ptr<Scene> NewScene(SceneID name);
		std::shared_ptr<Scene> SetScene(SceneID name);
	};

}

class StriderEngine {
private:
	core::AppInstance* app;

public:
	Timestep timestep;
	StriderEngine();
	~StriderEngine();

	int CreateWindow(const char* windowName, int nWindowWidth, int nWindowHeight);

	inline bool IsOpen() { return app->IsOpen(); }
	void Update();
	inline void Render() { app->Render(); }

	inline std::shared_ptr<Scene> NewScene(SceneID name) { return app->NewScene(name); }
	inline std::shared_ptr<Scene> SetScene(SceneID name) { return app->SetScene(name); }

};