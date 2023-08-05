#pragma once
#include "framework.h"
#include "mathTypes.h"
#include "request.h"
#include "scene.h"

#include <memory>

class Renderer {
private:
	std::shared_ptr<core::Platform> m_platform_renderer;
public:
	Renderer(int windowWidth = 1, int windowHeight = 1);
	~Renderer();

	void inline SetBackgroundColor(Strider::ColorVec4f color) {
		m_platform_renderer->SetBackgroundColor(color.red, color.green, color.blue, color.alpha);
	}

	void inline Clear() { m_platform_renderer->Clear(); }
	void StartNewFrame();
	void Render(std::shared_ptr<Scene>& scene);

	void FinishRender();


	void OnRequest(Request& request);
};