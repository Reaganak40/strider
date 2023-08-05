#pragma once

#include "core.h"
#include "glCore.h"
#include "platform.h"

#include <memory>

namespace core {
	class RendererGL;
	
	class PlatformGL : public Platform {
	private:
		GLFWwindow* window;
		std::unique_ptr<RendererGL> m_renderer;

	public:
		PlatformGL();
		~PlatformGL();

		void CreateWindow(const char* windowName, int nWindowWidth, int nWindowHeight) override final;
		void AddDefaultShader(int windowWidth = 1, int windowHeight = 1) override final;
		void Clear() override final;
		void Draw(const SceneID& s_ID) override final;
		void FinishDrawStep() override final;
		void SetBackgroundColor(float r, float g, float b, float a) override final;
		bool IsOpen() override final;
		void AddDrawLayer(const SceneID& s_ID, const LayerID& l_ID) override final;
		Vertex* GetMeshBatchLocation(const SceneID& s_ID, const LayerID& l_ID) override final;
		unsigned int AddMesh(const SceneID& s_ID, const LayerID & l_ID, const Mesh& mesh) override final;
		void AttachGui(const SceneID& s_ID, const LayerID& l_ID, GuiTemplate*& gui) override final;
		void GuiNewFrame() override final;
		float GetTime() override final;

	};
}