#include "renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight)
	: m_platform_renderer(Framework::GetInstance()->Platform())
{
	m_platform_renderer->AddDefaultShader(windowWidth, windowHeight);
}

Renderer::~Renderer()
{
}

void Renderer::StartNewFrame()
{
	m_platform_renderer->GuiNewFrame();
}

void Renderer::Render(std::shared_ptr<Scene>& scene)
{
	m_platform_renderer->Draw(scene->GetID());
}

void Renderer::FinishRender()
{
	m_platform_renderer->FinishDrawStep();
}

void Renderer::OnRequest(Request& request)
{
	switch (request.context) {
	case ATTACH_GUI:
		break;
	default:
		printf("Warning: [EntityManager] Could not interpret request: %d\n", request.context);
	}
}

