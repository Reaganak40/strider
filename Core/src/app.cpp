#include "core.h"
#include "app.h"
#include "utils.h"


Application::Application(const char* nWindowName, int nWindowWidth, int nWindowHeight)
{
	SetRandomSeed();

	m_framework = Framework::GetInstance();
	m_framework->Platform()->CreateWindow(nWindowName, nWindowWidth, nWindowHeight);

	m_renderer = std::make_shared<Renderer>(nWindowWidth, nWindowHeight);
	m_renderer->SetBackgroundColor({ 0.1f, 0.1f, 0.1f, 1.0f });

	m_message_manager = MessageManager::GetInstance();
	m_message_manager->SetRenderer(m_renderer);

	//frameworkState = m_message_manager->Query<Framework>(WindowOpen);
}

Application::~Application()
{
}

void Application::Update()
{
	/* Get new deltaTime */
	timestep.Update();

	/* API Procedures */
	m_renderer->Clear();
	m_renderer->StartNewFrame();
	
	/* Update Scene */
	m_currentScene->Update(timestep.deltaTime);
}

void Application::Render()
{
	/* Render current scene to the screen */
	if (m_currentScene) {
		m_renderer->Render(m_currentScene);
	}

	/* Swap buffers and poll events. */
	m_renderer->FinishRender();
}

std::shared_ptr<Scene> Application::NewScene(const char* name)
{
	std::shared_ptr<Scene> nScene = std::make_shared<Scene>();
	
	nScene->AddLayer();

	m_scenes[name] = nScene;
	return nScene;
}
std::shared_ptr<Scene> Application::SetScene(const char* name)
{
	if (m_scenes.find(name) == m_scenes.end()) {
		NewScene(name);
	}

	m_currentScene = m_scenes[name];
	m_currentScene->Activate();

	return m_currentScene;
}

