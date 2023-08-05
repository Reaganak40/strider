#pragma once

#include "core.h"
#include "mesh.h"
#include "gui.h"


namespace core {

	class Platform {
	private:
	public:
		Platform() {}
		~Platform() {}

		virtual void CreateWindow(const char* nWindowName, int nWindowWidth, int nWindowHeight) {}
		virtual void DestroyWindow() {}
		
		virtual void Clear() {}
		virtual void Draw(const SceneID& s_ID) {}
		virtual void FinishDrawStep() {}
		virtual void SetBackgroundColor(float r, float g, float b, float a) {}

		virtual bool IsOpen() { return false; }

		virtual void AddDefaultShader(int windowWidth = 1, int windowHeight = 1) {}
		virtual void AddDrawLayer(const SceneID& s_ID, const LayerID& l_ID) {}
		virtual Vertex* GetMeshBatchLocation(const SceneID& s_ID, const LayerID& l_ID) { return nullptr; }
		virtual unsigned int AddMesh(const SceneID& s_ID, const LayerID& l_ID, const Mesh& mesh) { return 0; }

		virtual void AttachGui(const SceneID& s_ID, const LayerID& l_ID, GuiTemplate*& gui) {}
		virtual void GuiNewFrame() {}

		virtual float GetTime() { return 0.0f; }

	};
}